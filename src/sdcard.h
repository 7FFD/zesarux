#pragma once

#if defined(__APPLE__)
        #include <sys/syslimits.h>
#endif


#include "cpu.h"


//Por el tema de usar PATH_MAX en windows
#ifdef MINGW
#include <stdlib.h>
#define PATH_MAX MAX_PATH
#define NAME_MAX MAX_PATH
#endif

//Por el uso de PATH_MAX en FreeBSD
//Nota: no en todos mis .h que uso PATH_MAX tengo este include, es debido a que en algunos incluyo utils.h y en este utils.h se incluye a su vez limits.h
#ifdef __FreeBSD__
#include <limits.h>
#endif

#define SDCARD_CONTROL_PORT     0x75
#define SDCARD_DATA_PORT        0x77

#define SDCARD_CRC7_POLY        0x89

typedef enum 
{ 
    SDCARD_GO_IDLE_STATE = 0x40|00,
    SDCARD_SEND_OP_COND  = 0x40|41,
    SDCARD_SEND_IF_COND  = 0x40|8,
    SDCARD_SEND_CID      = 0x40|10,
    SDCARD_APP_CMD       = 0x40|55,
    SDCARD_READ_OCR      = 0x40|58,
    SDCARD_CRC_ON_OFF    = 0x40|59,
    SDCARD_SET_BLOCK_LEN = 0x40|16,
    SDCARD_READ_SBLOCK   = 0x40|17,
    SDCARD_WRITE_SBLOCK  = 0x40|24,
    SDCARD_UNKNOWN       = 0x40|0x3F
} sdcard_cmd_t;

typedef enum
{
    SDCARD_STD_MODE        = 0,
    SDCARD_APP_MODE        = 1,
    SDCARD_SWITCH2APP_MODE = 2
} sdcard_cmd_mode_t;

typedef enum 
{ 
    SDSC = 0, 
    SDHC = 1, 
    SDXC = 2, 
    SDUC = 3 
} sdcard_type_t;

typedef enum
{
    SDCARD_R1_READY           = 0x00,
    SDCARD_R1_IDLE_STATE      = 0x01,
    SDCARD_R1_ERASE_RESET     = 0x02,
    SDCARD_R1_ILLEGAL_COMMAND = 0x04,
    SDCARD_R1_CRC_ERROR       = 0x08,
    SDCARD_R1_ERASE_SEQ_ERROR = 0x10,
    SDCARD_R1_ADDR_ERROR      = 0x20,
    SDCARD_R1_PARAM_ERROR     = 0x40
} sdcard_r1_t;

typedef struct
{
    // state parameters
    z80_bit cs;
    sdcard_cmd_t command;
    sdcard_cmd_mode_t command_mode;
    int command_param_index;
    z80_byte command_crc;
    sdcard_r1_t command_state;
    z80_byte command_ret;
    z80_bit command_crc_on;
    z80_byte command_params[4];

    // configuration parameters
    z80_bit enabled;
    sdcard_type_t type;
    char file_path[PATH_MAX];
}  sdcard_t;

void sdcard_enable();

void sdcard_disable();

void sdcard_cs(z80_bit value);

z80_byte sdcard_read();

void sdcard_write(z80_byte value);

extern sdcard_t sdcard;

extern z80_byte puerto_0x75;
