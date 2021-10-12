/**
 * Archivo: clock_module.h
 * Función: archivo de definiciones para el uso del módulo de clock (TRM 8)
 * Autores: Brito Sergio Sebastian
 **/


#ifndef __CLOCK_MODULE_H
#define __CLOCK_MODULE_H

/**
 * Clock Modules Registers y offsets (TRM 8.1.12)
 **/

#define CKM_PER_L4LS_CLKSTCTRL        0x000
#define CKM_PER_L3S_CLKSTCTRL         0x004
#define CKM_PER_L4FW_CLKSTCTRL        0x008
#define CKM_PER_L3_CLKSTCTRL          0x00C
#define CKM_PER_CPGMAC0_CLKCTRL       0x014
#define CKM_PER_LCDC_CLKCTRL          0x018
#define CKM_PER_USB0_CLKCTRL          0x01C
#define CKM_PER_TPTC0_CLKCTRL         0x024
#define CKM_PER_EMIF_CLKCTRL          0x028
#define CKM_PER_OCMCRAM_CLKCTRL       0x02C
#define CKM_PER_GPMC_CLKCTRL          0x030
#define CKM_PER_MCASP0_CLKCTRL        0x034
#define CKM_PER_UART5_CLKCTRL         0x038
#define CKM_PER_MMC0_CLKCTRL          0x03C
#define CKM_PER_ELM_CLKCTRL           0x040
#define CKM_PER_I2C2_CLKCTRL          0x044
#define CKM_PER_I2C1_CLKCTRL          0x048
#define CKM_PER_SPI0_CLKCTRL          0x04C
#define CKM_PER_SPI1_CLKCTRL          0x050
#define CKM_PER_L4LS_CLKCTRL          0x060
#define CKM_PER_L4FW_CLKCTRL          0x064
#define CKM_PER_MCASP1_CLKCTRL        0x068
#define CKM_PER_UART1_CLKCTRL         0x06C
#define CKM_PER_UART2_CLKCTRL         0x070
#define CKM_PER_UART3_CLKCTRL         0x074
#define CKM_PER_UART4_CLKCTRL         0x078
#define CKM_PER_TIMER7_CLKCTRL        0x07C
#define CKM_PER_TIMER2_CLKCTRL        0x080
#define CKM_PER_TIMER3_CLKCTRL        0x084
#define CKM_PER_TIMER4_CLKCTRL        0x088
#define CKM_PER_GPIO1_CLKCTRL         0x0AC
#define CKM_PER_GPIO2_CLKCTRL         0x0B0
#define CKM_PER_GPIO3_CLKCTRL         0x0B4
#define CKM_PER_TPCC_CLKCTRL          0x0BC
#define CKM_PER_DCAN0_CLKCTRL         0x0C0
#define CKM_PER_DCAN1_CLKCTRL         0x0C4
#define CKM_PER_EPWMSS1_CLKCTRL       0x0CC
#define CKM_PER_EMIF_FW_CLKCTRL       0x0D0
#define CKM_PER_EPWMSS0_CLKCTRL       0x0D4
#define CKM_PER_EPWMSS2_CLKCTRL       0x0D8
#define CKM_PER_L3_INSTR_CLKCTRL      0x0DC
#define CKM_PER_L3_CLKCTRL            0x0E0
#define CKM_PER_IEEE5000_CLKCTRL      0x0E4
#define CKM_PER_PRU_ICSS_CLKCTRL      0x0E8
#define CKM_PER_TIMER5_CLKCTRL        0x0EC
#define CKM_PER_TIMER6_CLKCTRL        0x0F0
#define CKM_PER_MMC1_CLKCTRL          0x0F4
#define CKM_PER_MMC2_CLKCTRL          0x0F8
#define CKM_PER_TPTC1_CLKCTRL         0x0FC
#define CKM_PER_TPTC2_CLKCTRL         0x100
#define CKM_PER_SPINLOCK_CLKCTRL      0x10C
#define CKM_PER_MAILBOX0_CLKCTRL      0x110
#define CKM_PER_L4HS_CLKSTCTRL        0x11C
#define CKM_PER_L4HS_CLKCTRL          0x120
#define CKM_PER_OCPWP_L3_CLKSTCTRL    0x12C
#define CKM_PER_OCPWP_CLKCTRL         0x130
#define CKM_PER_PRU_ICSS_CLKSTCTRL    0x140
#define CKM_PER_CPSW_CLKSTCTRL        0x144
#define CKM_PER_LCDC_CLKSTCTRL        0x148
#define CKM_PER_CLKDIV32K_CLKCTRL     0x14C
#define CKM_PER_CLK_24MHZ_CLKSTCTRL   0x150
   

