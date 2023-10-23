#include <stdio.h>
#include "debug.h"
#include "sdcard.h"

z80_byte puerto_0x75 = 0xFF;

sdcard_t sdcard = {0,SDCARD_UNKNOWN,0,0,0,SDCARD_R1_ILLEGAL_COMMAND,0xFF,1,{0,0,0,0},0,SDSC,0};

void sdcard_reset();
static z80_byte sdcard_crc7_add(z80_byte crc, z80_byte value);
static z80_int sdcard_crc16_add(z80_int crc, z80_byte value);

void sdcard_enable()
{
    puerto_0x75 = 0x00;
    // Initialize SD Card here
    sdcard.enabled.v = 1;
    sdcard.cs.v = 0;
    sdcard.command_crc_on.v = 1;
    sdcard.command_state = SDCARD_R1_IDLE_STATE;
    sdcard.command_mode = SDCARD_STD_MODE;
    sdcard_reset();
}

void sdcard_disable()
{
    sdcard_reset();
    sdcard.enabled.v = 0;
    sdcard.command_mode = SDCARD_STD_MODE;
    puerto_0x75 = 0xFF;
}

void sdcard_cs(z80_bit value)
{
    if(sdcard.cs.v != value.v)
    {
        sdcard.cs = value;
        sdcard_reset();
        if(sdcard.command_mode == SDCARD_STD_MODE);
        else if(sdcard.command_mode == SDCARD_SWITCH2APP_MODE && !sdcard.cs.v) sdcard.command_mode = SDCARD_APP_MODE;
        else if(sdcard.command_mode == SDCARD_APP_MODE && !sdcard.cs.v) sdcard.command_mode = SDCARD_STD_MODE;
        debug_printf(VERBOSE_INFO, "SD Card CS: %d", sdcard.cs.v);
    }
}

void sdcard_reset()
{
    debug_printf(VERBOSE_INFO, "SD Card reset");
    sdcard.command_param_index = 0;
    sdcard.command = SDCARD_UNKNOWN;
    sdcard.command_ret = 0xFF;
    sdcard.command_crc = 0;
    sdcard.command_state &= SDCARD_R1_IDLE_STATE;
    sdcard.command_ret = 0xFF;
}

