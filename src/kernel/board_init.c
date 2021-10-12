#include "../../inc/utils/types.h"
#include "../../inc/board/uart.h"
#include "../../inc/utils/system_utils.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/board/led.h"
#include "../../inc/board/pll.h"
#include "../../inc/board/ddr.h"
#include "../../inc/irq/timertick.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/board/i2c.h"
#include "../../inc/board/tps65217.h"
#include "../../inc/board/switch.h"
#include "../../inc/kernel/board_init.h"
#include "../../inc/utils/mmu_config.h"
#include "../../inc/utils/memcopy.h"
#include "../../inc/utils/mmu_tools.h"

/* Definitions in linker script */
// Kernel
extern const void _HANDLERS_LMA;
extern const void _DDR0_INIT;
extern const void _kernel_handler_size_;

extern const void _TEXT_KERNEL_LMA;
extern const void _TEXT_KERNEL_VMA;
extern const void _kernel_text_size_;

extern const void _BSS_KERNEL_LMA;
extern const void _BSS_KERNEL_VMA;
extern const void _kernel_bss_size_;

extern const void _DATA_KERNEL_LMA;
extern const void _DATA_KERNEL_VMA;
extern const void _kernel_data_size_;

// Table pagination Kernel
extern const void _TABLE_PAGINATION_LMA;
extern const void _TABLE_PAGINATION_VMA;
extern const void _kernel_table_size_;

// Table pagination TASK0
extern const void _TABLE_PAGINATION_TASK0_PUBLIC_RAM;
extern const void _TABLE_PAGINATION_TASK0_RAM;
extern const void _kernel_table_task0_size_;
// Table pagination TASK1
extern const void _TABLE_PAGINATION_TASK1_PUBLIC_RAM;
extern const void _TABLE_PAGINATION_TASK1_RAM;
extern const void _kernel_table_task1_size_;
// Table pagination TASK2
extern const void _TABLE_PAGINATION_TASK2_PUBLIC_RAM;
extern const void _TABLE_PAGINATION_TASK2_RAM;
extern const void _kernel_table_task2_size_;
// Table pagination TASK3
extern const void _TABLE_PAGINATION_TASK3_PUBLIC_RAM;
extern const void _TABLE_PAGINATION_TASK3_RAM;
extern const void _kernel_table_task3_size_;

/* Task 0 */
extern const void _TEXT_TASK0_PUBLIC_RAM;
extern const void _TEXT_TASK0_RAM;
extern const void _BSS_TASK0_PUBLIC_RAM;
extern const void _BSS_TASK0_RAM;
extern const void _DATA_TASK0_PUBLIC_RAM;
extern const void _DATA_TASK0_RAM;
extern const void _STACK_IRQ_TASK0_PUBLIC_RAM;
extern const void _STACK_IRQ_TASK0_RAM;
extern const void _STACK_SYS_TASK0_PUBLIC_RAM;
extern const void _STACK_SYS_TASK0_RAM;
extern const void _STACK_SVC_TASK0_PUBLIC_RAM;
extern const void _STACK_SVC_TASK0_RAM;
extern const void _STACK_UND_TASK0_PUBLIC_RAM;
extern const void _STACK_UND_TASK0_RAM;
extern const void _STACK_ABT_TASK0_PUBLIC_RAM;
extern const void _STACK_ABT_TASK0_RAM;
extern const void kernel_text_task0_size;
extern const void kernel_bss_task0_size;
extern const void kernel_data_task0_size;
extern const void kernel_stack_irq_task0_size;
extern const void kernel_stack_sys_task0_size;
extern const void kernel_stack_svc_task0_size;
extern const void kernel_stack_und_task0_size;
extern const void kernel_stack_abt_task0_size;

