/**
 * Archivo: exception_handlers.s
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

.global UND_Handler
.global SVC_Handler
.global PREF_Handler
.global ABT_Handler
.global IRQ_Handler
.global FIQ_Handler

.extern procIrqHandler

.equ    ADDR_SIR_IRQ, NVIC + INTC_SIR_IRQ

UND_Handler:  
    RFEFD   SP!  

SVC_Handler:
    RFEFD   SP!

PREF_Handler:
    RFEFD   SP!

ABT_Handler:
    RFEFD   SP!

IRQ_Handler:
    RFEFD   SP!

FIQ_Handler:
    RFEFD   SP!
