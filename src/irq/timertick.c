

#include "../../inc/utils/types.h"
#include "../../inc/utils/clock_modules.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/timertick.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/utils/console_utils.h"

void TimerTick_Init(uint32_t);
void TimerTick_Start(void);
void Enable_L3_L4_Clock_Systems(void);
void RTC_Config(uint32_t );

// Usamos el DMTimer 1ms (Timer 1) - TRM - 20.2
__attribute__((section(".text_pub")))void TimerTick_Init(uint32_t clk_source)
    {   
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init ...");
        uint32_t config = 0;
        uint32_t irq_addrs = 0;

        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));  

        // Configuramos el DPLL
        config = _READ_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK);
        config &= ~0x00000007;                                           // Nos quedamos con los 3 bis menos significativos
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - [CKM_DPLL_CLKSEL_TIMER1MS_CLK] 0x%x",config);
        _WRITE_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK, config);
        // Confirmamos que quede configurado
        while( (_READ_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK) & 0x00000007) != 0x0);

        config = _READ_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK);
        config &= ~0x00000007;                                           // Nos quedamos con los 3 bis menos significativos
        config |= clk_source;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - [CKM_DPLL_CLKSEL_TIMER1MS_CLK] 0x%x",config);
        _WRITE_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK, config);
        // Confirmamos que quede configurado
        while( (_READ_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK) & 0x00000007) != clk_source);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - [CKM_DPLL_CLKSEL_TIMER1MS_CLK] 0x%x",_READ_32(CKM_DPLL + CKM_DPLL_CLKSEL_TIMER1MS_CLK));
       
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));   

        // Habilitamos el módulo
        config = _READ_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - 1) [CKM_WKUP_TIMER1_CLKCTRL] 0x%x",config);
        config &= ~0x00000003;
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - 2) [CKM_WKUP_TIMER1_CLKCTRL] 0x%x",config);
        _WRITE_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL, config);
        // Confirmamos que quede configurado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - 3) [CKM_WKUP_TIMER1_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL));
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - 4) [CKM_WKUP_TIMER1_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL) & 0x3);
        while( (_READ_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL) & 0x3) != 0x2);

        // Ahora leemos que efectivamente esté "fully functional" bits [17:16] del registro 0xC4
        while( (_READ_32(CKM_WKUP + CKM_WKUP_TIMER1_CLKCTRL) & 0x00030000) != 0x0);

        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - [CKM_WKUP_CLKSTCTRL] 0x%x\n",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));
        // Seteo de prioridad (queremos que interrumpa prioritariamente frente a otro evento externo para nuestro mini S.O.)
        irq_addrs = TINT1_1MS_IRQn*0x4 + 0x100;     // TRM 6.5.1.44 - Calculamos a partir del mapa de memoria, el offset que
                                                    // para configurar la prioridad de esta IRQ. Además, en caso de que el uP
                                                    // lo soporte, se puede definir si va por IRQ o por FIQ. En el caso de la BBB
                                                    // sale solo por IRQ.
        config = _READ_32(NVIC + irq_addrs);
        config &= ~0x0000000F;
        config |= 0x0;                              // Prioridad 0 (la máxima) y routeo por IRQ - TRM 6.5.1.44
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [config] - [0x%x] 0x%x",NVIC + irq_addrs,config);
        _WRITE_32(NVIC + irq_addrs,config);

        // Habilitamos esta IRQ (desenmascaramos :))
        NVIC_IRQ_Unmask(TINT1_1MS_IRQn);

        /* 
            En este paso, ya podríamos agregar el puntero al manejador de nuestra IRQ,
            el cual ya fue creado previamente en nvic_handlers.c. En ese lugar, es necesario
            escribir la rutina de dicho manejador (tal como hicieron para el S2, TP1)
        */
       
        // Habilitamos la interrupción por overflow
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TIER,0x2);
        // Configuramos el contador - TRM 20.2.3.1.1
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TCRR,0xFFFFFFE0);
        // Configuramos el valor de recarga - TRM 20.2.3.1.1
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TLDR,0xFFFFFFE0);      // 0xFFFF9000 interrumpe cada 1 seg
        // Configuramos los registros de incremento positivo y negativo - TRM 20.2.3.1.1
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TPIR,0x38A40);      // 232000
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TNIR,0xFFF44800);     // -768000 (en palabras de 32 bits)

        // Listo!
    }

__attribute__((section(".text_pub"))) void TimerTick_Start(void)
    {
        _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TCLR,0x3);
    }