/* Task 1 */
extern const void _TEXT_TASK1_PUBLIC_RAM;
extern const void _TEXT_TASK1_RAM;
extern const void _BSS_TASK1_PUBLIC_RAM;
extern const void _BSS_TASK1_RAM;
extern const void _DATA_TASK1_PUBLIC_RAM;
extern const void _DATA_TASK1_RAM;
extern const void _STACK_IRQ_TASK1_PUBLIC_RAM;
extern const void _STACK_IRQ_TASK1_RAM;
extern const void _STACK_SYS_TASK1_PUBLIC_RAM;
extern const void _STACK_SYS_TASK1_RAM;
extern const void _STACK_SVC_TASK1_PUBLIC_RAM;
extern const void _STACK_SVC_TASK1_RAM;
extern const void _STACK_UND_TASK1_PUBLIC_RAM;
extern const void _STACK_UND_TASK1_RAM;
extern const void _STACK_ABT_TASK1_PUBLIC_RAM;
extern const void _STACK_ABT_TASK1_RAM;
extern const void kernel_text_task1_size;
extern const void kernel_bss_task1_size;
extern const void kernel_data_task1_size;
extern const void kernel_stack_irq_task1_size;
extern const void kernel_stack_sys_task1_size;
extern const void kernel_stack_svc_task1_size;
extern const void kernel_stack_und_task1_size;
extern const void kernel_stack_abt_task1_size;

/* Task 2 */
extern const void _TEXT_TASK2_PUBLIC_RAM;
extern const void _TEXT_TASK2_RAM;
extern const void _BSS_TASK2_PUBLIC_RAM;
extern const void _BSS_TASK2_RAM;
extern const void _DATA_TASK2_PUBLIC_RAM;
extern const void _DATA_TASK2_RAM;
extern const void _STACK_IRQ_TASK2_PUBLIC_RAM;
extern const void _STACK_IRQ_TASK2_RAM;
extern const void _STACK_SYS_TASK2_PUBLIC_RAM;
extern const void _STACK_SYS_TASK2_RAM;
extern const void _STACK_SVC_TASK2_PUBLIC_RAM;
extern const void _STACK_SVC_TASK2_RAM;
extern const void _STACK_UND_TASK2_PUBLIC_RAM;
extern const void _STACK_UND_TASK2_RAM;
extern const void _STACK_ABT_TASK2_PUBLIC_RAM;
extern const void _STACK_ABT_TASK2_RAM;
extern const void kernel_text_task2_size;
extern const void kernel_bss_task2_size;
extern const void kernel_data_task2_size;
extern const void kernel_stack_irq_task2_size;
extern const void kernel_stack_sys_task2_size;
extern const void kernel_stack_svc_task2_size;
extern const void kernel_stack_und_task2_size;
extern const void kernel_stack_abt_task2_size;

/* Task 3 */
extern const void _TEXT_TASK3_PUBLIC_RAM;
extern const void _TEXT_TASK3_RAM;
extern const void _BSS_TASK3_PUBLIC_RAM;
extern const void _BSS_TASK3_RAM;
extern const void _DATA_TASK3_PUBLIC_RAM;
extern const void _DATA_TASK3_RAM;
extern const void _STACK_IRQ_TASK3_PUBLIC_RAM;
extern const void _STACK_IRQ_TASK3_RAM;
extern const void _STACK_SYS_TASK3_PUBLIC_RAM;
extern const void _STACK_SYS_TASK3_RAM;
extern const void _STACK_SVC_TASK3_PUBLIC_RAM;
extern const void _STACK_SVC_TASK3_RAM;
extern const void _STACK_UND_TASK3_PUBLIC_RAM;
extern const void _STACK_UND_TASK3_RAM;
extern const void _STACK_ABT_TASK3_PUBLIC_RAM;
extern const void _STACK_ABT_TASK3_RAM;
extern const void kernel_text_task3_size;
extern const void kernel_bss_task3_size;
extern const void kernel_data_task3_size;
extern const void kernel_stack_irq_task3_size;
extern const void kernel_stack_sys_task3_size;
extern const void kernel_stack_svc_task3_size;
extern const void kernel_stack_und_task3_size;
extern const void kernel_stack_abt_task3_size;


extern int main(void);
void board_info_print(BBB_INFO , EFUSE_OPP );
uint32_t board_opp_config(BBB_INFO , EFUSE_OPP );

