/**
 * Archivo: led.c
 * Función: Uso de LEDs de la BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/

#include "../../inc/board/led.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/utils/types.h"


void LED_init(void);
void LED_on(LED_typedef);
void LED_off(LED_typedef);
void LED_invert(LED_typedef);

__attribute__((section(".text_pub"))) void LED_init(void)
{
    GPIO_Init_Port(GPIO1, GPIO_CONFIG);
    GPIO_Init_Pin(CM_conf_gpmc_a5, MODO_7);
    GPIO_Init_Pin(CM_conf_gpmc_a6, MODO_7);
    GPIO_Init_Pin(CM_conf_gpmc_a7, MODO_7);
    GPIO_Init_Pin(CM_conf_gpmc_a8, MODO_7);
    GPIO_Port_ModuleCtrl(GPIO1,0x01UL);
    GPIO_SoftReset(GPIO1);

    GPIO_Set_Direction(GPIO1, LED0 , OUTPUT_SIGNAL);
    GPIO_Set_Direction(GPIO1, LED1 , OUTPUT_SIGNAL);
    GPIO_Set_Direction(GPIO1, LED2 , OUTPUT_SIGNAL);
    GPIO_Set_Direction(GPIO1, LED3 , OUTPUT_SIGNAL);

    GPIO_Clear_Pin(GPIO1, LED0);
    GPIO_Clear_Pin(GPIO1, LED1);
    GPIO_Clear_Pin(GPIO1, LED2);
    GPIO_Clear_Pin(GPIO1, LED3);
}

__attribute__((section(".text_pub"))) void LED_on(LED_typedef led)
{
    GPIO_Set_Pin(GPIO1,led);
}

__attribute__((section(".text_pub"))) void LED_off(LED_typedef led)
{
    GPIO_Clear_Pin(GPIO1,led);
}

__attribute__((section(".text_pub"))) void LED_invert(LED_typedef led)
{
    (GPIO_Get_Pin(GPIO1,led) == HIGH)?(GPIO_Clear_Pin(GPIO1,led)):(GPIO_Set_Pin(GPIO1,led));
}