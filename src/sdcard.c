#include <stdio.h>
#include "debug.h"
#include "sdcard.h"

sdcard_t sdcard = {0,SDCARD_UNKNOWN,0,0,0,SDCARD_R1_ILLEGAL_COMMAND,0xFF,1,{0,0,0,0},0,0,SDSC,0};

void sdcard_reset();
static z80_byte sdcard_crc7_add(z80_byte crc, z80_byte value);
static z80_int sdcard_crc16_add(z80_int crc, z80_byte value);

void sdcard_enable()
{
    // Initialize SD Card here
    sdcard.cs = 3;
    sdcard.command_crc_on.v = 1;
    sdcard_reset();
    sdcard.enabled.v = 1;
}

void sdcard_disable()
{
    sdcard_reset();
    sdcard.cs = 2;
    sdcard.enabled.v = 0;
}

// 0x77 sd card control port
// Bit 0: sd power 0=off,1=on
// Bit 1: sd cs 1=deselected,0=selected
// Bit 2-7: unused
void sdcard_cs(z80_byte value)
{
    if(sdcard.cs != (value&3))
    {
        sdcard.cs = value&3;
        // expect new command????
        sdcard.command_param_index = 0;
        debug_printf(VERBOSE_INFO, "SD Card CS: %d", sdcard.cs);
    }
}

void sdcard_reset()
{
    debug_printf(VERBOSE_INFO, "SD Card reset");
    sdcard.command_param_index = 0;
    sdcard.command = SDCARD_UNKNOWN;
    sdcard.command_mode = SDCARD_IDLE_MODE;
    sdcard.command_crc = 0;
    sdcard.command_state = SDCARD_R1_IDLE_STATE;
    sdcard.command_ret = 0xFF;
}

z80_byte sdcard_read()
{
    debug_printf(VERBOSE_INFO, "SD Card read: 0x%02X, MODE: %d, CS:%d", sdcard.command_ret, sdcard.command_mode, sdcard.cs);
    sdcard_write(0xff);
    return sdcard.command_ret;
}

static int read_param(z80_byte value)
{
    if(sdcard.command_param_index > 4) return 0;
    sdcard.command_params[sdcard.command_param_index - 1] = value;
    sdcard.command_crc = sdcard_crc7_add(sdcard.command_crc, value);
    return 1;
}

static int read_crc7(z80_byte value)
{
    if(sdcard.command_param_index != 5) return 0;

    sdcard.command_crc |= 1;
    if(sdcard.command_crc_on.v)
    {
        sdcard.command_state |= sdcard.command_crc != value ? SDCARD_R1_CRC_ERROR : 0;
        debug_printf(VERBOSE_INFO, "SD Card CRC check ON: 0x%02X, Host CRC: 0x%02X", sdcard.command_crc, value);
    }
    else
    {
        debug_printf(VERBOSE_INFO, "SD Card CRC check OFF: 0x%02X, Host CRC: 0x%02X", sdcard.command_crc, value);
    }    
    return 1;
}

static int is_error_state()
{
    return sdcard.command_state > 1;
}

static int set_wait_state(z80_byte value)
{
    if(sdcard.command_param_index == 6)
    {
        sdcard.command_ret = 0xFF;
        return 1;
    }
    return 0;
}

static int set_r1_state(z80_byte value, z80_byte state)
{
    if(sdcard.command_param_index == 7)
    {
        sdcard.command_ret = sdcard.command_state = state;
        sdcard.command_ret_params_count--;
        return 1;
    }
    return 0;
}

static int set_fe_token(z80_byte value)
{
    if(sdcard.command_param_index != 8 || is_error_state()) return 0;
    sdcard.command_ret = 0xfe;
    return 1;
}

static int get_stop_transfer(z80_byte value)
{
    if(value == SDCARD_STOP_TRANSFER)
    {
        sdcard.command = value;
        sdcard.command_param_index = 0;
        sdcard.command_crc = sdcard_crc7_add(0, sdcard.command);
        sdcard.command_ret = 0xFF;
        sdcard.command_ret_params_count = 0;
        return 1;
    }
    return 0;
}

static int get_fe_token(z80_byte value)
{
    if(is_error_state() || 
       !(sdcard.command == SDCARD_READ_SBLOCK || sdcard.command == SDCARD_READ_MBLOCK || sdcard.command == SDCARD_WRITE_SBLOCK) ||
       sdcard.command_param_index != 8 || 
       value != 0xfe) 
       return 0;

    return 1;
}

