 /**
 * Archivo: uart.c
 * Función: Posee los wrappers necesarios para el manejo de la UART: inicialización, lectura y escritura.
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
#include "../../inc/board/uart.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/system_utils.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/utils/clock_modules.h"


uint16_t UART_Init(uint32_t, uint32_t, uint32_t, uint32_t);
uint16_t UART_printf(uint16_t, char *, uint16_t );
uint16_t UART_scanf(uint16_t, char *, uint16_t );
void UART_putC(uint16_t , char );
char UART_getC(uint16_t );
int UART_putString(uint16_t , char *, uint32_t);
int UART_getString(uint16_t , char *, uint32_t);

__attribute__((section(".text_pub"))) uint16_t UART_Init(uint32_t uart_num, uint32_t baudrate, uint32_t stop_bits, uint32_t parity)
    {
        uint32_t uart_dir_base = UART_ARRAY_BASE[uart_num], ret_status = 0;
        uint32_t control_module_read = 0, clock_module_read = 0, read_uart = 0;
        uint32_t divisor_baudios = 0, gpio1_settings = 0;
        // float div;

        /* Acá habilitamos el clock (bit 18) y el modo 2 (bits 0 y 1)*/
        gpio1_settings = (1<<18) | (0x2<<0);
        
        switch(uart_num)
        {
            case 0:
                /* Inicializamos los GPIO */
                GPIO_Init_Port(GPIO1,gpio1_settings);

                /* Configuramos Modulos de Control */
                ControlModule_Set(CM_BASE_DIR,CM_conf_uart0_txd,0);
                ControlModule_Set(CM_BASE_DIR,CM_conf_uart0_rxd,(1<<4)|(1<<5));

                /* 
                    Configuramos los pads (los que se mapean luego a los pines J1 de la BBB),
                    es decir, tocamos el MUX.
                    P1.11 como TX 
                    P1.10 como RX
                */
                // Para TX
                control_module_read = ControlModule_Get(CM_BASE_DIR,CM_conf_uart0_txd);
                control_module_read &= ~(0b111);
                control_module_read |= MODO_0;
                ControlModule_Set(CM_BASE_DIR,CM_conf_uart0_txd,control_module_read);
                // Para RX
                control_module_read = ControlModule_Get(CM_BASE_DIR,CM_conf_uart0_rxd);
                control_module_read &= ~(0b111);
                control_module_read |= MODO_0;
                ControlModule_Set(CM_BASE_DIR,CM_conf_uart0_rxd,control_module_read);
 

                /* Configuramos los Registros de Clock*/
                clock_module_read = ClockModule_Get(CKM_WKUP,CKM_WKUP_CLKSTCTRL);
                clock_module_read &= ~(0b11);
                clock_module_read |= 0b10;                        // Activamos el modulo forzandolo por software - TRM 8.1.12.1.54
                ClockModule_Set(CKM_WKUP,CKM_WKUP_CLKSTCTRL,clock_module_read);

                clock_module_read = ClockModule_Get(CKM_PER,CKM_PER_L4HS_CLKSTCTRL);
                clock_module_read &= ~(0x11);
                clock_module_read |= 0x010;                        // Activamos el modulo forzandolo por software - TRM 8.1.12.2.46
                ClockModule_Set(CKM_PER,CKM_PER_L4HS_CLKSTCTRL,clock_module_read);
                
                // Aca falta algo, el original setea 
                
                clock_module_read = ClockModule_Get(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL);
                clock_module_read &= ~(0b11);
                clock_module_read |= 0b10;                       // Activamos el modulo forzandolo por software - TRM 8.1.12.2.46
                ClockModule_Set(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL,clock_module_read);

                // Ahora esperamos que se complete la transición del clock
                // while((ClockModule_Get(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL) & (0xB11<<16)) != 0);
                while((ClockModule_Get(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL) & (0b11 << 16)) != 0);

                // Ahora esperamos que se complete la transición del clock
                //while((ClockModule_Get(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL) & (0xB11<<16)) != 0);

                // Algo con la UART 1
                clock_module_read = ClockModule_Get(CKM_PER,CKM_PER_UART1_CLKCTRL);
                clock_module_read &= ~(0b11);
                clock_module_read |= 0b10;                        // Activamos el modulo forzandolo por software - TRM 8.1.12.2.46
                ClockModule_Set(CKM_PER,CKM_PER_UART1_CLKCTRL,clock_module_read);

                /* Resteamos la UART */
                read_uart = _READ_32(uart_dir_base + UARTx_OP_R_SYSC);  // Leemos el registro SYSC - TRM 19.5.1
                read_uart |= 0x2;                                       // Ponemos en 1 el bit 1
                _WRITE_32(uart_dir_base + UARTx_OP_R_SYSC, read_uart);  // Escribimos el registro SYSC

                // Esperamos a que se confirme el reset. Para eso, leemos el registro SYSS
                while((_READ_32(uart_dir_base + UARTx_OP_R_SYSS) & 0x1) == 0);

                /* Configuramos la UART */
                // Configuramos como No-Idle en el registro SYSC
                read_uart = _READ_8(uart_dir_base + UARTx_OP_R_SYSC);  // Leemos el registro SYSC - TRM 19.5.1
                read_uart |= (0x1<<3); //0x8;                                       // Ponemos en 1 el bit 3
                _WRITE_8(uart_dir_base + UARTx_OP_R_SYSC, read_uart);  // Escribimos el registro SYSC

                // Esperamos que la FIFO de TX este limpia
                while(((_READ_32(uart_dir_base + UARTx_OP_R_LSR) & 0x40) != 0x40));

                // Obtenemos el valor de división para configurar la tasa de baudios
                //divisor_baudios = (uint32_t) (((double)48000000.0)/((double)16.0 * (float)baudrate));

                // div = 48000000.0/(16.0*(float)baudrate);
                // divisor_baudios = (unsigned int) div;
                divisor_baudios = 26;
                // Escribimos los registros de la UART0:
                _WRITE_8(uart_dir_base + 0x04, 0);
                _WRITE_8(uart_dir_base + 0x20, 0x7);                 // Deshabilitamos mode-select - TRM tabla 19-50
                _WRITE_8(uart_dir_base + 0x0C, ~(0x7C));              // Acceso a DLL y DHL, UART 8 bits.
                _WRITE_8(uart_dir_base + 0x00, 0);                               // Cargamos DLL
                _WRITE_8(uart_dir_base + 0x04, 0);                               // Cargamos DHL
                _WRITE_8(uart_dir_base + 0x0C, 0x3);                             // UART de 8 bits
                _WRITE_8(uart_dir_base + 0x10,0x3);                   // Se fuerza a rts y drt activos bajo
                _WRITE_8(uart_dir_base + 0x08,0x7);                   // Se limpian las FIFOs RX y TX, y las habilita
                _WRITE_8(uart_dir_base + 0x0C, ~(0x7C));              // Acceso a DLL y DHL, UART 8 bits.
                _WRITE_8(uart_dir_base + 0x00, divisor_baudios & 0xFF);          // Cargamos parte baja
                _WRITE_8(uart_dir_base + 0x04, (divisor_baudios >>8) & 0x3F);    // Cargamos parte alta
                
                _WRITE_8(uart_dir_base + 0x0C, 0x3);                             // UART de 8 bits
                _WRITE_8(uart_dir_base + 0x20, 0);

                ret_status = 0;

                break;
            case 1:
                ret_status = 1;
                break;
            case 2:
                ret_status = 1;
                break;
            case 3:
                ret_status = 1;
                break;
            case 4:
                ret_status = 1;
                break;
            case 5:
                ret_status = 1;
                break;
            default:
                ret_status = 1;
                break;

        }


        return ret_status;

    }

