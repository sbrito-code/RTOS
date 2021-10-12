/**
 * Archivo: nvic_handlers.h
 * Función: definiciones para el uso del nvic_handlers.c
 * Autores: Brito Sergio Sebastian
 **/

#include "../utils/types.h"

// Ver TRM 6.5.1 - Registros del Controlador de Interrupciones
#define EMUINT_IRQn                       (0)
#define COMMTX_IRQn                       (1)
#define COMMRX_IRQn                       (2)
#define BENCH_IRQn                        (3)
#define ELM_IRQ_IRQn                      (4)
#define NMI_IRQn                          (7)
#define L3DEBUG_IRQn                      (9)
#define L3APPINT_IRQn                     (10)
#define PRCMINT_IRQn                      (11)
#define EDMACOMPINT_IRQn                  (12)
#define EDMAMPERR_IRQn                    (13)
#define EDMAERRINT_IRQn                   (14)
#define ADC_TSC_GENINT_IRQn               (16)
#define USNSSINT_IRQn                     (17)
#define USBINT0_IRQn                      (18)
#define USBINT1_IRQn                      (19)
#define PRU_ICSS_EVTOUT0_IRQn             (20)
#define PRU_ICSS_EVTOUT1_IRQn             (21)
#define PRU_ICSS_EVTOUT2_IRQn             (22)
#define PRU_ICSS_EVTOUT3_IRQn             (23)
#define PRU_ICSS_EVTOUT4_IRQn             (24)
#define PRU_ICSS_EVTOUT5_IRQn             (25)
#define PRU_ICSS_EVTOUT6_IRQn             (26)
#define PRU_ICSS_EVTOUT7_IRQn             (27)
#define MMCSD1INT_IRQn                    (28)
#define MMCSD2INT_IRQn                    (29)
#define I2C2INT_IRQn                      (30)
#define eCAP0INT_IRQn                     (31)
#define GPIOINT2A_IRQn                    (32)
#define GPIOINT2B_IRQn                    (33)
#define USBWAKEUP_IRQn                    (34)
#define LCDCINT_IRQn                      (36)
#define GFXINT_IRQn                       (37)
#define ePWM2INT_IRQn                     (39)
#define THRESH_PULSE_3PGSWRXTHR0_IRQn     (40)
#define RX_PULSE_3PGSWRXINT0_IRQn         (41)
#define TX_PULSE_3PGSWTXINT0_IRQn         (42)
#define MISC_PULSE_3PGSWMISC0_IRQn        (43)
#define UART3INT_IRQn                     (44)
#define UART4INT_IRQn                     (45)
#define UART5INT_IRQn                     (46)
#define eCAP1INT_IRQn                     (47)
#define DCAN0_INT0_IRQn                   (52)
#define DCAN0_INT1_IRQn                   (53)
#define DCAN0PARITY_IRQn                  (54)
#define DCAN1_INT0_IRQn                   (55)
#define DCAN1_INT1_IRQn                   (56)
#define DCAN1PARITY_IRQn                  (57)
#define ePWM0_TZINT_IRQn                  (58)
#define ePWM1_TZINT_IRQn                  (59)
#define ePWM2_TZINT_IRQn                  (60)
#define eCAP2INT_IRQn                     (61)
#define GPIOINT3A_IRQn                    (62)
#define GPIOINT3B_IRQn                    (63)
#define MMCSD0INT_IRQn                    (64)
#define McSPI0INT_IRQn                    (65)
#define TINT0_IRQn                        (66)
#define TINT1_1MS_IRQn                    (67)
#define TINT2_IRQn                        (68)
#define TINT3_IRQn                        (69)
#define I2C0INT_IRQn                      (70)
#define I2C1INT_IRQn                      (71)
#define UART0INT_IRQn                     (72)
#define UART1INT_IRQn                     (73)
#define UART2INT_IRQn                     (74)
#define RTCINT_IRQn                       (75)
#define RTCALARMINT_IRQn                  (76)
#define MBINT0_IRQn                       (77)
#define M3_TXEV_IRQn                      (78)
#define eQEP0INT_IRQn                     (79)
#define MCATXINT0_IRQn                    (80)
#define MCARXINT0_IRQn                    (81)
#define MCATXINT1_IRQn                    (82)
#define MCARXINT1_IRQn                    (83)
#define ePWM0INT_IRQn                     (86)
#define ePWM1INT_IRQn                     (87)
#define eQEP1INT_IRQn                     (88)
#define eQEP2INT_IRQn                     (89)
#define DMA_INTR_PIN2_IRQn                (90)
#define WDT1INT_IRQn                      (91)
#define TINT4_IRQn                        (92)
#define TINT5_IRQn                        (93)
#define TINT6_IRQn                        (94)
#define TINT7_IRQn                        (95)
#define GPIOINT0A_IRQn                    (96)
#define GPIOINT0B_IRQn                    (97)
#define GPIOINT1A_IRQn                    (98)
#define GPIOINT1B_IRQn                    (99)
#define GPMCINT_IRQn                      (100)
#define DDRERR0_IRQn                      (101)
#define TCERRINT0_IRQn                    (112)
#define TCERRINT1_IRQn                    (113)
#define TCERRINT2_IRQn                    (114)
#define ADC_TSC_PENINT_IRQn               (115)
#define SMRFLX_MPU_IRQn                   (120)
#define SMRFLX_Core_IRQn                  (121)
#define DMA_INTR_PIN0_IRQn                (123)
#define DMA_INTR_PIN1_IRQn                (124)
#define McSPI1INT_IRQn                    (125)