static const tOPPConfig oppTable[] =
    {
        {MPUPLL_M_275_MHZ, PMIC_VOLT_SEL_1100MV},  /* OPP100 275Mhz - 1.1v */
        {MPUPLL_M_500_MHZ, PMIC_VOLT_SEL_1100MV},  /* OPP100 500Mhz - 1.1v */
        {MPUPLL_M_600_MHZ, PMIC_VOLT_SEL_1200MV},  /* OPP120 600Mhz - 1.2v */
        {MPUPLL_M_720_MHZ, PMIC_VOLT_SEL_1260MV},  /* OPP TURBO 720Mhz - 1.26v */
        {MPUPLL_M_300_MHZ, PMIC_VOLT_SEL_0950MV},  /* OPP50 300Mhz - 950mv */
        {MPUPLL_M_300_MHZ, PMIC_VOLT_SEL_1100MV},  /* OPP100 300Mhz - 1.1v */
        {MPUPLL_M_600_MHZ, PMIC_VOLT_SEL_1100MV},  /* OPP100 600Mhz - 1.1v */
        {MPUPLL_M_720_MHZ, PMIC_VOLT_SEL_1200MV},  /* OPP120 720Mhz - 1.2v */
        {MPUPLL_M_800_MHZ, PMIC_VOLT_SEL_1260MV},  /* OPP TURBO 800Mhz - 1.26v */
        {MPUPLL_M_1000_MHZ, PMIC_VOLT_SEL_1325MV}  /* OPP NITRO 1000Mhz - 1.325v */
    };