static int get_fd_token(z80_byte value)
{
    if(is_error_state() || 
       sdcard.command != SDCARD_WRITE_MBLOCK ||
       sdcard.command_param_index != 8 || 
       value != 0xfd) 
       return 0;

    sdcard.command_ret_params_count = -1;
    return 1;
}

static int get_fc_token(z80_byte value)
{
    if(is_error_state() || 
       sdcard.command != SDCARD_WRITE_MBLOCK ||
       sdcard.command_param_index != 8 || 
       value != 0xfc) 
       return 0;

    return 1;
}

static int set_r3_state(z80_byte value, z80_byte state)
{
    if(!is_error_state() && sdcard.command_param_index > 7 && sdcard.command_param_index < 12)
    {

        sdcard.command_ret = sdcard.command_params[sdcard.command_param_index - 8];
        sdcard.command_ret_params_count--;
        return 1;
    } 
    return 0;
}

static int set_r7_state(z80_byte value, z80_byte state)
{
    return set_r3_state(value, state);
}

static void illegal_cmd(z80_byte value)
{
    if(read_param(value));
    else if(read_crc7(value));
    else if(set_wait_state(value));
    else if(set_r1_state(value, SDCARD_R1_ILLEGAL_COMMAND|(sdcard.command_state&SDCARD_R1_IDLE_STATE)));
    return;
}

static void sdcard_read_sector(long position, char buff[512])
{
    FILE *pf = fopen(sdcard.file_path, "rb");
    if(pf)
    {
        debug_printf(VERBOSE_INFO, "SD Card read sector: 0x%08lX to %s, fd: %p", position, sdcard.file_path, pf);
        if(!fseek(pf, position, SEEK_SET))
        {
            debug_printf(VERBOSE_INFO, "SD Card positioning: 0x%08lX", ftell(pf));
            long read = fread(buff, 1, 512, pf);
            sdcard.command_ret_params_count += 512 + 2;
            debug_printf(VERBOSE_INFO, "SD Card bytes read: %ld", read);
        }
        if(ferror(pf))
        {
            debug_printf(VERBOSE_ERR, "SD Card read error: %d, Can't read file: ", ferror(pf), sdcard.file_path);
            sdcard.command_state |= SDCARD_R1_ADDR_ERROR;
        }
        fclose(pf);
    }
    else
    {
        debug_printf(VERBOSE_ERR, "SD Card read error: %d, Can't open file: ", ferror(pf), sdcard.file_path);
        sdcard.command_state |= SDCARD_R1_ADDR_ERROR;
    }
}


