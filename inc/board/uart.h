/**
 * Archivo: uart.h
 * Función: definición para el uso de la UART para BeagleBone Black - Rev. C
 * Autores: Brito Sergio Sebastian
 **/


#ifndef __UART_H
#define __UART_H

#define UARTx_OP_R_RHR 			0x0
#define UARTx_OP_R_IER			0x4
#define UARTx_OP_R_IIR			0x8
#define UARTx_OP_R_LCR			0xC
#define UARTx_OP_R_MCR			0x10
#define UARTx_OP_R_LSR			0x14
#define UARTx_OP_R_MSRTCR		0x18
#define UARTx_OP_R_SPRTLR		0x1C
#define UARTx_OP_R_MDR1			0x20
#define UARTx_OP_R_MDR2			0x24
#define UARTx_OP_R_SFLSR		0x28
#define UARTx_OP_R_RESUME		0x2C
#define UARTx_OP_R_SFREGL		0x30
#define UARTx_OP_R_SFREGH		0x34
#define UARTx_OP_R_BLR			0x38
#define UARTx_OP_R_ACREG		0x3C
#define UARTx_OP_R_SCR			0x40
#define UARTx_OP_R_SSR			0x44
#define UARTx_OP_R_EBLR			0x48
#define UARTx_OP_R_MVR			0x50
#define UARTx_OP_R_SYSC			0x54
#define UARTx_OP_R_SYSS			0x58
#define UARTx_OP_R_WER			0x5C
#define UARTx_OP_R_CFPS			0x60
#define UARTx_OP_R_RXFIFO_LVL	0x64
#define UARTx_OP_R_TXFIFO_LVL	0x68
#define UARTx_OP_R_IER2			0x6C
#define UARTx_OP_R_ISR2			0x70
#define UARTx_OP_R_FREQ_SEL	    0x74
#define UARTx_OP_R_MDR3			0x80
#define UARTx_OP_R_TXDMA		0x84

#define UARTx_OP_W_THR			0x0
#define UARTx_OP_W_IER			0x4
#define UARTx_OP_W_FCR			0x8
#define UARTx_OP_W_LCR			0xC
#define UARTx_OP_W_MCR			0x10
#define UARTx_OP_W_TCR			0x18
#define UARTx_OP_W_SPRTLR		0x1C
#define UARTx_OP_W_MDR1			0x20
#define UARTx_OP_W_MDR2			0x24
#define UARTx_OP_W_TXFLL		0x28
#define UARTx_OP_W_TXFLH		0x2C
#define UARTx_OP_W_RXFLL		0x30
#define UARTx_OP_W_RXFLH		0x34
#define UARTx_OP_W_BLR			0x38
#define UARTx_OP_W_ACREG		0x3C
#define UARTx_OP_W_SCR			0x40
#define UARTx_OP_W_SSR			0x44
#define UARTx_OP_W_EBLR			0x48
#define UARTx_OP_W_SYSC			0x54
#define UARTx_OP_W_WER			0x5C
#define UARTx_OP_W_CFPS			0x60
#define UARTx_OP_W_RXFIFO_LVL	0x64
#define UARTx_OP_W_TXFIFO_LVL	0x68
#define UARTx_OP_W_IER2			0x6C
#define UARTx_OP_W_ISR2			0x70
#define UARTx_OP_W_FREQ_SEL	    0x74
#define UARTx_OP_W_MDR3			0x80
#define UARTx_OP_W_TXDMA		0x84

// uart address map if UARTx_LCR[7:0] != 0xBF  (Configuration Mode A)
#define UARTx_MA_R_DLL			0x0
#define UARTx_MA_R_DLH			0x4
#define UARTx_MA_R_IIR			0x8
#define UARTx_MA_R_LCR			0xC
#define UARTx_MA_R_MCR			0x10
#define UARTx_MA_R_LSR			0x14
#define UARTx_MA_R_MSRTCR		0x18
#define UARTx_MA_R_SPRTLR		0x1C
#define UARTx_MA_R_MDR1			0x20
#define UARTx_MA_R_MDR2			0x24
#define UARTx_MA_R_SFLR			0x28
#define UARTx_MA_R_RESUME		0x2C
#define UARTx_MA_R_SFREGL		0x30
#define UARTx_MA_R_SFREGH		0x34
#define UARTx_MA_R_UASR			0x38
#define UARTx_MA_R_SCR			0x40
#define UARTx_MA_R_SSR			0x44
#define UARTx_MA_R_				0x48
#define UARTx_MA_R_MVR			0x50
#define UARTx_MA_R_SYSC			0x54
#define UARTx_MA_R_SYSS			0x58
#define UARTx_MA_R_WER			0x5C
#define UARTx_MA_R_CFPS			0x60
#define UARTx_MA_R_RXFIFO_LVL	0x64
#define UARTx_MA_R_TXFIFO_LVL	0x68
#define UARTx_MA_R_IER2			0x6C
#define UARTx_MA_R_ISR2			0x70
#define UARTx_MA_R_FREQ_SEL	    0x74
#define UARTx_MA_R_MDR3			0x80
#define UARTx_MA_R_TXDMA		0x84