__attribute__((section("text_pub")))int init_board(void)
    {   
        uint32_t input_clock_in = 0, board_opp = 0;        
        
        // uint8_t pmic_status = 0;
        BBB_INFO board_info;
        EFUSE_OPP board_opp_info;

        UART_Init(UART_0,115200,STOP_BITS_1,NO_PARITY);

        /* Configurar el GPIO de los LEDs */
        ConsoleUtilsPrintf("\n\r[8.0] Configurando leds de usuario ... ");

        ConsoleUtilsPrintf("\n\r[0.0] Inicializando Beaglebone Black ...");

        // Deshabilitamos las IRQ
        _irq_disable();

        // Obtenemos algo de información para la configuración de la placa
        board_info.bbb_info = _READ_32(CM_BASE_DIR + CM_device_id);
        board_opp_info.efuse_opp = _READ_32(CM_BASE_DIR + CM_efuse_sma);
        board_info_print(board_info,board_opp_info);
        board_opp = board_opp_config(board_info,board_opp_info);
        ConsoleUtilsPrintf("\n\r[0.1] Configuración del punto de operación de rendimiento (OPP): \n\r\tMPU PLL Mult. %d \n\r\tPMIC Volt. 0x%x",oppTable[board_opp].pllMult,oppTable[board_opp].pmicVolt);

        ConsoleUtilsPrintf("\n\r[1.0] Configurando sistemas de clock L3 y L4...");
        Enable_L3_L4_Clock_Systems();    

        // Inicializamos el I2C0 para configurar el PMIC
        ConsoleUtilsPrintf("\n\r[2.0] Configurando I2C0 ...");
        I2C0_Setup();

        ConsoleUtilsPrintf("\n\r[3.0] Configurando PMIC (TPS65217) ...");
        // Configuramos la direccion slave del PMIC en el I2C0
        I2C_Master_SlaveAddrs_Set(I2C0_BASE_ADDR,PMIC_TPS65217_I2C_SLAVE_ADDR);
        
        // Leemos el estado del PMIC
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) Configuración actual: ");
        TPS65217_Power_Status();

        // Aumentamos el limite de corriente del USB
        TPS65217_Write(PROT_LEVEL_NONE,POWER_PATH,USB_INPUT_CUR_LIMIT_1300MA,USB_INPUT_CUR_LIMIT_MASK);

        // Modificamos el valor de tensión del DCDC2 a 1.275 V
        TPS65217_V_Update(DEFDCDC2,DCDC_VOLT_SEL_1275MV);
        // Configuramos para que la salida de LDO3 sea de 3.3 V
        TPS65217_Write(PROT_LEVEL_2, DEFLS1, LDO_VOLTAGE_OUT_3_3, LDO_MASK);
        // Configuramos para que la salida de LDO4 sea de 3.3 V
        TPS65217_Write(PROT_LEVEL_2, DEFLS2, LDO_VOLTAGE_OUT_3_3, LDO_MASK);
        // Configuramos en funcion del Max OPP obtenido más arriba en "board_opp" al valor de tensión de la MPU
        TPS65217_V_Update(DEFDCDC2,oppTable[board_opp].pmicVolt);

        // Visualizamos la nueva configuración del PMIC
        ConsoleUtilsPrintf("\n\n\r\tPMIC (TPS65217) Configuración actualizada. Nuevos valores: ");
        TPS65217_Power_Status();

        ConsoleUtilsPrintf("\n\r[4.0] Verificando frecuencia de clock de entrada ...");
        input_clock_in = PLL_Get_InputClockFreq();
        if(input_clock_in == 24)
            {
                ConsoleUtilsPrintf(" [OK] | f_clk_in = %d MHz",input_clock_in);
                ConsoleUtilsPrintf("\n\r[5.0] Configurando PLLs ...");
                ConsoleUtilsPrintf("\n\r[5.1] \tMPU ...");
                PLL_Config(MPU_PLL,input_clock_in,oppTable[board_opp].pllMult,23,1,0,0,0);
                ConsoleUtilsPrintf(" [OK]");

                ConsoleUtilsPrintf("\n\r[5.2] \tCORE ...");
                PLL_Config(CORE_PLL,input_clock_in,1000,23,0,10,8,4);
                ConsoleUtilsPrintf(" [OK]");

                ConsoleUtilsPrintf("\n\r[5.3] \tDDR ...");
                PLL_Config(DDR_PLL,input_clock_in,400,23,1,0,0,0);
                ConsoleUtilsPrintf(" [OK]");

                ConsoleUtilsPrintf("\n\r[5.4] \tDISP ...");
                PLL_Config(DISP_PLL,input_clock_in,25,3,1,0,0,0);
                ConsoleUtilsPrintf(" [OK]");

                ConsoleUtilsPrintf("\n\r[5.5] \tPER ...");
                PLL_Config(PER_PLL,input_clock_in,960,23,5,0,0,0);
                ConsoleUtilsPrintf(" [OK]");
                ConsoleUtilsPrintf("\n\r");
            }
        else
            {
                ConsoleUtilsPrintf("\n\r\tFrecuencia de clock incorrecta. Se detiene el booteo.");    
                _HALT_CPU();
            }    


        /***********************************************************/
        /*************************** TP1 ***************************/
        /***********************************************************/

        /* Unmask Interrupt */
        NVIC_IRQ_Unmask(GPIOINT2A_IRQn);

        /* SWITCH_init */
        switch_init(SW2,INTERRUPT_SW);

        /* Enable IRQ in CPSR */
        _irq_enable();
        
        /* LED_init */
        LED_init();

        /***********************************************************/

        /***********************************************************/
        /*************************** TP2 ***************************/
        /***********************************************************/
        /* Config DDR */
        ConsoleUtilsPrintf("\n\r[6.0] Configurando memoria DDR3 externa ...");
        DDR3_Init();
        ConsoleUtilsPrintf(" [OK]");
        ConsoleUtilsPrintf("\n\r[6.0] Limpiando memoria DDR3 externa ...");
        Clean_DDR();
        ConsoleUtilsPrintf(" [OK]");

        /* Initialize MMU */
        ConsoleUtilsPrintf("\n\r[7.0] Configurando MMU ...");
        MMU_config();
        ConsoleUtilsPrintf(" [OK]");

        /* Config MMU tables */
        ConsoleUtilsPrintf("\n\r[7.1] Escribiendo las tablas de paginacion ...");
        // Vector de reset y código de inicialización: 64KB
        MMU_Write_Tables(0x402F0400,0x402F0400,0x40300400, TTBR0_KERNEL);
        // Public stack: 64KB
        MMU_Write_Tables(0x40300000,0x40300000,0x40310000, TTBR0_KERNEL);
        // ISR Table
        MMU_Write_Tables(0x4030CE00,0x4030CE00,0x4031CE00, TTBR0_KERNEL);
        // Mapeo desde 0x44000000 a 0x80000000
        MMU_Write_Tables(0x44000000,0x44000000,0x80000000, TTBR0_KERNEL);
        // Handlers de interrupción
        // TEXT Kernel
        // BSS Kernel
        // DATA Kernel
        // Tablas de paginación
        // Mapeo de 0x80000000 a 0x80424000
        MMU_Write_Tables((uint32_t)&_DDR0_INIT,(uint32_t)&_DDR0_INIT,0x80424000, TTBR0_KERNEL);
        ConsoleUtilsPrintf(" [OK]");

        /* Copy LMA to VMA content */
        ConsoleUtilsPrintf("\n\r[7.2] Copiando contenido de LMA a VMA ...");
        memcopy((uint32_t)&_HANDLERS_LMA, (uint32_t)&_DDR0_INIT, (uint32_t)&_kernel_handler_size_);
        memcopy((uint32_t)&_TEXT_KERNEL_LMA, (uint32_t)&_TEXT_KERNEL_VMA, (uint32_t)&_kernel_text_size_);
        memcopy((uint32_t)&_BSS_KERNEL_LMA, (uint32_t)&_BSS_KERNEL_VMA, (uint32_t)&_kernel_bss_size_);
        memcopy((uint32_t)&_DATA_KERNEL_LMA, (uint32_t)&_DATA_KERNEL_VMA, (uint32_t)&_kernel_data_size_);
        memcopy((uint32_t)&_TABLE_PAGINATION_LMA, (uint32_t)&_TABLE_PAGINATION_VMA, (uint32_t)&_kernel_table_size_);
        ConsoleUtilsPrintf(" [OK]");

        /***********************************************************/

        /***********************************************************/
        /*************************** TP3 ***************************/
        /***********************************************************/
        // Páginas de Tareas
        ConsoleUtilsPrintf("\n\r[7.3] Escribiendo las tablas de paginacion de tareas ...");
        // Mapeo tablas de task0 a task3
        // Mapeo de 0x80420000 a 0x80820000
        MMU_Write_Tables((uint32_t)&_TABLE_PAGINATION_TASK0_RAM,(uint32_t)&_TABLE_PAGINATION_TASK0_RAM,0x80820000, TTBR0_TASK0);
        // Mapeo de 0x80820000 a 0x80C20000
        MMU_Write_Tables((uint32_t)&_TABLE_PAGINATION_TASK1_RAM,(uint32_t)&_TABLE_PAGINATION_TASK1_RAM,0x80C20000, TTBR0_TASK1);
        // Mapeo de 0x80C20000 a 0x81020000
        MMU_Write_Tables((uint32_t)&_TABLE_PAGINATION_TASK2_RAM,(uint32_t)&_TABLE_PAGINATION_TASK2_RAM,0x81020000, TTBR0_TASK2);
        // Mapeo de 0x81020000 a 0x81420000
        MMU_Write_Tables((uint32_t)&_TABLE_PAGINATION_TASK3_RAM,(uint32_t)&_TABLE_PAGINATION_TASK3_RAM,0x81420000, TTBR0_TASK3);

        // Table pagination TASKs        
         memcopy((uint32_t)&_TABLE_PAGINATION_TASK0_PUBLIC_RAM, (uint32_t)&_TABLE_PAGINATION_TASK0_RAM, (uint32_t)&_kernel_table_task0_size_);
         memcopy((uint32_t)&_TABLE_PAGINATION_TASK1_PUBLIC_RAM, (uint32_t)&_TABLE_PAGINATION_TASK1_RAM, (uint32_t)&_kernel_table_task1_size_);
         memcopy((uint32_t)&_TABLE_PAGINATION_TASK2_PUBLIC_RAM, (uint32_t)&_TABLE_PAGINATION_TASK2_RAM, (uint32_t)&_kernel_table_task2_size_);
         memcopy((uint32_t)&_TABLE_PAGINATION_TASK3_PUBLIC_RAM, (uint32_t)&_TABLE_PAGINATION_TASK3_RAM, (uint32_t)&_kernel_table_task3_size_);
        ConsoleUtilsPrintf(" [Tablas OK]");

        /* Enable MMU */
        ConsoleUtilsPrintf("\n\r[7.3] Habilitando MMU ...");
        MMU_enable();
        ConsoleUtilsPrintf(" [OK]");

        // Configurando TimerTick
        ConsoleUtilsPrintf("\n\r[8.2] Configurando TimerTick [DMTimer 1ms]...");
        /* 
            Seleccionamos la referencia externa - Este paso es necesario dado que la entrada del 
            clock externo de 32,768 KHz (la entrada de XTALIN) se encuentra en estado de alta impendancia
            e inhabilitada en el mux del RTC. En este paso, lo que hacemos es justamente seleccionar dicha
            entrada en el mux y sacar de alta impedancia al pin de entrada. Eso nos permite que una vez que
            en TimerTick_Init, habilitamos en el CKM_WKUP del TIMER1 la entrada 0x4 (la del cristal externo)
            funcione.
        */
        RTC_Config(0x00000008);     
        // TimerTick_Init(TIMER_1MS_CLK_RC32K_SOURCE);
        TimerTick_Init(TIMER_1MS_CLK_32768_SOURCE);
        
        // Habilitamos las IRQ nuevamente
        _irq_enable();                                
  
        ConsoleUtilsPrintf("\n\n\r[10.0] Lanzando S.O. (main()) ...");
        /***********************************************************/
        
        /* Branch a tu código =) */
        main();

        return 0;
    }

