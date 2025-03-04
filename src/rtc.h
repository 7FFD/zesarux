#pragma once

#if defined(__APPLE__)
        #include <sys/syslimits.h>
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
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

typedef struct
{
    u_int8_t second;
    u_int8_t second_timer;
    u_int8_t minute;
    u_int8_t minute_timer;
    u_int8_t hour;
    u_int8_t hour_timer;
    u_int8_t dayOfWeek;
    u_int8_t day;
    u_int8_t month;
    u_int8_t year;
    u_int8_t reg0A; //  UIP DV2 DV1 DV0 RS3  RS2 RS1   RS0 = #20
    u_int8_t reg0B; //  SET PIE AIE UIE SQWE DM  24/12 DSE = #03
    u_int8_t reg0C; //  IRQF PF AF  UF  0    0   0     0   = #00
    u_int8_t reg0D; //  VRT   0  0  0   0    0   0     0   = #80
    u_int8_t ram0[36];
    u_int8_t century;
    u_int8_t ram1[77];
} rtc_mem_t;

typedef struct
{
    u_int8_t enabled;
    u_int8_t active;
    u_int8_t addr;
    union
    {    
        rtc_mem_t mem;
        u_int8_t dat[128];
    };
} rtc_t;

extern rtc_t mrgluk_rtc;

void rtc_update(rtc_t* prtc);