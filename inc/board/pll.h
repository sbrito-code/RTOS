/**
 * Archivo: pll.h
 * Función: definición para el uso del pll para BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/

#define DDR_PLL 0
#define CORE_PLL 1
#define MPU_PLL 2
#define PER_PLL 3
#define DISP_PLL 4

extern void PLL_Config(uint8_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t);
extern uint32_t PLL_Get_InputClockFreq(void);