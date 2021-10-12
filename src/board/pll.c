 /**
 * Archivo: pll.c
 * Función: Realiza la inicialización básica del PLL del core, DDR, PER, MMU, etc. 
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
#include "../../inc/utils/clock_modules.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/board/pll.h"

// Para debuggear, despues la saco
#include "../../inc/utils/console_utils.h"

void PLL_Config(uint8_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t , uint32_t);
uint32_t PLL_Get_InputClockFreq(void);

__attribute__((section(".text_pub"))) void PLL_Config(uint8_t pll_device, uint32_t clock_in, uint32_t pll_mult, uint32_t pll_div, uint32_t div_m2, uint32_t div_m4, uint32_t div_m5, uint32_t div_m6)
    {
        uint32_t clk_mode = 0, clk_sel = 0, div = 0;


        switch(pll_device)
            {
                case DDR_PLL:
                        // Ponemos el PLL en modo Bypass
                        // Esto nos permite configurar los demás registros PLL (divisores)
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_DDR);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x4;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_DDR,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_DDR) & 0x100) != 0x100);
                        
                        // Configuramos el clock del PLL ahora
                        clk_sel = _READ_32(CKM_WKUP + CKM_CLKSEL_DPLL_DDR);
                        clk_sel &= ~0x7FFFF; // Tenemos el 1er Byte para Div (en realidad, 7 bits). Y 11 bits para Mult.
                        clk_sel |= (pll_mult << 8)|pll_div;
                        _WRITE_32(CKM_WKUP + CKM_CLKSEL_DPLL_DDR,clk_sel);
                        
                        // Configuramos el divisor M2
                        div = _READ_32(CKM_WKUP + CKM_DIV_M2_DPLL_DDR);
                        div &= ~0x1F;
                        div |= div_m2;
                        _WRITE_32(CKM_WKUP + CKM_DIV_M2_DPLL_DDR,div_m2);
                        
                        // Entonces activamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_DDR);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x7;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_DDR,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_DDR) & 0x1) != 0x1);
                        break;

                case CORE_PLL:
                        // La lógica es la misma. Bypass y podemos configurar los divisores,
                        // luego habilitamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_CORE);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x4;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_CORE,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_CORE) & 0x100) != 0x100);
                        
                        clk_sel = _READ_32(CKM_WKUP + CKM_CLKSEL_DPLL_CORE);
                        clk_sel &= ~0x7FFFF; // Tenemos el 1er Byte para Div (en realidad, 7 bits). Y 11 bits para Mult.
                        clk_sel |= (pll_mult << 8)|pll_div;
                        _WRITE_32(CKM_WKUP + CKM_CLKSEL_DPLL_CORE,clk_sel);
                        _WRITE_32(CKM_WKUP + CKM_DIV_M4_DPLL_CORE,div_m4);  // 200 MHz
                        _WRITE_32(CKM_WKUP + CKM_DIV_M5_DPLL_CORE,div_m5);  // 250 MHz
                        _WRITE_32(CKM_WKUP + CKM_DIV_M6_DPLL_CORE,div_m6);  // 500 MHz

                        // Entonces activamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_CORE);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x7;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_CORE,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_CORE) & 0x1) != 0x1);
                        break;

                case MPU_PLL:
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_MPU);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x4;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_MPU,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_MPU) & 0x101) != 0x100);
                        
                        clk_sel = _READ_32(CKM_WKUP + CKM_CLKSEL_DPLL_MPU);
                        clk_sel &= ~0x7FFFF; // Tenemos el 1er Byte para Div (en realidad, 7 bits). Y 11 bits para Mult.
                        clk_sel |= (pll_mult << 8)|pll_div;
                        _WRITE_32(CKM_WKUP + CKM_CLKSEL_DPLL_MPU,clk_sel);

                        div = _READ_32(CKM_WKUP + CKM_DIV_M2_DPLL_MPU);
                        div &= ~0x1F;
                        div |= div_m2;
                        _WRITE_32(CKM_WKUP + CKM_DIV_M2_DPLL_MPU,div_m2);
                        
                        // Entonces activamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_MPU);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x7;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_MPU,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_MPU) & 0x101) != 0x1);
                        break;

                case PER_PLL:
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_PER);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x4;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_PER,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_PER) & 0x100) != 0x100);

                        clk_sel = _READ_32(CKM_WKUP + CKM_CLKSEL_DPLL_PER);
                        clk_sel &= 0x00F00000;
                        clk_sel |= 0x04000000; // SD divider = 4 para ambos OPP100 y OPP50
                        clk_sel |= (pll_mult << 8)|pll_div;
                        _WRITE_32(CKM_WKUP + CKM_CLKSEL_DPLL_PER,clk_sel);

                        div = _READ_32(CKM_WKUP + CKM_DIV_M2_DPLL_PER);
                        div = 0xFFFFFF80 | div_m2;
                        _WRITE_32(CKM_WKUP + CKM_DIV_M2_DPLL_PER,div);

                        // Entonces activamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_PER);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x7;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_PER,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_PER) & 0x1) != 0x1);

                        break;

                case DISP_PLL:
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_DISP);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x4;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_DISP,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_DISP) & 0x100) != 0x100);

                        clk_sel = _READ_32(CKM_WKUP + CKM_CLKSEL_DPLL_DISP);
                        clk_sel &= ~0x7FFFF; // Tenemos el 1er Byte para Div (en realidad, 7 bits). Y 11 bits para Mult.
                        clk_sel |= (pll_mult << 8)|pll_div;
                        _WRITE_32(CKM_WKUP + CKM_CLKSEL_DPLL_DISP,clk_sel);

                        div = _READ_32(CKM_WKUP + CKM_DIV_M2_DPLL_DISP);
                        div &= ~0x1F;
                        div |= div_m2;
                        _WRITE_32(CKM_WKUP + CKM_DIV_M2_DPLL_DISP,div_m2);

                        // Entonces activamos el DPLL
                        clk_mode = _READ_32(CKM_WKUP + CKM_CLKMODE_DPLL_DISP);
                        clk_mode &= ~0x7;   // Son los últimos 3 bits
                        clk_mode |= 0x7;
                        _WRITE_32(CKM_WKUP + CKM_CLKMODE_DPLL_DISP,clk_mode);
                        // Esperamos a que la configuración se haya efectuado
                        while((_READ_32(CKM_WKUP + CKM_IDLEST_DPLL_DISP) & 0x1) != 0x1);
                        break;

                default:
                    break;
            }

    }

__attribute__((section(".text_pub"))) uint32_t PLL_Get_InputClockFreq(void)
    {
        uint32_t input_freq = 0;

        input_freq = _READ_32(CM_BASE_DIR + CM_control_status) >> 22;
        input_freq &= 0x3;  // Hacemos una máscara para quedarnos con el valor de frec. de entrada

        switch(input_freq)
            {
                case 0:
                    return 19;  // 19.2 MHz
                    break;
                case 1:
                    return 24;  // 24 MHz
                    break;
                case 2:
                    return 25;  // 25 MHz
                    break;
                case 3:
                    return 26;  // 26 MHz
                    break;
                default:
                    return -1;
                    break;
            }        
    }