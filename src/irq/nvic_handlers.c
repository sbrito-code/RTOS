/**
 * Archivo: nvic_handlers.c
 * Función: manejadores de interrupciones
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
 * 
 *             Este código es copia explícita del desarrollado por: Ref. 1, archivo: proc_handlers.c
 **/

#include "../../inc/utils/types.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/debug_tools.h"

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

WEAK void IntDefaultHandler(void);

void EMUINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void COMMTX_IRQHandler(void) ALIAS(IntDefaultHandler);
void COMMRX_IRQHandler(void) ALIAS(IntDefaultHandler);
void BENCH_IRQHandler(void) ALIAS(IntDefaultHandler);
void ELM_IRQ_IRQHandler(void) ALIAS(IntDefaultHandler);
void NMI_IRQHandler(void) ALIAS(IntDefaultHandler);
void L3DEBUG_IRQHandler(void) ALIAS(IntDefaultHandler);
void L3APPINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRCMINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void EDMACOMPINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void EDMAMPERR_IRQHandler(void) ALIAS(IntDefaultHandler);
void EDMAERRINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_TSC_GENINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void USNSSINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void USBINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USBINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT1_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT2_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT3_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT4_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT5_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT6_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void PRU_ICSS_EVTOUT7_IRQHandler_IRQHandler(void) ALIAS(IntDefaultHandler);
void MMCSD1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void MMCSD2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void eCAP0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT2A_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT2B_IRQHandler(void) ALIAS(IntDefaultHandler);
void USBWAKEUP_IRQHandler(void) ALIAS(IntDefaultHandler);
void LCDCINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void GFXINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void THRESH_PULSE_3PGSWRXTHR0_IRQHandler(void) ALIAS(IntDefaultHandler);
void RX_PULSE_3PGSWRXINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TX_PULSE_3PGSWTXINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void MISC_PULSE_3PGSWMISC0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART3INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART4INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART5INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void eCAP1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN0_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN0_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN0PARITY_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN1_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN1_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void DCAN1PARITY_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM0_TZINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM1_TZINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM2_TZINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void eCAP2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT3A_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT3B_IRQHandler(void) ALIAS(IntDefaultHandler);
void MMCSD0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void McSPI0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT1_1MS_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTCINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTCALARMINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void MBINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void M3_TXEV_IRQHandler(void) ALIAS(IntDefaultHandler);
void eQEP0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCATXINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCARXINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCATXINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void MCARXINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM0INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void ePWM1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void eQEP1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void eQEP2INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_INTR_PIN2_IRQHandler(void) ALIAS(IntDefaultHandler);
void WDT1INT_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void TINT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT0A_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT0B_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT1A_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOINT1B_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPMCINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void DDRERR0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TCERRINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void TCERRINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void TCERRINT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_TSC_PENINT_IRQHandler(void) ALIAS(IntDefaultHandler);
void SMRFLX_MPU_IRQHandler(void) ALIAS(IntDefaultHandler);
void SMRFLX_Core_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_INTR_PIN0_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_INTR_PIN1_IRQHandler(void) ALIAS(IntDefaultHandler);
void McSPI1INT_IRQHandler(void) ALIAS(IntDefaultHandler);

static void Reserved(void);

