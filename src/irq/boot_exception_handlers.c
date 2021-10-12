/**
 * Archivo: boot_exception_handlers.c
 * Función: manejadores de las excepciones
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

#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/debug_tools.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/board/uart.h"

void UND_Handler(void);
void SVC_Handler(void);
void PREF_Handler(void);
void ABT_Handler(void);
void IRQ_Handler(void);
void FIQ_Handler(void);

__attribute__((section(".text_pub")))__attribute__((naked)) void UND_Handler(void)
{   
    UART_printf(UART_0,"\n\r[Handler] - UNDEFINED Exception\n",34);
    // while(1);
}


__attribute__((section(".text_pub"))) __attribute__((naked)) void SVC_Handler(void)
{   
    UART_printf(UART_0,"\n\r[Handler] - SVC Exception\n",28);
    // while(1);    
}


__attribute__((section(".text_pub"))) __attribute__((interrupt("abort"))) void PREF_Handler(void)
{   
    ConsoleUtilsPrintf("\n\r[Boot Handler] - Pref_Handler");
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    uint32_t IFAR = 0, IFSR = 0;
    uint32_t DFAR = 0, DFSR = 0;
    uint32_t AIFSR = 0, ADFSR = 0;
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception");
    UART_printf(UART_0,"\n\r[Handler] - ABORT Exception\n",31);
    asm("MRC p15, 0, R0, c6, c0, 2");
    asm("STR R0,%0" : "=m"(IFAR));
    asm("MRC p15, 0, R0, c5, c0, 1");
    asm("STR R0,%0" : "=m"(IFSR));
    asm("MRC p15, 0, R0, c6, c0, 0");
    asm("STR R0,%0" : "=m"(DFAR));
    asm("MRC p15, 0, R0, c5, c0, 0");
    asm("STR R0,%0" : "=m"(DFSR));
    asm("MRC p15, 0, R0, c5, c1, 0");
    asm("STR R0,%0" : "=m"(ADFSR));
    asm("MRC p15, 0, R0, c5, c1, 1");
    asm("STR R0,%0" : "=m"(AIFSR));
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - IFAR: 0x%x",IFAR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - IFSR: 0x%x",IFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - AIFSR: 0x%x",AIFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - DFAR: 0x%x",DFAR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - DFSR: 0x%x",DFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - ABORT Exception - ADFSR: 0x%x",ADFSR);
    PrintStack(10);
    while(1) {}
}


__attribute__((section(".text_pub"))) __attribute__((interrupt("abort"))) void ABT_Handler(void)
{   
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    uint32_t IFAR = 0, IFSR = 0;
    uint32_t DFAR = 0, DFSR = 0;
    uint32_t AIFSR = 0, ADFSR = 0;
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception");
    asm("MRC p15, 0, R0, c6, c0, 2");
    asm("STR R0,%0" : "=m"(IFAR));
    asm("MRC p15, 0, R0, c5, c0, 1");
    asm("STR R0,%0" : "=m"(IFSR));
    asm("MRC p15, 0, R0, c6, c0, 0");
    asm("STR R0,%0" : "=m"(DFAR));
    asm("MRC p15, 0, R0, c5, c0, 0");
    asm("STR R0,%0" : "=m"(DFSR));
    asm("MRC p15, 0, R0, c5, c1, 0");
    asm("STR R0,%0" : "=m"(ADFSR));
    asm("MRC p15, 0, R0, c5, c1, 1");
    asm("STR R0,%0" : "=m"(AIFSR));
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - IFAR: 0x%x",IFAR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - IFSR: 0x%x",IFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - AIFSR: 0x%x",AIFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - DFAR: 0x%x",DFAR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - DFSR: 0x%x",DFSR);
    ConsoleUtilsPrintf("\n\r[Boot Handler] - PREFETCHABORT Exception - ADFSR: 0x%x",ADFSR);
    PrintStack(10);
    while(1) {}
}


__attribute__((section(".text_pub"))) __attribute__((naked)) void IRQ_Handler(void)
{   
    asm("SUB      LR, LR, #4");                     // Apply lr correction
    asm("STMFD    r13!, {r0-r12, r14}");            // Save context onto IRQ stack
    asm("ISB");
    asm("DSB");
    procIrqHandler((_READ_32(NVIC + INTC_SIR_IRQ)) & 0x7F); //Go to function
    // asm("CPSID    i");                              // Disable IRQ interrupts
    _WRITE_32(NVIC + INTC_CONTROL, (uint32_t)0x01); // Enable new IRQ Generation
    asm("DSB");
    asm("LDMFD    r13!, {r0-r12, pc}^");            // Restore the IRQ context and return
}


__attribute__((section(".text_pub"))) __attribute__((naked)) void FIQ_Handler(void)
{   
    UART_printf(UART_0,"\n\r[Handler] - FIQ\n",18);
    // while(1);    
}