#define UARTx_MA_W_DLL			0x00
#define UARTx_MA_W_DLH			0x04
#define UARTx_MA_W_FCR			0x08
#define UARTx_MA_W_LCR			0x0C
#define UARTx_MA_W_MCR			0x10
#define UARTx_MA_W_TCR			0x18
#define UARTx_MA_W_SPRTLR		0x1C
#define UARTx_MA_W_MDR1			0x20
#define UARTx_MA_W_MDR2			0x24
#define UARTx_MA_W_TXFLL		0x28
#define UARTx_MA_W_TXFLH		0x2C
#define UARTx_MA_W_RXFLL		0x30
#define UARTx_MA_W_RXFLH		0x34
#define UARTx_MA_W_SCR			0x40
#define UARTx_MA_W_SSR			0x44
#define UARTx_MA_W_SYSC			0x54
#define UARTx_MA_W_WER			0x5C
#define UARTx_MA_W_CFPS			0x60
#define UARTx_MA_W_RXFIFO_LVL	0x64
#define UARTx_MA_W_TXFIFO_LVL	0x68
#define UARTx_MA_W_IER2			0x6C
#define UARTx_MA_W_ISR2			0x70
#define UARTx_MA_W_FREQ_SEL	    0x74
#define UARTx_MA_W_MDR3			0x80
#define UARTx_MA_W_TXDMA		0x84

// uart address map if UARTx_LCR[7:0] == 0xBF  (Configuration Mode B)
#define UARTx_MB_R_DLL			0x00
#define UARTx_MB_R_DLH			0x04
#define UARTx_MB_R_EFR			0x08
#define UARTx_MB_R_LCR			0x0C
#define UARTx_MB_R_XON1ADDR2	0x10
#define UARTx_MB_R_XON2ADDR2	0x14
#define UARTx_MB_R_XOFF1TCR	    0x18
#define UARTx_MB_R_XOFF2TLR	    0x1C
#define UARTx_MB_R_MDR1			0x20
#define UARTx_MB_R_MDR2			0x24
#define UARTx_MB_R_SFLSR		0x28
#define UARTx_MB_R_RESUME		0x2C
#define UARTx_MB_R_SFREGL		0x30
#define UARTx_MB_R_SFREGH		0x34
#define UARTx_MB_R_UASR			0x38
#define UARTx_MB_R_SCR			0x40
#define UARTx_MB_R_SSR			0x44
#define UARTx_MB_R_MVR			0x50
#define UARTx_MB_R_SYSC			0x54
#define UARTx_MB_R_SYSS			0x58
#define UARTx_MB_R_WER			0x5C
#define UARTx_MB_R_CFPS			0x60
#define UARTx_MB_R_RXFIFO_LVL	0x64
#define UARTx_MB_R_TXFIFO_LVL	0x68
#define UARTx_MB_R_IER2			0x6C
#define UARTx_MB_R_ISR2			0x70
#define UARTx_MB_R_FREQ_SEL	    0x74
#define UARTx_MB_R_MDR3			0x80
#define UARTx_MB_R_TXDMA		0x84

#define UARTx_MB_W_DLL			0x00
#define UARTx_MB_W_DLH			0x04
#define UARTx_MB_W_EFR			0x08
#define UARTx_MB_W_LCR			0x0C
#define UARTx_MB_W_XON1ADDR1	0x10
#define UARTx_MB_W_XON2ADDR2	0x14
#define UARTx_MB_W_XOFF1TCR	    0x18
#define UARTx_MB_W_XOFF2TLR	    0x1C
#define UARTx_MB_W_MDR1			0x20
#define UARTx_MB_W_MDR2			0x24
#define UARTx_MB_W_SFLSR		0x28
#define UARTx_MB_W_RESUME		0x2C
#define UARTx_MB_W_SFREGL		0x30
#define UARTx_MB_W_SFREGH		0x34
#define UARTx_MB_W_UASR			0x38
#define UARTx_MB_W_SCR			0x40
#define UARTx_MB_W_SSR			0x44
#define UARTx_MB_W_MVR			0x50
#define UARTx_MB_W_SYSC			0x54
#define UARTx_MB_W_SYSS			0x58
#define UARTx_MB_W_WER			0x5C
#define UARTx_MB_W_CFPS			0x60
#define UARTx_MB_W_RXFIFO_LVL	0x64
#define UARTx_MB_W_TXFIFO_LVL	0x68
#define UARTx_MB_W_IER2			0x6C
#define UARTx_MB_W_ISR2			0x70
#define UARTx_MB_W_FREQ_SEL	    0x74
#define UARTx_MB_W_MDR3			0x80
#define UARTx_MB_W_TXDMA		0x84

#define MASK_TX_FIFO 0x20
#define MASK_RX_FIFO 0x01

static const unsigned int UART_ARRAY_BASE[] = {0x44E09000, 0x48022000, 0x48024000, 0x481A6000, 0x481A8000, 0x481AA000};

#define UART_0 0
#define UART_1 1
#define UART_2 2
#define UART_3 3
#define UART_4 4
#define UART_5 5

#define STOP_BITS_1 0
#define STOP_BITS_1_5 1
#define STOP_BITS_2 2

#define NO_PARITY 0
#define PAR_PARITY 1 
#define IMPAR_PARITY 2

#define UART0_CONFIG_RX 0x30 /* Establecemos Pull-Up/Pull-Down y habilitamos el receptor*/

#include "../utils/types.h"

extern uint16_t UART_Init(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint16_t UART_printf(uint16_t, char *, uint16_t );
extern uint16_t UART_scanf(uint16_t, char *, uint16_t );

#endif /* defined(__UART_H) */