// Registros de control del NVIC
#define INTC_REVISION           0x0
#define INTC_SYSCONFIG          0x10
#define INTC_SYSSTATUS          0x14
#define INTC_SIR_IRQ            0x40
#define INTC_SIR_FIQ            0x44
#define INTC_CONTROL            0x48
#define INTC_PROTECTION         0x4C
#define INTC_IDLE               0x50
#define INTC_IRQ_PRIORITY       0x60
#define INTC_FIQ_PRIORITY       0x64
#define INTC_THRESHOLD          0x68
#define INTC_ITR0               0x80
#define INTC_MIR0               0x84
#define INTC_MIR_CLEAR0         0x88
#define INTC_MIR_SET0           0x8C
#define INTC_ISR_SET0           0x90
#define INTC_ISR_CLEAR0         0x94
#define INTC_PENDING_IRQ0       0x98
#define INTC_PENDING_FIQ0       0x9C
#define INTC_ITR1               0xA0
#define INTC_MIR1               0xA4
#define INTC_MIR_CLEAR1         0xA8
#define INTC_MIR_SET1           0xAC
#define INTC_ISR_SET1           0xB0
#define INTC_ISR_CLEAR1         0xB4
#define INTC_PENDING_IRQ1       0xB8
#define INTC_PENDING_FIQ1       0xBC
#define INTC_ITR2               0xC0
#define INTC_MIR2               0xC4
#define INTC_MIR_CLEAR2         0xC8
#define INTC_MIR_SET2           0xCC
#define INTC_ISR_SET2           0xD0
#define INTC_ISR_CLEAR2         0xD4
#define INTC_PENDING_IRQ2       0xD8
#define INTC_PENDING_FIQ2       0xDC
#define INTC_ITR3               0xE0
#define INTC_MIR3               0xE4
#define INTC_MIR_CLEAR3         0xE8
#define INTC_MIR_SET3           0xEC
#define INTC_ISR_SET3           0xF0
#define INTC_ISR_CLEAR3         0xF4
#define INTC_PENDING_IRQ3       0xF8
#define INTC_PENDING_FIQ3       0xFC



#define NVIC_MIR_0                      0
#define NVIC_MIR_1                      1
#define NVIC_MIR_2                      2
#define NVIC_MIR_3                      3

#define NVIC   0x48200000                           // Ver TRM 2.1 - Tabla 2-3 (L4_PER), pag. 161

extern uint32_t (* IRQ_Vectors[128])(void);

extern void NVICConfig(void);
extern void NVIC_IRQ_Unmask(uint32_t );
extern uint32_t procIrqHandler(uint32_t);
void NVIC_Install_IRQ_Handler(void* ,uint32_t );