/**
 * Archivo: gpio.h
 * Función: definición para el uso de la UART para BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/


#ifndef __GPIO_H
#define __GPIO_H


#define GPIO0 0
#define GPIO1 1
#define GPIO2 2
#define GPIO3 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
#define PIN16 16
#define PIN17 17
#define PIN18 18
#define PIN19 19
#define PIN20 20
#define PIN21 21
#define PIN22 22
#define PIN23 23
#define PIN24 24
#define PIN25 25
#define PIN26 26
#define PIN27 27
#define PIN28 28
#define PIN29 29
#define PIN30 30
#define PIN31 31

#define GPIO_CONFIG         0x00040002   /* La configuración es la correspondiente según TRM 8.1.12.1.32 */
#define GPIO_CONFIG_MASK    0x00030000

#define FALLING_EDGE            0x0
#define RISING_EDGE             0x1
#define OUTPUT_SIGNAL           0x0
#define INPUT_SIGNAL            0x1

/* Modos de operación para los pines */
#define MODO_0 0
#define MODO_1 1
#define MODO_2 2
#define MODO_3 3
#define MODO_4 4
#define MODO_5 5
#define MODO_6 6
#define MODO_7 7

#define GPIO_REVISION           0x000
#define GPIO_SYSCONFIG          0x010
#define GPIO_EOI                0x020
#define GPIO_IRQSTATUS_RAW_0    0x024
#define GPIO_IRQSTATUS_RAW_1    0x028
#define GPIO_IRQSTATUS_0        0x02C
#define GPIO_IRQSTATUS_1        0x030
#define GPIO_IRQSTATUS_SET_0    0x034
#define GPIO_IRQSTATUS_SET_1    0x038
#define GPIO_IRQSTATUS_CLR_0    0x03C
#define GPIO_IRQSTATUS_CLR_1    0x040
#define GPIO_IRQWAKEN_0         0x044
#define GPIO_IRQWAKEN_1         0x048
#define GPIO_SYSSTATUS          0x114
#define GPIO_CTRL               0x130
#define GPIO_OE                 0x134
#define GPIO_DATAIN             0x138
#define GPIO_DATAOUT            0x13C
#define GPIO_LEVELDETECT0       0x140
#define GPIO_LEVELDETECT1       0x144
#define GPIO_RISINGDETECT       0x148
#define GPIO_FALLINGDETECT      0x14C
#define GPIO_DEBOUNCENABLE      0x150
#define GPIO_DEBOUNCINGTIME     0x154
#define GPIO_CLEARDATAOUT       0x190
#define GPIO_SETDATAOUT         0x194




static const unsigned int GPIO_BASE_ARRAY[4] = {0x44E07000, 0x4804C000, 0x481AC000, 0x481AE000};

#include "../utils/types.h"

extern uint16_t GPIO_Init_Port(uint16_t, uint32_t);
extern void GPIO_Set_Port(uint8_t, uint32_t);
extern uint16_t GPIO_Get_Port(uint8_t );
extern void GPIO_Clear_Port(uint8_t );
extern void GPIO_Set_Port_Mode(uint8_t , uint16_t);
extern void GPIO_Port_ModuleCtrl(uint8_t, uint8_t);

extern uint16_t GPIO_Init_Pin(uint32_t, uint16_t);
extern void GPIO_Set_Pin(uint8_t, uint8_t);
extern uint16_t GPIO_Get_Pin(uint8_t, uint8_t);
extern void GPIO_Clear_Pin(uint8_t, uint8_t);

extern void GPIO_Set_Direction(uint8_t, uint8_t, uint8_t);
extern uint8_t GPIO_Get_Direction(uint8_t, uint8_t);
extern void GPIO_SoftReset(uint8_t );

extern void GPIO_Set_Status_IRQ(uint8_t , uint8_t , uint8_t );
extern void GPIO_Set_LogicLevel_IRQ(uint8_t, uint8_t, uint8_t, uint8_t);
extern void GPIO_SetEdgeDetect_IRQ(uint8_t, uint8_t, uint8_t );
extern void GPIO_SetDebounce(uint8_t, uint8_t, uint8_t);
extern void GPIO_ClearDebounce(uint8_t, uint8_t);

#endif /* defined(__GPIO_H) */