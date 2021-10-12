/**
 * Archivo: switch.h
 * Función: Uso de switchs de la BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/

#include "../board/gpio.h"

typedef enum
{
    SW2 = PIN8
} switch_typedef;

typedef enum
{
    SIMPLE,
    INTERRUPT_SW
} mode_switch_typedef;

/**
 * @fn void switch_init(switch_typedef sw, mode_switch_typedef mode)
 * @brief         Initialize the switch
 * @param[in]     SIMPLE: initialize the switch without interrupt
 *                INTERRUPT_SW: initialize the switch with interrupt
 * @return        void
 **/
extern void switch_init(switch_typedef sw, mode_switch_typedef mode);

/**
 * @fn uint16_t switch_read(switch_typedef sw)
 * @brief         Read the switch
 * @return        bool
 **/
extern bool switch_read(switch_typedef sw);

