/**
 * Archivo: low_level_cpu_access.S
 * Función: funciones de bajo nivel de acceso al control del CPU
 * Autor: Brito Sergio Sebastian
 * Referencia: los códigos desarrollados fueron tomados a partir de diferentes referencias y en base al TRM. El objetivo de esta recopilación
 *             fue darle un enfoque didáctico para el alumno, con comentarios pertinentes y referencias a la documentación disponible.
 *             Ref. 1: https://github.com/allexoll/BBB-BareMetal
 *             Ref. 2: https://github.com/auselen/down-to-the-bone
 *             Ref. 3: https://github.com/mvduin/bbb-asm-demo
 *             Ref. 4: Starterware de Texas Instruments
 *             Ref. 5: AM335x ARM Cortex-A8 - Technical Reference Manual (TRM)
 *             Ref. 6: ARM Architectural Reference Manual ARMv7-A and ARMv7-R Edition (ARM)
 *             Ref. 7: Instruction Set Assembly Guide for ARMv7 and earlier ARM Architectures (Version 2.0) - Ref. Guide (ISAG)
 **/

 .section .text_pub

.global _irq_enable
.global _irq_disable
.global _MMU_Enable
.global _MMU_Disable
.global _LOAD_ISR_Vectors_Base
.global _WRITE_8
.global _WRITE_16
.global _WRITE_32
.global _READ_8
.global _READ_16
.global _READ_32
.global _HALT_CPU
.global _READ_CPSR_REGS
.global _EOI

/*
 Habilita interrupciones
 */
.align 4             // Alineado a 4 Bytes
_irq_enable:
    DSB
    MRS R0, CPSR
    BIC R0, #0x80
    MSR CPSR, R0
    DSB
    ISB
    BX LR

/*
 Deshabilita interrupciones
 */
.align 4             // Alineado a 4 Bytes
_irq_disable:
    DSB
    MRS R0, CPSR
    ORR R0, #0x40
    MSR CPSR, R0
    DSB
    ISB
    BX LR

/*
    Carga la dirección base en la Public RAM de
    la tabla de ISR
 */
_LOAD_ISR_Vectors_Base:
    MCR     P15, #0, R0, C12, C0, #0
    DSB
    BX      LR


/*
    Realiza una suspensión del uP esperando por un evento
    de interrupción para salir de ese estado. Es como la instrucción
    HLT de Intel X86.
 */
.align 4             // Alineado a 4 Bytes
_HALT_CPU:
    WFI
    BX LR

/*
    Utilizamos la instrucción WFE (Wait for Event) para generarnos 
    un "Magic Breakpoint" propio y poder debuggear el código
 */
.align 4             // Alineado a 4 Bytes
_BREAKPOINT_DEBUG:
    WFE
    BX LR

.align 4             // Alineado a 4 Bytes
_READ_CPSR_REGS:
    DSB
    MRS R0, CPSR
    BX LR

.align 4             // Alineado a 4 Bytes
_EOI:
    MOV r0,#0x1
    LDR r1,=0x48200000
    STR r0, [r1, #0x48]

    BX LR
/*
    Funciones de escritura y lecutra de 8, 16 y 32 bits
    Para las funciones _WRITE_X, desde C es: _WRITE_X(DIRECCION, VALOR) 
 */
.align 4             // Alineado a 4 Bytes
_WRITE_8:
    STRB R1, [R0]       // STR Byte el contenido de R0 en la posición R1
    BX LR

_WRITE_16:
    STRH R1, [R0]       // STR HalfWord el contenido de R0 en la posición R1
    BX LR

_WRITE_32:
    STR R1, [R0]       // STR Word el contenido de R0 en la posición R1
    BX LR

_READ_8:
    LDRB R0, [R0]
    BX LR

_READ_16:
    LDRH R0, [R0]
    BX LR

_READ_32:
    LDR R0, [R0]
    BX LR