void sdcard_write(z80_byte value)
{
    debug_printf(VERBOSE_INFO, "SD Card write: 0x%02X, MODE: %d, CS: %d", value, sdcard.command_mode, sdcard.cs);

    // if chip select hasn't been activated before, just ignore input
    if(sdcard.cs != 1) return;

    // if it's first byte then it must be a command
    if(!sdcard.command_param_index)
    {
        sdcard.command = value;
        sdcard.command_crc = sdcard_crc7_add(0, sdcard.command);
        sdcard.command_ret = 0xFF;
        sdcard.command_ret_params_count = 0;

        if(value == 0xFF) return;
    }
    else if(sdcard.command_mode == SDCARD_IDLE_MODE || sdcard.command_mode == SDCARD_RDY_MODE)
    {
        static z80_int crc16;
        static long position;
        static char buff[512];

        // regular CMD processing
        switch (sdcard.command)
        {
        case SDCARD_GO_IDLE_STATE:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, SDCARD_R1_IDLE_STATE))
            {
                sdcard_reset();
                sdcard.command_ret = sdcard.command_state;
            }
            break;        
        case SDCARD_CRC_ON_OFF:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_crc_on.v = sdcard.command_params[3] & 1;
                debug_printf(VERBOSE_INFO, "SD Card CRC check: %s", (sdcard.command_crc_on.v ? "ON" : "OFF"));
            }
            break;
        case SDCARD_SEND_IF_COND:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                if(sdcard.command_param_index == 6) break;

                if(sdcard.type == SDSC)
                {
                   sdcard.command_state |= SDCARD_R1_ILLEGAL_COMMAND;
                }
                else
                {
                    sdcard.command_params[0] = 0; 
                    sdcard.command_params[1] = 0; 
                    sdcard.command_params[2] &= 0x01; 
                    sdcard.command_params[3] &= 0xAA;
                    sdcard.command_ret_params_count += 4;
                }
            }
            else if(set_r7_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE));
            break;        
        case SDCARD_APP_CMD:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_mode = SDCARD_APP_MODE;
            }
            break;
        case SDCARD_READ_OCR:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_params[0] = 0x40; 
                sdcard.command_params[1] = sdcard.command_params[2] = sdcard.command_params[3] = 0;
                sdcard.command_ret_params_count += 4;
            }
            else if(set_r3_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE));
            break;
        case SDCARD_SET_BLOCK_LEN:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                if(!(sdcard.command_params[0] == 0x00 && 
                   sdcard.command_params[1] == 0x00 &&
                   sdcard.command_params[2] == 0x02 &&
                   sdcard.command_params[3] == 0x00))
                   sdcard.command_state |= SDCARD_R1_PARAM_ERROR;
            }
            break;
        case SDCARD_STOP_TRANSFER:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state());
            break;
        case SDCARD_READ_SBLOCK:
        case SDCARD_READ_MBLOCK:
            {
                if(read_param(value));
                else if(read_crc7(value));
                else if(set_wait_state(value));
                else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE)&&!is_error_state())
                {
                    crc16 = 0;
                    position = (sdcard.command_params[0]<<24) + 
                               (sdcard.command_params[1]<<16) + 
                               (sdcard.command_params[2]<<8) + 
                               (sdcard.command_params[3]<<0);
                    if(sdcard.type > SDSC) position <<= 9;
                    
                    sdcard_read_sector(position, buff);
                }
                else if(get_stop_transfer(value));
                else if(set_fe_token(value));
                else if(!is_error_state() && sdcard.command_param_index > 8 && sdcard.command_param_index < 521)
                {
                    sdcard.command_ret = buff[sdcard.command_param_index - 9];
                    crc16 = sdcard_crc16_add(crc16, sdcard.command_ret);
                    sdcard.command_ret_params_count--;
                }
                else if(!is_error_state() && sdcard.command_param_index == 521)
                {
                    sdcard.command_ret = (crc16>>8)&0xFF;
                    sdcard.command_ret_params_count--;
                }
                else if(!is_error_state() && sdcard.command_param_index == 522)
                {
                    sdcard.command_ret = crc16&0xFF;
                    sdcard.command_ret_params_count--;

                    if(sdcard.command == SDCARD_READ_MBLOCK)
                    {
                        crc16 = 0;
                        position += 512;
                        sdcard.command_param_index = 7;
                        sdcard_read_sector(position, buff);
                    }
                }
                else if(is_error_state())
                {
                    sdcard.command_ret_params_count = -1;
                }
            }
            break;    
        case SDCARD_WRITE_SBLOCK:
        case SDCARD_WRITE_MBLOCK:
            {
                if(read_param(value));
                else if(read_crc7(value));
                else if(set_wait_state(value));
                else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE)&&!is_error_state())
                {
                    crc16 = 0;
                    position = (sdcard.command_params[0]<<24) + 
                               (sdcard.command_params[1]<<16) + 
                               (sdcard.command_params[2]<<8) + 
                               (sdcard.command_params[3]<<0);
                    if(sdcard.type > SDSC) position <<= 9;
                    
                    sdcard.command_ret_params_count += 512 + 2 + 1 + 10;
                    debug_printf(VERBOSE_INFO, "SD Card position: 0x%08lX", position);
                }
                else if(sdcard.command_param_index == 8 && value == 0xff)
                {
                    sdcard.command_ret = 0xFF;
                    sdcard.command_param_index--;
                }
                else if(get_fe_token(value))
                {
                    debug_printf(VERBOSE_INFO, "SD Card sblock write token received");
                }
                else if(get_fd_token(value))
                {
                    debug_printf(VERBOSE_INFO, "SD Card mblock write stop received");
                }
                else if(get_fc_token(value))
                {
                    debug_printf(VERBOSE_INFO, "SD Card mblock write token received");
                }
                else if(!is_error_state() && sdcard.command_param_index > 8 && sdcard.command_param_index < 521)
                {
                    debug_printf(VERBOSE_INFO, "SD Card write data to buff[%d]=%d", sdcard.command_param_index - 9, value);
                    buff[sdcard.command_param_index - 9] = value;
                    crc16 = sdcard_crc16_add(crc16, value);
                    sdcard.command_ret_params_count--;
                }
                else if(!is_error_state() && sdcard.command_param_index == 521)
                {
                    sdcard.command_ret_params_count--;
                    if(sdcard.command_crc_on.v && ((z80_byte)((crc16>>8)&0xFF)) != value) 
                    {
                        sdcard.command_state |= SDCARD_R1_CRC_ERROR;
                        debug_printf(VERBOSE_INFO, "SD Card write sector: CRC error: %hhd <> %hhd", ((z80_byte)((crc16>>8)&0xFF)), value);
                    }
                }
                else if(!is_error_state() && sdcard.command_param_index == 522)
                {
                    sdcard.command_ret_params_count--;
                    if(sdcard.command_crc_on.v && ((z80_byte)(crc16&0xFF)) != value) 
                    {
                        sdcard.command_state |= SDCARD_R1_CRC_ERROR;
                        debug_printf(VERBOSE_INFO, "SD Card write sector: CRC error: %hhd <> %hhd", ((z80_byte)(crc16&0xFF)), value);
                    }
                    else
                    {
                        FILE *pf = fopen(sdcard.file_path, "rb+");
                        if(pf)
                        {
                            debug_printf(VERBOSE_INFO, "SD Card write sector: 0x%08lX to %s, fd: %p", position, sdcard.file_path, pf);
                            if(!fseek(pf, position, SEEK_CUR))
                            {
                                debug_printf(VERBOSE_INFO, "SD Card positioning: 0x%08lX", ftell(pf));
                                long written = fwrite(buff, 1, sizeof(buff), pf);
                                debug_printf(VERBOSE_INFO, "SD Card bytes written: %ld", written);
                            }
                            if(ferror(pf))
                            {
                                debug_printf(VERBOSE_ERR, "SD Card write error: %d, Can't write file: ", ferror(pf), sdcard.file_path);
                                sdcard.command_state = 0x0D;
                            }
                            fclose(pf);
                        }
                        else
                        {
                            debug_printf(VERBOSE_ERR, "SD Card write error: %d, Can't open file: ", ferror(pf), sdcard.file_path);
                            sdcard.command_state = 0x0D;
                        }
                        sdcard.command_ret = 0xFF;

                        if(sdcard.command == SDCARD_WRITE_MBLOCK)
                        {
                            crc16 = 0;
                            position += 512;
                            sdcard.command_param_index = 7;
                            sdcard.command_ret_params_count += 512 + 2 + 1 + 10;
                        }
                    }
                }
                else if(!is_error_state() && sdcard.command_param_index == 523)
                {
                    sdcard.command_ret_params_count--;
                    sdcard.command_ret = 0x05; // return CRC OK
                }
                else if(!is_error_state() && sdcard.command_param_index > 523 && sdcard.command_ret_params_count)
                {
                    sdcard.command_ret_params_count--;
                    sdcard.command_ret = 0x00; // emulate busy state (internal write)
                }
                else if(!is_error_state() && sdcard.command_param_index > 523 && !sdcard.command_ret_params_count)
                {
                    sdcard.command_ret_params_count--;
                    sdcard.command_ret = 0xFF; // emulate end of busy
                }
                else
                {
                    sdcard.command_state = 0x0D;
                    sdcard.command_ret_params_count = -1;
                }
            }    
            break;        
        default:
            // process as regular command but return Illegal Command error
            illegal_cmd(value);
            break;
        }
    }
    else
    {
        // APP CMD processing
        switch (sdcard.command)
        {
        case SDCARD_SEND_OP_COND:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_wait_state(value));
            else if(set_r1_state(value, SDCARD_R1_READY) && !is_error_state())
            {
                sdcard.command_mode = SDCARD_RDY_MODE;
            }
            break;         
        default:
            // process as regular command but return Illegal Command error
            illegal_cmd(value);
            break;
        }
    }
    // next parameter index
    sdcard.command_param_index = sdcard.command_ret_params_count < 0 ? 0 : sdcard.command_param_index + 1;
}

static z80_byte sdcard_crc7_add(z80_byte crc, z80_byte value)
{
    crc ^= value;
    for (int i = 0; i < 8; i++)
    {
        if((crc&0x80) == 0x80) crc ^= SDCARD_CRC7_POLY;
        crc <<= 1;
    }
    return crc;
}

static z80_int sdcard_crc16_add(z80_int crc, z80_byte value)
{
	crc  = (z80_byte)(crc >> 8)|(crc << 8);
	crc ^=  value;
	crc ^= (z80_byte)(crc & 0xff) >> 4;
	crc ^= (crc << 8) << 4;
	crc ^= ((crc & 0xff) << 4) << 1;

    return crc;
}
