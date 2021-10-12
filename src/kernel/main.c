/**
 * Archivo: main.c
 * Función: A partir de este archivo, se realiza la guía de TPs
 * Autor: Brito Sergio Sebastian
 * Referencia: los códigos desarrollados fueron tomados a partir de diferentes referencias y en base al TRM. El objetivo de esta recopilación
 *             fue darle un enfoque didáctico para el alumno, con comentarios pertinentes y referencias a la documentación disponible.
 *             Ref. 1: https://github.com/allexoll/BBB-BareMetal
 *             Ref. 2: https://github.com/auselen/down-to-the-bone
 *             Ref. 3: https://github.com/mvduin/bbb-asm-demo
 *             Ref. 4: Starterware de Texas Instruments
 *             Ref. 5: AM335x ARM Cortex-A8 - Technical Reference Manual 
 *             Ref. 6: ARM Architectural Reference Manual ARMv7-A and ARMv7-R Edition (ARM)
 *             Ref. 7: Instruction Set Assembly Guide for ARMv7 and earlier ARM Architectures (Version 2.0) - Ref. Guide (ISAG)
 **/

#include "../../inc/utils/types.h"
#include "../../inc/board/uart.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/board/led.h"
#include "../../inc/utils/debug_tools.h"
#include "../../inc/utils/memcopy.h"
#include "../../inc/scheduler/os.h"

int main (void);

 __attribute__((section(".kernel_text")))int main(void)
{
    UART_printf(UART_0,"\n\r[TD3_uBoot]:~$ En el main -",31);  

    /* Encendido de Leds */
    ConsoleUtilsPrintf("\n\rEncendiendo el led 2...");
    LED_on(LED2);

    ConsoleUtilsPrintf("\n\rIniciando el SO... \n");
    //os_init_task_list();
    os_start(); /* initialize timer1 and select first context */

    ConsoleUtilsPrintf("\n\rDentro del while");
    while(1);

    return 0;
}