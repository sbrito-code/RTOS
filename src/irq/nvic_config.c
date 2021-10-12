 /**
 * Archivo: nvic_config.c
 * Función: Realiza la inicialización básica de la UART, que oficia de debbuger para la guía de TP.
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
#include "../../inc/utils/system_utils.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/boot_exception_handlers.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/debug_tools.h"

void NVICConfig(void);
extern void NVIC_IRQ_Unmask(uint32_t );
void NVIC_Install_IRQ_Handler(void* ,uint32_t );


// Ver TRM 6.5.1 y los registros a partir de allí.

__attribute__((section(".text_pub"))) void NVICConfig(void)
    {   
        ConsoleUtilsPrintf("\n\r[TD3_uBoot]:~$ Dentro de NVICConfig ...");      
        _WRITE_32(NVIC+0x10,2);                 // SYSCONFIG - Reseteamos el controlador INTC - TRM 6.5.1.2
        while((_READ_32(NVIC+0x14)&0x1)==0);    // SYSSTATUS - Esperamos a que se complete el reset

        ConsoleUtilsPrintf("\n\r[TD3_uBoot]:~$ Pasamos el While...");

        _WRITE_32(NVIC+0x68,0xFF);	            // THRESHOLD - Se deshabilita
        _WRITE_32(NVIC+0x50,1);                 // IDLE - Se habilita como: functional clock free-running
         
        ConsoleUtilsPrintf("\n\r[TD3_uBoot]:~$ pasamos idle...");

        _WRITE_32(NVIC+0x94,0xFFFFFFFF);        // INTC_ISR_CLEAR0 - Limpiamos los bits de int. de soft.
        _WRITE_32(NVIC+0xB4,0xFFFFFFFF);        // INTC_ISR_CLEAR1 - Limpiamos los bits de int. de soft.
        _WRITE_32(NVIC+0xD4,0xFFFFFFFF);        // INTC_ISR_CLEAR2 - Limpiamos los bits de int. de soft.
        _WRITE_32(NVIC+0xF4,0xFFFFFFFF);        // INTC_ISR_CLEAR3 - Limpiamos los bits de int. de soft.

        ConsoleUtilsPrintf("\n\r[TD3_uBoot]:~$ Volviendo...");
        // _EOI;
    }

__attribute__((section(".text_pub"))) void NVIC_IRQ_Unmask(uint32_t irq_num)
    {

        uint32_t irq_num2vec = 0, mir_addr = 0;

        // irq_num2vec = (1 << (irq_num - 1));
        /* 
            Viendo el TRM 6.5.1 comienza los MIR (INTC_MIR_CLEAR0, en 0x88),
            y analizando que tenemos 4 registros MIR y 128 interrupciones disponi-
            bles, se puede calcular el registro MIR correspondiente a la IRQ en 
            acción, teniendo en cuenta que:
                NVIC_BASE_ADDR = 0x48200000
                INTC_MIR_CLEAR0 = 0x88
                INTC_MIR_CLEAR1 = 0xA8
                INTC_MIR_CLEAR2 = 0xC8
                INTC_MIR_CLEAR3 = 0xE8

                - La distancia entre los INTC_MIR_CLEARn es 0x20 posiciones,
                - Si pensamos que cada bit de cada registro refiere a una IRQ de 
                forma tal que: el bit 0 del registro INTC_MIR_CLEAR0 es la IRQ 0,
                y el bit 31 de la INTC_MIR_CLEAR0 es la IRQ 31, la IRQ 32 es el bit 0
                del INTC_MIR_CLEAR1, entonces, una división entera por 32 permite
                convertirnos el número de IRQ en decimal a un numero multiplo de 32 
                y así, multiplicando por 0x20 (que es la distancia enumerada antes),
                nos define el registro MIR correspondiente.
                - Luego, resta definir que bit dentro del registro definido previamente,
                y eso lo hacemos con una máscara 0x1F (es decir, un decimal restringido
                entre 0 y 31), y colocando un 1 (un left shift) en la posicion determinada
        */
        mir_addr = NVIC + 0x88 + (irq_num >> 0x5)*0x20;       
        irq_num2vec = 0x01 << (irq_num & 0x1F);
        //ConsoleUtilsPrintf("\n\rNVIC Config Reg.: 0x%x | Dato: 0x%x",mir_addr,irq_num2vec);
        _WRITE_32(mir_addr, irq_num2vec);

    }

__attribute__((section(".text_pub"))) void NVIC_Install_IRQ_Handler(void* irq_handler,uint32_t irq_num)
    {   
        IRQ_Vectors[irq_num] = irq_handler;       
    }