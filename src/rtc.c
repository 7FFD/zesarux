#include "debug.h"
#include "rtc.h"

//                  en ac ad       s    as     m    am     h    ah    dw     d     M     y    ra    rb    rc    rd
rtc_t mrgluk_rtc = { 1, 0, 0, 
                              { 0x17, 0xFF, 0x49, 0xFF, 0x20, 0xFF, 0x00, 0x02, 0x03, 0x25, 0x20, 0x03, 0x00, 0x80, 0x80, 0xFF, 
                                0x00, 0xAA, 0x47, 'R', 'T', 'C', ' ', 'e', 'm', 'u', 'l', 'a', 't', 'o', 'r', 
                                ' ', 'b', 'y', ' ', 'M', 'a', 'k', 's', 'y', 'm', '/', '7', 'F', 'F', 'D', 0xFF, 0xFF, 
                                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF //, 
                                // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                // 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
                              } 
};

static u_int8_t rtc_dec2bcd(u_int8_t num)
{
    return (((u_int8_t)(num/10)%10))<<4 | (num%10);
}

static void rtc_update(rtc_t* prtc)
{
    if(prtc->addr < 10)
    {
        time_t rawtime = time(NULL);
        struct tm *info = localtime(&rawtime);
        prtc->mem.second = rtc_dec2bcd(info->tm_sec);
        prtc->mem.minute = rtc_dec2bcd(info->tm_min);
        prtc->mem.hour = rtc_dec2bcd(info->tm_hour);
        prtc->mem.dayOfWeek = rtc_dec2bcd(info->tm_wday);
        prtc->mem.day = rtc_dec2bcd(info->tm_mday);
        prtc->mem.month = rtc_dec2bcd(info->tm_mon+1);
        prtc->mem.year = rtc_dec2bcd(info->tm_year);
    }
}

void rtc_cs(rtc_t* prtc, u_int8_t value)
{
    if(prtc && prtc->enabled)
    {
        prtc->active = value&0x80 ? 1 : 0;
    }
}

void rtc_set_addr(rtc_t* prtc, u_int8_t value)
{
    if(prtc && prtc->enabled && prtc->active) prtc->addr = value < MRGLUK_RTC_MEMORY_SIZE ? value : 0xFF;
}

u_int8_t rtc_read(rtc_t* prtc)
{
    if(prtc && prtc->enabled && prtc->active && prtc->addr < MRGLUK_RTC_MEMORY_SIZE)
    {
        if(prtc->addr < 10 && !(prtc->mem.reg0B&0x80)) rtc_update(prtc);
        return prtc->dat[prtc->addr];
    }
    return 0xFF;
}

void rtc_write(rtc_t* prtc, u_int8_t value)
{
    if(prtc && prtc->enabled && prtc->active && prtc->addr < MRGLUK_RTC_MEMORY_SIZE)
    {
        prtc->dat[prtc->addr] = value;
    }
}