__attribute__((section(".text_pub"))) void board_info_print(BBB_INFO board_info, EFUSE_OPP bord_opp_info)
{   
    ConsoleUtilsPrintf("\n\r\t Información del hardware: ");
    ConsoleUtilsPrintf("\n\r\t JTAG ID: %d | 0x%x",board_info.mfgr,board_info.mfgr);
    ConsoleUtilsPrintf("\n\r\t Part Number: %d | 0x%x",board_info.partnum,board_info.partnum);
    if(board_info.devrev == 0x2)
        {
        ConsoleUtilsPrintf("\n\r\t Revisión del silicio: 2.1 | 0x%x",board_info.devrev);
        }
    else
        {
        ConsoleUtilsPrintf("\n\r\t Revisión del silicio: %d | 0x%x",board_info.devrev,board_info.devrev);
        }

    ConsoleUtilsPrintf("\n\r\t Package_type 0x%x",bord_opp_info.pkg_type);
    switch(bord_opp_info.pkg_type)
        {   
        case 0x0:
            ConsoleUtilsPrintf("\n\r\t Package_type: Undefined");
            break;
        case 0x1:
            ConsoleUtilsPrintf("\n\r\t Package_type: ZCZ");
            break;
        case 0x2:
            ConsoleUtilsPrintf("\n\r\t Package_type: ZCE");
            break;
        case 0x3:
            ConsoleUtilsPrintf("\n\r\t Package_type: Reservado");
            break;
        }

    ConsoleUtilsPrintf("\n\r\t Freq. 0x%x",bord_opp_info.arm_mpu_max_freq);
    switch(bord_opp_info.arm_mpu_max_freq)
        {   
        case 0x1FEF:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 300 MHz");
            break;
        case 0x1FAF:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 600 MHz");
            break;
        case 0x1F2F:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 720 MHz");
            break;
        case 0x1E2F:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 800 MHz");
            break;
        case 0x1C2F:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 1 GHz");
            break;
        case 0x1FDF:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 300 MHz");
            break;   
        case 0x1F9F:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: 600 MHz");
            break;
        default:
            ConsoleUtilsPrintf("\n\r\t Frecuencia máxima soportada del procesador: reservado");
            break;                                  
        }

}
__attribute__((section(".text_pub")))uint32_t board_opp_config(BBB_INFO board_info, EFUSE_OPP bord_opp_info)
    {   
        uint32_t value = 0;
        
        switch(board_info.devrev)
            {   
            case 0x0:
                value = EFUSE_OPPTB_720;
                break;
            case 0x1:
                value = EFUSE_OPPTB_800;
                break;
            case 0x2:
                if(!(bord_opp_info.arm_mpu_max_freq & EFUSE_OPPNT_1000_MASK))
                    {
                    value = EFUSE_OPPNT_1000;
                    }
                else 
                    {
                    if(!(bord_opp_info.arm_mpu_max_freq & EFUSE_OPPTB_800_MASK))
                        {
                        value = EFUSE_OPPTB_800;
                        }                    
                    else 
                        {
                        if(!(bord_opp_info.arm_mpu_max_freq & EFUSE_OPP120_720_MASK))
                            {
                                value = EFUSE_OPP120_720;
                            }
                        else
                            { 
                            if(!(bord_opp_info.arm_mpu_max_freq & EFUSE_OPP100_600_MASK))
                                {
                                    value = EFUSE_OPP100_600;
                                }
                            else 
                                {
                                if(!(bord_opp_info.arm_mpu_max_freq & EFUSE_OPP100_300_MASK))
                                    {
                                        value = EFUSE_OPP100_300;
                                    }
                                else
                                    {
                                        value = EFUSE_OPP50_300;
                                    }
                                }
                            }
                        }
                    }
                break;
            default:
                value = -1;
                break;
            }
        return value;      
    }