#define CKM_WKUP_CLKSTCTRL            0x00
#define CKM_WKUP_CONTROL_CLKCTRL      0x04
#define CKM_WKUP_GPIO0_CLKCTRL        0x08
#define CKM_WKUP_L4WKUP_CLKCTRL       0x0C
#define CKM_WKUP_TIMER0_CLKCTRL       0x10
#define CKM_WKUP_DEBUGSS_CLKCTRL      0x14
#define CKM_L3_AON_CLKSTCTRL          0x18
#define CKM_AUTOIDLE_DPLL_MPU         0x1C
#define CKM_IDLEST_DPLL_MPU           0x20
#define CKM_SSC_DELTAMSTEP_DPLL_MPU   0x24
#define CKM_SSC_MODFREQDIV_DPLL_MPU   0x28
#define CKM_CLKSEL_DPLL_MPU           0x2C
#define CKM_AUTOIDLE_DPLL_DDR         0x30
#define CKM_IDLEST_DPLL_DDR           0x34
#define CKM_SSC_DELTAMSTEP_DPLL_DDR   0x38
#define CKM_SSC_MODFREQDIV_DPLL_DDR   0x3C
#define CKM_CLKSEL_DPLL_DDR           0x40
#define CKM_AUTOIDLE_DPLL_DISP        0x44
#define CKM_IDLEST_DPLL_DISP          0x48
#define CKM_SSC_DELTAMSTEP_DPLL_DISP  0x4C
#define CKM_SSC_MODFREQDIV_DPLL_DISP  0x50
#define CKM_CLKSEL_DPLL_DISP          0x54
#define CKM_AUTOIDLE_DPLL_CORE        0x58
#define CKM_IDLEST_DPLL_CORE          0x5C
#define CKM_SSC_DELTAMSTEP_DPLL_CORE  0x60
#define CKM_SSC_MODFREQDIV_DPLL_CORE  0x64
#define CKM_CLKSEL_DPLL_CORE          0x68
#define CKM_AUTOIDLE_DPLL_PER         0x6C
#define CKM_IDLEST_DPLL_PER           0x70
#define CKM_SSC_DELTAMSTEP_DPLL_PER   0x74
#define CKM_SSC_MODFREQDIV_DPLL_PER   0x78
#define CKM_CLKDCOLDO_DPLL_PER        0x7C
#define CKM_DIV_M4_DPLL_CORE          0x80
#define CKM_DIV_M5_DPLL_CORE          0x84
#define CKM_CLKMODE_DPLL_MPU          0x88
#define CKM_CLKMODE_DPLL_PER          0x8C
#define CKM_CLKMODE_DPLL_CORE         0x90
#define CKM_CLKMODE_DPLL_DDR          0x94
#define CKM_CLKMODE_DPLL_DISP         0x98
#define CKM_CLKSEL_DPLL_PER           0x9C
#define CKM_DIV_M2_DPLL_DDR           0xA0
#define CKM_DIV_M2_DPLL_DISP          0xA4
#define CKM_DIV_M2_DPLL_MPU           0xA8
#define CKM_DIV_M2_DPLL_PER           0xAC
#define CKM_WKUP_WKUP_M3_CLKCTRL      0xB0
#define CKM_WKUP_UART0_CLKCTRL        0xB4
#define CKM_WKUP_I2C0_CLKCTRL         0xB8
#define CKM_WKUP_ADC_TSC_CLKCTRL      0xBC
#define CKM_WKUP_SMARTREFLEX0_CLKCTRL 0xC0
#define CKM_WKUP_TIMER1_CLKCTRL       0xC4
#define CKM_WKUP_SMARTREFLEX1_CLKCTRL 0xC8
#define CKM_L4_WKUP_AON_CLKSTCTRL     0xCC
#define CKM_WKUP_WDT1_CLKCTRL         0xD4
#define CKM_DIV_M6_DPLL_CORE          0xD8

#define CKM_DPLL_CLKSEL_TIMER7_CLK          0x4
#define CKM_DPLL_CLKSEL_TIMER2_CLK          0x8
#define CKM_DPLL_CLKSEL_TIMER3_CLK          0xC
#define CKM_DPLL_CLKSEL_TIMER4_CLK          0x10
#define CKM_DPLL_CM_MAC_CLKSEL              0x14
#define CKM_DPLL_CLKSEL_TIMER5_CLK          0x18
#define CKM_DPLL_CLKSEL_TIMER6_CLK          0x1C
#define CKM_DPLL_CM_CPTS_RFT_CLKSEL         0x20
#define CKM_DPLL_CLKSEL_TIMER1MS_CLK        0x28
#define CKM_DPLL_CLKSEL_GFX_FCLK            0x2C
#define CKM_DPLL_CLKSEL_PRU_ICSS_OCP_CLK    0x30
#define CKM_DPLL_CLKSEL_LCDC_PIXEL_CLK      0x34
#define CKM_DPLL_CLKSEL_WDT1_CLK            0x38
#define CKM_DPLL_CLKSEL_GPIO0_DBCLK         0x3C


/**
 * Direcciones base de los Clock Modules (TRM - 2.1)
 **/

#define CKM_PER     0x44E00000
#define CKM_WKUP    0x44E00400
#define CKM_DPLL    0x44E00500
#define CKM_MPU     0x44E00600
#define CKM_DEVICE  0x44E00700
#define CKM_RTC     0x44E00800
#define CKM_GFX     0X44E00900
#define CKM_CEFUSE  0X44E00A00



#endif /* defined(__CLOCK_MODULE_H) */