z80_byte sdcard_read()
{
    debug_printf(VERBOSE_INFO, "SD Card read: 0x%02X, MODE: %d, CS:%d", sdcard.command_ret, sdcard.command_mode, sdcard.cs.v);
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

static int set_r1_state(z80_byte value, z80_byte state)
{
    if(sdcard.command_param_index != 6) return 0;
    sdcard.command_ret = sdcard.command_state = state;
    return 1;
}

static int set_fe_token(z80_byte value)
{
    if(sdcard.command_param_index != 7 || is_error_state()) return 0;
    sdcard.command_ret = 0xfe;
    return 1;
}

static int set_r3_state(z80_byte value, z80_byte state)
{
    if(set_r1_state(value, state)) return 1;

    if(!is_error_state() && sdcard.command_param_index > 6 && sdcard.command_param_index < 11)
    {
        sdcard.command_ret = sdcard.command_params[sdcard.command_param_index - 7];
        return 1;
    } 
    return 0;
}

static int set_r7_state(z80_byte value, z80_byte state)
{
    return set_r3_state(value, state);
}

static int set_busy(z80_byte value)
{
    if(sdcard.command_param_index < 7) return 0;
    sdcard.command_ret = 0xFF;
    return 1;
}

static void illegal_cmd(z80_byte value)
{
    if(read_param(value));
    else if(read_crc7(value));
    else if(set_r1_state(value, SDCARD_R1_ILLEGAL_COMMAND|SDCARD_R1_IDLE_STATE));
    else set_busy(value);
}

void sdcard_write(z80_byte value)
{
    debug_printf(VERBOSE_INFO, "SD Card write: 0x%02X, MODE: %d, CS: %d", value, sdcard.command_mode, sdcard.cs.v);

    // if chip select hasn't been activated before, just ignore input
    if(!sdcard.cs.v) return;

    // if it's first byte then it must be a command
    if(!sdcard.command_param_index)
    {
        sdcard.command = value;
        sdcard.command_crc = sdcard_crc7_add(0, sdcard.command);
        sdcard.command_ret = 0xFF;
    }
    else if(!sdcard.command_mode)
    {
        // regular CMD processing
        switch (sdcard.command)
        {
        case SDCARD_GO_IDLE_STATE:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, SDCARD_R1_IDLE_STATE));
            else set_busy(value);
            break;        
        case SDCARD_CRC_ON_OFF:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_crc_on.v = sdcard.command_params[3] & 1;
                debug_printf(VERBOSE_INFO, "SD Card CRC check: %s", (sdcard.command_crc_on.v ? "ON" : "OFF"));
            }
            else set_busy(value);
            break;
        case SDCARD_SEND_IF_COND:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                if(sdcard.type == SDSC)
                {
                    set_r1_state(value, sdcard.command_state|SDCARD_R1_ILLEGAL_COMMAND);
                }
                else
                {
                    sdcard.command_params[0] = 0; 
                    sdcard.command_params[1] = 0; 
                    sdcard.command_params[2] &= 0x01; 
                    sdcard.command_params[3] &= 0xAA; 
                }
            }
            else if(set_r7_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE));
            else set_busy(value);
            break;        
        case SDCARD_APP_CMD:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_mode = SDCARD_SWITCH2APP_MODE;
            }
            else set_busy(value);
            break;
        case SDCARD_READ_OCR:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                sdcard.command_params[0] = 0x40; 
                sdcard.command_params[1] = sdcard.command_params[2] = sdcard.command_params[3] = 0; 
            }
            else if(set_r3_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE));
            else set_busy(value);
            break;
        case SDCARD_SET_BLOCK_LEN:
            if(read_param(value));
            else if(read_crc7(value));
            else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE) && !is_error_state())
            {
                if(!(sdcard.command_params[0] == 0x00 && 
                   sdcard.command_params[1] == 0x00 &&
                   sdcard.command_params[2] == 0x02 &&
                   sdcard.command_params[3] == 0x00))
                   set_r1_state(value, sdcard.command_state|SDCARD_R1_PARAM_ERROR);
            }
            else if(set_r3_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE));
            else set_busy(value);
            break;
        case SDCARD_READ_SBLOCK:
            {
                static z80_int crc16;
                static char buff[512];

                if(read_param(value));
                else if(read_crc7(value));
                else if(set_r1_state(value, sdcard.command_state&SDCARD_R1_IDLE_STATE))
                {
                    crc16 = 0;
                    long position = (sdcard.command_params[0]<<24) + 
                               (sdcard.command_params[1]<<16) + 
                               (sdcard.command_params[2]<<8) + 
                               (sdcard.command_params[3]<<0);
                    if(sdcard.type > SDSC) position <<= 9;
                    
                    debug_printf(VERBOSE_INFO, "SD Card position: 0x%08lX", position);
// TODO: Add file error handling
                    FILE *pf = fopen(sdcard.file_path, "rb");
                    fseek(pf, position, SEEK_SET);
                    fread(buff, 1, sizeof(buff), pf);
                    fclose(pf);
                }
                else if(set_fe_token(value));
                else if(!is_error_state() && sdcard.command_param_index > 7 && sdcard.command_param_index < 520)
                {
                    sdcard.command_ret = buff[sdcard.command_param_index - 8];
                    crc16 = sdcard_crc16_add(crc16, sdcard.command_ret);
                }
                else if(!is_error_state() && sdcard.command_param_index == 520)
                {
                    sdcard.command_ret = (crc16>>8)&0xFF;
                }
                else if(!is_error_state() && sdcard.command_param_index == 521)
                {
                    sdcard.command_ret = crc16&0xFF;
                }
                else set_busy(value);
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
            else if(set_r1_state(value, SDCARD_R1_READY) && !is_error_state())
            {
                sdcard.command_params[0] &= sdcard.type > SDSC ? 0x40 : 0;
                sdcard.command_params[1] = sdcard.command_params[2] = sdcard.command_params[3] = 0;
            }
            else if(set_r3_state(value, SDCARD_R1_READY));
            else set_busy(value);
            break;         
        default:
            // process as regular command but return Illegal Command error
            illegal_cmd(value);
            break;
        }
    }
    // next parameter index
    sdcard.command_param_index++;
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