/*  
    Wrapper para imprimir/escribir por la consola UART
*/
__attribute__((section(".text_pub"))) uint16_t UART_printf(uint16_t uart_num, char *string, uint16_t len)
    {
        uint16_t i = 0;
        uint32_t uart_dir_base = UART_ARRAY_BASE[uart_num];
        for(i = 0; i < len; i++)
            {   
                /* Esperamos que la FIFO de TX esté limpia (TRM - 19.5.1.12)*/
                while((_READ_8(uart_dir_base + UARTx_OP_R_LSR) & 0x20) != 0x20 );
                /* Escribimos el dato */
                _WRITE_8(uart_dir_base + UARTx_OP_W_THR, string[i]);
            }
        return len;
    }

/*  
    Wrapper para leer/recibir por la UART
*/
__attribute__((section(".text_pub"))) uint16_t UART_scanf(uint16_t uart_num, char *buffer, uint16_t len)
    {
        uint16_t i = 0;
        uint16_t uart_dir_base = UART_ARRAY_BASE[uart_num];     

        for(i = 0; i < len; i++)
            {
                /* Esperamos que haya un caracter en la UART */
                while((_READ_8(uart_dir_base + UARTx_OP_R_LSR) & 0x1) == 0);
                /* Leemos el dato recibido */
                buffer[i] = _READ_8(uart_dir_base + UARTx_OP_R_RHR);
            }


        return len;
    }


__attribute__((section(".text_pub"))) void UART_putC(uint16_t uart, char c)
{
   unsigned int uart_base = UART_ARRAY_BASE[uart];
   while((_READ_8(uart_base+0x14)&0x20)!=0x20);   //wait until txfifo is empty
    
   _WRITE_8(uart_base +0,c);
}

__attribute__((section(".text_pub"))) char UART_getC(uint16_t uart)
{
   unsigned int uart_base = UART_ARRAY_BASE[uart];
   while((_READ_8(uart_base+0x14)&0x1)==0);     //wait for a character to be in the rx fifo
   return _READ_8(uart_base+0x0);
}

__attribute__((section(".text_pub"))) int UART_putString(uint16_t uart, char *str, unsigned int length)
{
   for(int i = 0; i < length; i++)
   {
      UART_putC(uart,str[i]);
   }
   return length;
}

__attribute__((section(".text_pub"))) int UART_getString(uint16_t uart, char *buf, unsigned int length)
{
   for(int i = 0; i < length; i ++)
   {
      buf[i] = UART_getC(uart);
   }
   return length;
}