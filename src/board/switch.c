/**
 * Archivo: switch.c
 * Función: Uso de switchs de la BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/

#include "../../inc/board/switch.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/utils/low_level_cpu_access.h"


bool switch_read(switch_typedef sw);
void switch_init(switch_typedef sw, mode_switch_typedef mode);

__attribute__((section(".text_pub"))) void switch_init(switch_typedef sw, mode_switch_typedef mode)
{
    GPIO_Init_Port(GPIO2, GPIO_CONFIG);
    uint32_t aux_reg = 0;
    if (mode == SIMPLE)
    {
        GPIO_Init_Pin(CM_conf_lcd_data2, MODO_7);
        GPIO_Port_ModuleCtrl(GPIO2,0x01UL);
        GPIO_SoftReset(GPIO2);
        GPIO_Set_Direction(GPIO2,sw,INPUT_SIGNAL);
        GPIO_Clear_Pin(GPIO2,sw);
    }
    else
    {
        GPIO_SoftReset(GPIO2);
        GPIO_Set_Port_Mode(GPIO2,0x10);
        GPIO_Port_ModuleCtrl(GPIO2,0);
        GPIO_Set_Direction(GPIO2,sw,INPUT_SIGNAL);
        GPIO_Set_Status_IRQ(GPIO2,sw,0);
        GPIO_SetEdgeDetect_IRQ(GPIO2,sw,FALLING_EDGE);
        GPIO_SetDebounce(GPIO2,sw,16);
        aux_reg = _READ_32(GPIO_BASE_ARRAY[GPIO2] + GPIO_IRQSTATUS_0);
        aux_reg = aux_reg | (0b01 << 8);
        _WRITE_32((GPIO_BASE_ARRAY[GPIO2] + GPIO_IRQSTATUS_0), aux_reg);
    }
} 

__attribute__((section(".text_pub"))) bool switch_read(switch_typedef sw)
{
    return ((bool)(GPIO_Get_Pin(GPIO2, sw)));
}