/**
 * Archivo: system_utils.h
 * Función: definición para el uso de utilidades del sistema
 * Autor: Brito Sergio Sebastian
 **/


#ifndef __SYS_UTILS_H
#define __SYS_UTILS_H

#include "types.h"

extern void ControlModule_Set(uint32_t, uint32_t, uint32_t );
extern uint32_t ControlModule_Get(uint32_t, uint32_t);
extern void ClockModule_Set(uint32_t, uint32_t, uint32_t);
extern uint32_t ClockModule_Get(uint32_t, uint32_t);


#endif /* defined(__SYS_UTILS_H) */