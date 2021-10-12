/**
 * Archivo: startup.S
 * Función: Realiza la inicialización básica del uP:
 *          - Setea los modos de funcionamiento del uP,
 *          - Prepara el stack,
 *          - Habilita los distintos coprocesadores,
 *          - Salta hacia main.c
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

/* Referencias a funciones externas */

.extern _irq_enable
.extern _irq_disable
.extern _UART_init
.extern init_board
.extern main

.extern UND_Handler
.extern SVC_Handler
.extern PREF_Handler
.extern ABT_Handler
.extern IRQ_Handler
.extern FIQ_Handler

.global _startup

/* Referencia a variables o simbolos externos */
.extern _ISR_VECTORS_BASE
.extern __isr_table_start__

.extern _startup
.extern __bss_start
.extern __bss_end


.extern __irq_stack_top__
.extern __fiq_stack_top__ 
.extern __svc_stack_top__
.extern __abt_stack_top__
.extern __und_stack_top__    
.extern __sys_stack_top__ 


/* Tamaños en Public RAM */
.equ _PUB_RAM_SYS_STACK_SIZE, 256
.equ _PUB_RAM_IRQ_STACK_SIZE, 256
.equ _PUB_RAM_FIQ_STACK_SIZE, 8
.equ _PUB_RAM_SVC_STACK_SIZE, 8
.equ _PUB_RAM_ABT_STACK_SIZE, 8
.equ _PUB_RAM_UND_STACK_SIZE, 8

/* 
 Definimos bits del CPSR para los diferentes modos
   
 CPSR: Current Program Status Register - Ver ARM B1
 El SPSR posee la misma estructura que el CPSR, solo que se refiere al
 "Saved Program Status Register".
 */

.equ USR_MODE, 0x10    /* USER       - Encoding segun ARM B1.3.1 (pag. B1-1139): 10000 - Bits 4:0 del CPSR */
.equ FIQ_MODE, 0x11    /* FIQ        - Encoding segun ARM B1.3.1 (pag. B1-1139): 10001 - Bits 4:0 del CPSR */
.equ IRQ_MODE, 0x12    /* IRQ        - Encoding segun ARM B1.3.1 (pag. B1-1139): 10010 - Bits 4:0 del CPSR */
.equ SVC_MODE, 0x13    /* Supervisor - Encoding segun ARM B1.3.1 (pag. B1-1139): 10011 - Bits 4:0 del CPSR */
.equ ABT_MODE, 0x17    /* Abort      - Encoding segun ARM B1.3.1 (pag. B1-1139): 10111 - Bits 4:0 del CPSR */
.equ UND_MODE, 0x1B    /* Undefined  - Encoding segun ARM B1.3.1 (pag. B1-1139): 11011 - Bits 4:0 del CPSR */
.equ SYS_MODE, 0x1F    /* System     - Encoding segun ARM B1.3.1 (pag. B1-1139): 11111 - Bits 4:0 del CPSR */
.equ I_BIT,    0x80    /* Mask bit I - Encoding segun ARM B1.3.3 (pag. B1-1149) - Bit 7 del CPSR */
.equ F_BIT,    0x40    /* Mask bit F - Encoding segun ARM B1.3.3 (pag. B1-1149) - Bit 6 del CPSR */

/* Modo de funcionamiento: arm */
.code 32

/* Hasta este momento, no hay nada inicializado */
.section ._start_code
_startup:
    LDR R0,=__isr_table_start__

    LDR R1, =_startup
    STR R1, [R0,#0x20]

    LDR R1, =UND_Handler
    STR R1, [R0, #0x24]

    LDR R1, =SVC_Handler
    STR R1, [R0, #0x28]

    LDR R1, =PREF_Handler
    STR R1, [R0, #0x2C]

    LDR R1, =ABT_Handler
    STR R1, [R0, #0x30]

    LDR R1, =_startup
    STR R1, [R0, #0x34]

    LDR R1, =IRQ_Handler
    STR R1, [R0, #0x38]

    LDR R1, =FIQ_Handler
    STR R1, [R0, #0x3C]


/* Limpiamos la sección BSS - Sugerido por Starterware */
_clear_BSS:
    LDR R0, =__bss_start__      /* Dirección de inicio de la sección BSS (pública) */
    LDR R1, =__bss_end__        /* Dirección final de la sección BSS (pública) */
    MOV R2, #0                  /* Copiamos el valor "0" en R2 */
    CMP R0,R1
    BEQ _STACK_INIT             /* Para el caso particular en el que bss está vacía (__bss_start__ == __bss_end__) no hay nada que inicializar, asi que me salteo el loop */
_LOOP:
    STR R2, [R0], #4            /* El contenido de R2 es cargado en "lo apuntado" por R0, luego incrementa la dirección de R0 */
    CMP R0, R1                  /* Comparamos R0 y R1, que poseen las direcciones de interés */
    BLE _LOOP                   /* Mientras la comparación anterior sea falsa, se vuelve a _LOOP */
_STACK_INIT:
    /* Inicializamos los stack pointers para los diferentes modos de funcionamiento */
    MSR cpsr_c,#(IRQ_MODE | I_BIT |F_BIT)
    LDR SP,=__irq_stack_top__     /* IRQ stack pointer */

    MSR cpsr_c,#(FIQ_MODE | I_BIT |F_BIT)
    LDR SP,=__fiq_stack_top__     /* FIQ stack pointer */

    MSR cpsr_c,#(SVC_MODE | I_BIT |F_BIT)
    LDR SP,=__svc_stack_top__     /* SVC stack pointer */

    MSR cpsr_c,#(ABT_MODE | I_BIT |F_BIT)
    LDR SP,=__abt_stack_top__     /* ABT stack pointer */

    MSR cpsr_c,#(UND_MODE | I_BIT |F_BIT)
    LDR SP,=__und_stack_top__     /* UND stack pointer */

    MSR cpsr_c,#(SYS_MODE | I_BIT |F_BIT)
    LDR SP,=__sys_stack_top__     /* SYS stack pointer */

    /* Habilitar UART y luego salta al main() */
    LDR R10, =init_board
    MOV LR, PC
    BX R10

idle:
    WFI
    B idle

.end

