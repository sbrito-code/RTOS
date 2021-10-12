/**
 * Archivo: system_utils.c
 * Función: algunos wrappers útiles
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
#include "../../inc/utils/low_level_cpu_access.h"


extern void _start(void);
void ControlModule_Set(uint32_t, uint32_t, uint32_t );
uint32_t ControlModule_Get(uint32_t, uint32_t);
void ClockModule_Set(uint32_t, uint32_t, uint32_t);
uint32_t ClockModule_Get(uint32_t, uint32_t);

/*
    Wrapper para escritura de registros de control
*/
__attribute__((section(".text_pub"))) void ControlModule_Set(uint32_t dir_base, uint32_t offset, uint32_t valor)
    {
        _WRITE_32(dir_base + offset, valor);
    }

/*
    Wrapper para lectura de registros de control
*/
__attribute__((section(".text_pub"))) uint32_t ControlModule_Get(uint32_t dir_base, uint32_t offset)
    {   
        uint32_t valor;

        valor = _READ_32(dir_base + offset);
        return valor;
    }

/*
    Wrapper para escritura de registros de clock
*/
__attribute__((section(".text_pub"))) void ClockModule_Set(uint32_t dir_base,  uint32_t offset, uint32_t valor)
    {   
        _WRITE_32(dir_base + offset, valor);
    }

/*
    Wrapper para lectura de registros de clock
*/
__attribute__((section(".text_pub"))) uint32_t ClockModule_Get(uint32_t dir_base,  uint32_t offset)
    {       
        uint32_t valor;
        valor = _READ_32(dir_base + offset);

        return valor;
    }

// static uint32_t const tabla_vectores[14] = {
//     0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
//     0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
//     0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
//     0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
//     0xE59FF014,    /* Opcode for loading PC with the contents of [PC + 0x14] */
//     0xE24FF008,    /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
//     0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
//     0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
//     (uint32_t)_start,
//     (uint32_t)UND_Handler,
//     (uint32_t)SVC_Handler,
//     (uint32_t)PREF_Handler,
//     (uint32_t)ABT_Handler,
//     (uint32_t) 0,
//     (uint32_t)IRQ_Handler,
//     (uint32_t)FIQ_Handler};


// int load_isr_vectors(uint32_t dir_base)
//     {   
//         uint32_t *ptr_dst = 0;
//         uint32_t *ptr_src = 0;
//         uint32_t i;

//         ptr_dst = dir_base;
//         ptr_src = (uint32_t) tabla_vectores;

//         _LOAD_ISR_Vectors_Base(dir_base);

//         for(i = 0; i < sizeof(tabla_vectores)/sizeof(tabla_vectores[0]); i++)
//             {
//                 ptr_dst[i] = ptr_src[i];
//             }

//     }