__attribute__((section(".text_pub"))) void RTC_Config(uint32_t clk_source)
    {   
        uint32_t config = 0;

        // Deshabilitamos la proteccion de escritura de los registros del RTC
        _WRITE_32(RTC_BASE_ADDR + RTC_KICK0,RTC_KICK0R_KEY);
        _WRITE_32(RTC_BASE_ADDR + RTC_KICK1,RTC_KICK1R_KEY);

        // Configuramos para usar la referencia externa del RTC
        config = _READ_32(RTC_BASE_ADDR + RTC_OSC);             // TRM 20.3.5.19
        config &= ~0x00000008;
        _WRITE_32(RTC_BASE_ADDR + RTC_OSC,config);              // Limpiamos el registro y usamos el source deseado

        config = _READ_32(RTC_BASE_ADDR + RTC_OSC);
        config |= clk_source;
        _WRITE_32(RTC_BASE_ADDR + RTC_OSC,config);

        if (clk_source == 0x00000008)       // Es decir, si se selecciona la referencia externa: SEL_32KCLK_SRC = 1
            {
                config = _READ_32(RTC_BASE_ADDR + RTC_OSC);     
                config &= ~0x00000010;                          // Tenemos que sacar del estado de alta impedancia a OSC32K_GZ
                config |= 0x000000000;
                _WRITE_32(RTC_BASE_ADDR + RTC_OSC,config);    
            }

        // Habilitamos que el RTC reciba esas entradas de clock
        config = _READ_32(RTC_BASE_ADDR + RTC_OSC);
        config &= ~0x00000040;
        _WRITE_32(RTC_BASE_ADDR + RTC_OSC,config);

        config = _READ_32(RTC_BASE_ADDR + RTC_OSC);
        config |= 0x00000040;
        _WRITE_32(RTC_BASE_ADDR + RTC_OSC,config);
    }

__attribute__((section(".text_pub"))) void Enable_L3_L4_Clock_Systems(void)
    {   
        uint32_t config = 0;

        /*
            Configuración de Clocks
        */
        // L3
        config = _READ_32(CKM_PER + CKM_PER_L3_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_CLKCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L3_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L3_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
       //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_CLKCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_INSTR_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL,config);                      // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL) & 0x3) != 0x2);     // Esperamos a que esté habilitad
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_INSTR_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L3_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_CLKSTCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L3_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L3_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3_CLKSTCTRL));

        config = _READ_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_OCPWP_L3_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL));
        _WRITE_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL, config);                    // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_OCPWP_L3_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3S_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3S_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL));

        // Ahora esperamos que efectivamente se vean reflejadas las configuraciones anteriores:
        while((_READ_32(CKM_PER + CKM_PER_L3_CLKCTRL) & 0x00030000) != 0x0);
        while((_READ_32(CKM_PER + CKM_PER_L3_INSTR_CLKCTRL) & 0x00030000) != 0x0);
        while((_READ_32(CKM_PER + CKM_PER_L3_CLKSTCTRL) & 0x00000010) != 0x10);
        while((_READ_32(CKM_PER + CKM_PER_OCPWP_L3_CLKSTCTRL) & 0x00000010) != 0x10);
        while((_READ_32(CKM_PER + CKM_PER_L3S_CLKSTCTRL) & 0x00000008) != 0x8);

        // L4
        config = _READ_32(CKM_PER + CKM_PER_L4LS_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4LS_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4LS_CLKCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L4LS_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L4LS_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L3S_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4LS_CLKCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L4FW_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4FW_CLKCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L4FW_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L4FW_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4FW_CLKCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L4HS_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4HS_CLKCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L4HS_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L4HS_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4HS_CLKCTRL));

        config = _READ_32(CKM_PER + CKM_PER_L4LS_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4LS_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4LS_CLKSTCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L4LS_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L4LS_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4LS_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4LS_CLKSTCTRL));
       
        config = _READ_32(CKM_PER + CKM_PER_L4FW_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4FW_CLKSTCTRL));
        _WRITE_32(CKM_PER + CKM_PER_L4FW_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_PER + CKM_PER_L4FW_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_PER_L4FW_CLKSTCTRL] 0x%x",_READ_32(CKM_PER + CKM_PER_L4FW_CLKSTCTRL));
       
        /*
            Clock WKUP
        */

        config = _READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CONTROL_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL));
        _WRITE_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CONTROL_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL));        

        config = _READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));
        _WRITE_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));      

        config = _READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_L3_AON_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL));
        _WRITE_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_L3_AON_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL));      

        config = _READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL);
        config |= 0x2;
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_L4WKUP_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL));
        _WRITE_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL,config);                     // Habilitamos el módulo
        while((_READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL) & 0x3) != 0x2);       // Esperamos a que esté habilitado
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_L4WKUP_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL));        


        // Ahora esperamos que efectivamente se vean reflejadas las configuraciones anteriores:
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CONTROL_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL));   
        while((_READ_32(CKM_WKUP + CKM_WKUP_CONTROL_CLKCTRL) & 0x00030000) != 0x0);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_L3_AON_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL));   
        while((_READ_32(CKM_WKUP + CKM_L3_AON_CLKSTCTRL) & 0x00000008) != 0x8);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_L4WKUP_CLKCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL));   
        while((_READ_32(CKM_WKUP + CKM_WKUP_L4WKUP_CLKCTRL) & 0x00030000) != 0x0);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_WKUP_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL));   
        while((_READ_32(CKM_WKUP + CKM_WKUP_CLKSTCTRL) & 0x00000004) != 0x4);
        //ConsoleUtilsPrintf("\n\rDentro de TimerTick_Init [CLK_Interface] - [CKM_L4_WKUP_AON_CLKSTCTRL] 0x%x",_READ_32(CKM_WKUP + CKM_L4_WKUP_AON_CLKSTCTRL));   
        while((_READ_32(CKM_WKUP + CKM_L4_WKUP_AON_CLKSTCTRL) & 0x00000004) != 0x4);
        

    }



