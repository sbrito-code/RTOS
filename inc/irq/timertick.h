/**
 * Archivo: timertick.h
 * Función: archivo de definiciones para el uso del Timertick (DMTimer1)
 * Autor: Brito Sergio Sebastian
 **/

#ifndef __TIMERTICK_H
#define __TIMERTICK_H


// TRM 8.1.12.3.9
#define TIMER_1MS_CLK_OSC_SOURCE      0
#define TIMER_1MS_CLK_32KHZ_SOURCE    1
#define TIMER_1MS_CLK_TCLKIN_SOURCE   2
#define TIMER_1MS_CLK_RC32K_SOURCE    3
#define TIMER_1MS_CLK_32768_SOURCE    4

// TRM 2.1 - Tabla 2-2 y TRM 20.2.5
#define TIMER_1MS_BASE 0x44E31000

#define TIMER_1MS_TIDR          0x0
#define TIMER_1MS_TIOCP_CFG     0x10
#define TIMER_1MS_TISTAT        0x14
#define TIMER_1MS_TISR          0x18
#define TIMER_1MS_TIER          0x1C
#define TIMER_1MS_TWER          0x20
#define TIMER_1MS_TCLR          0x24
#define TIMER_1MS_TCRR          0x28
#define TIMER_1MS_TLDR          0x2C
#define TIMER_1MS_TTGR          0x30
#define TIMER_1MS_TWPS          0x34
#define TIMER_1MS_TMAR          0x38
#define TIMER_1MS_TCAR1         0x3C
#define TIMER_1MS_TSICR         0x40
#define TIMER_1MS_TCAR2         0x44
#define TIMER_1MS_TPIR          0x48
#define TIMER_1MS_TNIR          0x4C
#define TIMER_1MS_TCVR          0x50
#define TIMER_1MS_TOCR          0x54
#define TIMER_1MS_TOWR          0x58

// TRM 2.1 - Tabla 2-2 y TRM 20.3
#define RTC_BASE_ADDR           0x44E3E000

#define RTC_SECOND              0x0
#define RTC_MINUTE              0x4
#define RTC_HOUR                0x8
#define RTC_DAY                 0xC
#define RTC_MONTH               0x10
#define RTC_YEAR                0x14
#define RTC_DOTW                0x18
#define RTC_ALARMSECOND         0x20
#define RTC_ALARMMINUTE         0x24
#define RTC_ALARMHOUR           0x28
#define RTC_ALARMDAY            0x2C
#define RTC_ALARMMONTH          0x30
#define RTC_ALARMYEAR           0x34
#define RTC_CTRL                0x40
#define RTC_STATUS              0x44
#define RTC_INTERRUPT           0x48
#define RTC_COMPLSB             0x4C
#define RTC_COMPMSB             0x50
#define RTC_OSC                 0x54
#define RTC_SCRATCH0            0x60
#define RTC_SCRATCH1            0x64
#define RTC_SCRATCH2            0x68
#define RTC_KICK0               0x6C
#define RTC_KICK1               0x70

// Especificos del RTC IP en AM335x
#define RTC_REVISION            0x74
#define RTC_SYSCONFIG           0x78
#define RTC_IRQWAKEEN           0x7C
#define RTC_ALARM2_SECONDS      0x80
#define RTC_ALARM2_MINUTES      0x84
#define RTC_ALARM2_HOURS        0x88
#define RTC_ALARM2_DAYS         0x8C
#define RTC_ALARM2_MONTHS       0x90
#define RTC_ALARM2_YEARS        0x94
#define RTC_PMIC                0x98
#define RTC_DEBOUNCE            0x9C

// Para deshabilitar la protección de escritura del RTC
#define RTC_KICK0R_KEY      0x83E70B13
#define RTC_KICK1R_KEY      0x95A4F1E0

extern void TimerTick_Init(uint32_t);
extern void TimerTick_Start(void);
extern void Enable_L3_L4_Clock_Systems(void);
extern void RTC_Config(uint32_t );

#endif /* defined(__TIMERTICK_H) */