void (* const IRQ_Vectors[128])(void) = {
   EMUINT_IRQHandler,                        // 0
   COMMTX_IRQHandler,                        // 1
   COMMRX_IRQHandler,                        //
   BENCH_IRQHandler,
   ELM_IRQ_IRQHandler,
   Reserved,
   Reserved,
   NMI_IRQHandler,
   Reserved,
   L3DEBUG_IRQHandler,
   L3APPINT_IRQHandler,
   PRCMINT_IRQHandler,
   EDMACOMPINT_IRQHandler,
   EDMAMPERR_IRQHandler,
   EDMAERRINT_IRQHandler,
   Reserved,
   ADC_TSC_GENINT_IRQHandler,
   USNSSINT_IRQHandler,
   USBINT0_IRQHandler,
   USBINT1_IRQHandler,
   PRU_ICSS_EVTOUT0_IRQHandler,
   PRU_ICSS_EVTOUT1_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT2_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT3_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT4_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT5_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT6_IRQHandler_IRQHandler,
   PRU_ICSS_EVTOUT7_IRQHandler_IRQHandler,
   MMCSD1INT_IRQHandler,
   MMCSD2INT_IRQHandler,
   I2C2INT_IRQHandler,
   eCAP0INT_IRQHandler,
   GPIOINT2A_IRQHandler,
   GPIOINT2B_IRQHandler,
   USBWAKEUP_IRQHandler,
   Reserved,
   LCDCINT_IRQHandler,
   GFXINT_IRQHandler,
   Reserved,
   ePWM2INT_IRQHandler,
   THRESH_PULSE_3PGSWRXTHR0_IRQHandler,
   RX_PULSE_3PGSWRXINT0_IRQHandler,
   TX_PULSE_3PGSWTXINT0_IRQHandler,
   MISC_PULSE_3PGSWMISC0_IRQHandler,
   UART3INT_IRQHandler,
   UART4INT_IRQHandler,
   UART5INT_IRQHandler,
   eCAP1INT_IRQHandler,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   DCAN0_INT0_IRQHandler,
   DCAN0_INT1_IRQHandler,
   DCAN0PARITY_IRQHandler,
   DCAN1_INT0_IRQHandler,
   DCAN1_INT1_IRQHandler,
   DCAN1PARITY_IRQHandler,
   ePWM0_TZINT_IRQHandler,
   ePWM1_TZINT_IRQHandler,
   ePWM2_TZINT_IRQHandler,
   eCAP2INT_IRQHandler,
   GPIOINT3A_IRQHandler,
   GPIOINT3B_IRQHandler,
   MMCSD0INT_IRQHandler,
   McSPI0INT_IRQHandler,
   TINT0_IRQHandler,
   TINT1_1MS_IRQHandler,
   TINT2_IRQHandler,
   TINT3_IRQHandler,
   I2C0INT_IRQHandler,
   I2C1INT_IRQHandler,
   UART0INT_IRQHandler,
   UART1INT_IRQHandler,
   UART2INT_IRQHandler,
   RTCINT_IRQHandler,
   RTCALARMINT_IRQHandler,
   MBINT0_IRQHandler,
   M3_TXEV_IRQHandler,
   eQEP0INT_IRQHandler,
   MCATXINT0_IRQHandler,
   MCARXINT0_IRQHandler,
   MCATXINT1_IRQHandler,
   MCARXINT1_IRQHandler,
   Reserved,
   Reserved,
   ePWM0INT_IRQHandler,
   ePWM1INT_IRQHandler,
   eQEP1INT_IRQHandler,
   eQEP2INT_IRQHandler,
   DMA_INTR_PIN2_IRQHandler,
   WDT1INT_IRQHandler,
   TINT4_IRQHandler,
   TINT5_IRQHandler,
   TINT6_IRQHandler,
   TINT7_IRQHandler,
   GPIOINT0A_IRQHandler,
   GPIOINT0B_IRQHandler,
   GPIOINT1A_IRQHandler,
   GPIOINT1B_IRQHandler,
   GPMCINT_IRQHandler,
   DDRERR0_IRQHandler,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   TCERRINT0_IRQHandler,
   TCERRINT1_IRQHandler,
   TCERRINT2_IRQHandler,
   ADC_TSC_PENINT_IRQHandler,
   Reserved,
   Reserved,
   Reserved,
   Reserved,
   SMRFLX_MPU_IRQHandler,
   SMRFLX_Core_IRQHandler,
   Reserved,
   DMA_INTR_PIN0_IRQHandler,
   DMA_INTR_PIN1_IRQHandler,
   McSPI1INT_IRQHandler,
   Reserved,
   Reserved
};

__attribute__((section(".text_pub"))) void procIrqHandler(uint32_t irq_n)
{
   typedef void (*IntVector)(void);
   IntVector vect = IRQ_Vectors[irq_n];
   (*vect)();
}

__attribute__((section(".text_pub"))) void BSP_fiq(void)
{
   while(1);

}
__attribute__((section(".text_pub"))) void BSP_abort(char *str, uint32_t instruction)
{
   while(1);
}

__attribute__((section(".text_pub"))) void IntDefaultHandler (void)
{
   while(1);
}

__attribute__((section(".text_pub"))) static void Reserved(void)
{
   while(1);
}