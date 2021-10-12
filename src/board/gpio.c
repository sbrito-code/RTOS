 /**
 * Archivo: gpio.c
 * Función: Posee los wrappers necesarios para el manejo de los GPIO: inicialización, seteo, apagado, etc..
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
#include "../../inc/board/gpio.h"
#include "../../inc/utils/system_utils.h"
#include "../../inc/utils/clock_modules.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/debug_tools.h"


uint16_t GPIO_Init_Port(uint16_t, uint32_t);
void GPIO_Set_Port(uint8_t, uint32_t);
uint16_t GPIO_Get_Port(uint8_t );
void GPIO_Clear_Port(uint8_t );
void GPIO_Set_Port_Mode(uint8_t , uint16_t);
void GPIO_Port_ModuleCtrl(uint8_t, uint8_t);

uint16_t GPIO_Init_Pin(uint32_t, uint16_t);
void GPIO_Set_Pin(uint8_t, uint8_t);
uint16_t GPIO_Get_Pin(uint8_t, uint8_t);
void GPIO_Clear_Pin(uint8_t, uint8_t);

void GPIO_Set_Direction(uint8_t, uint8_t, uint8_t);
uint8_t GPIO_Get_Direction(uint8_t, uint8_t);

void GPIO_SoftReset(uint8_t);

void GPIO_Set_Status_IRQ(uint8_t , uint8_t , uint8_t );
void GPIO_Set_LogicLevel_IRQ(uint8_t, uint8_t, uint8_t, uint8_t);
void GPIO_SetEdgeDetect_IRQ(uint8_t, uint8_t, uint8_t );
void GPIO_SetDebounce(uint8_t, uint8_t, uint8_t);
void GPIO_ClearDebounce(uint8_t, uint8_t);

/* Operaciones a nivel de Puerto */
/* Inicializa un puerto */
__attribute__((section(".text_pub"))) uint16_t GPIO_Init_Port(uint16_t port_num, uint32_t settings)
    {
        uint16_t ret_status = 0;
        //uint32_t ckm_read = 1;


        switch(port_num)
            {
                case 0:
                    ret_status = 2; /* GPIO0 no posee un registro de Modulo de clock (TRM 8.1.12.1) */
                    break;
                case 1:
                    ClockModule_Set(CKM_PER,CKM_PER_GPIO1_CLKCTRL,settings);  
                    while((ClockModule_Get(CKM_PER, CKM_PER_GPIO1_CLKCTRL) & (0x3<<16)) != 0)
                    ret_status = 0;
                    break;
                case 2:
                    ClockModule_Set(CKM_PER,CKM_PER_GPIO2_CLKCTRL,settings); 
                    while((ClockModule_Get(CKM_PER, CKM_PER_GPIO2_CLKCTRL) & (0x3<<16)) != 0)
                    ret_status = 0;
                    break;
                case 3:
                    ClockModule_Set(CKM_PER,CKM_PER_GPIO3_CLKCTRL,settings); 
                    while((ClockModule_Get(CKM_PER, CKM_PER_GPIO3_CLKCTRL) & (0x3<<16)) != 0)
                    ret_status = 0;
                    break;                
                default:
                    ret_status = 1;
                    break;

            }

        return ret_status;
    }

/* Lee el PUERTO seleccionado del PUERTO deseado */
__attribute__((section(".text_pub"))) uint16_t GPIO_Get_Port(uint8_t puerto)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_DATAIN;                  // Data In - Lo encontramos en TRM 2.1 y 25.4.1.17. 
        gpio_val = _READ_32(gpio_addr);
        return gpio_val;
    }

__attribute__((section(".text_pub"))) void GPIO_Set_Port(uint8_t puerto, uint32_t gpio_val)
    {
        uint32_t gpio_addr = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_SETDATAOUT;                  // Set Data Out - Lo encontramos en TRM 2.1 y 25.4.1.26. 
        _WRITE_32(gpio_addr, gpio_val);
    }

__attribute__((section(".text_pub"))) void GPIO_Set_Port_Mode(uint8_t puerto, uint16_t modo)
    {
        uint32_t gpio_addr = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_SYSCONFIG;      
        _WRITE_32(gpio_addr,modo);
    }

__attribute__((section(".text_pub"))) void GPIO_Port_ModuleCtrl(uint8_t puerto, uint8_t action)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_CTRL;  

        gpio_val = _READ_32(gpio_addr);
        gpio_val &= ~(0b111);
        gpio_val |= action;            
        _WRITE_32(gpio_addr,gpio_val);
    }

/* Operaciones a nivel de Pin */
/* Inicializa un pin */
__attribute__((section(".text_pub"))) uint16_t GPIO_Init_Pin(uint32_t module_offset, uint16_t modo)
    {
        uint32_t control_module_read = 0;
        control_module_read = ControlModule_Get(CM_BASE_DIR,module_offset);
        control_module_read &= ~(0b111);
        control_module_read |= modo;
        ControlModule_Set(CM_BASE_DIR,module_offset,control_module_read);
        return 0;

    }

/* Pone en 1 el PIN seleccionado del PUERTO deseado */
__attribute__((section(".text_pub"))) void GPIO_Set_Pin(uint8_t puerto, uint8_t pin)
    {
        uint32_t gpio_val = 0, gpio_addr = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_SETDATAOUT;                  // Set Data Out - Lo encontramos en TRM 2.1 y 25.4.1.26. 
        gpio_val = 1 << pin;
        _WRITE_32(gpio_addr, gpio_val);
    }

/* Lee el PIN seleccionado del PUERTO deseado */
__attribute__((section(".text_pub"))) uint16_t GPIO_Get_Pin(uint8_t puerto, uint8_t pin)
    {
        uint32_t gpio_val = 0, gpio_addr = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_DATAIN;                  // Data In - Lo encontramos en TRM 2.1 y 25.4.1.17. 
        gpio_val = _READ_32(gpio_addr);

        if (gpio_val & (1 << pin))
            {
                return 1;               // Está el pin en 1
            }
        else
            {
                return 0;               // Está el pin en 0
            }
    }

/* Limpia el estado del PIN seleccionado del PUERTO deseado */
__attribute__((section(".text_pub"))) void GPIO_Clear_Pin(uint8_t puerto, uint8_t pin)
    {
        uint32_t gpio_val = 0, gpio_addr = 0;
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_CLEARDATAOUT;                  // Clear Data Out - Lo encontramos en TRM 2.1 y 25.4.1.25. 
        gpio_val = 1 << pin;
        _WRITE_32(gpio_addr, gpio_val);

    }

/* Control de direccion */
// Esta funcion presenta algun tipo de bug que no permite la modificación de la variable gpio_val una vez que 
// se realiza la lectura del registro solicitado. 

__attribute__((section(".text_pub"))) void GPIO_Set_Direction(uint8_t puerto, uint8_t pin, uint8_t direction)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_OE;                          // Output Enable - Lo encontramos en TRM 2.1 y 25.4.1.16
        gpio_val = _READ_32(gpio_addr);
        gpio_val &= ~ (1 << pin);

        if(direction)
            {   
                gpio_val |= (1 << pin);
            }
        else
            {   
                gpio_val |= (0 << pin);
            }    

        _WRITE_32(gpio_addr,gpio_val);
    }

// __attribute__((section(".text_pub"))) void GPIO_Set_Direction(uint8_t puerto, uint8_t pin, uint8_t direction)
//     {
//         uint32_t gpio_addr = 0, gpio_val = 0;

//         gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_OE;                          // Output Enable - Lo encontramos en TRM 2.1 y 25.4.1.16

//         if(direction)
//             {   
//                 gpio_val = (1 << pin);
//             }
//         else
//             {   
//                 gpio_val = (0 << pin);
//             }    
//         _WRITE_32(gpio_addr,gpio_val);
//     }

__attribute__((section(".text_pub"))) uint8_t GPIO_Get_Direction(uint8_t puerto, uint8_t pin)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_OE;                          // Output Enable - Lo encontramos en TRM 2.1 y 25.4.1.16
        gpio_val = _READ_32(gpio_addr);

        if (gpio_val & (1 << pin))
            {
                return 1;               // Está como entrada
            }
        else
            {
                return 0;               // Está como salida 
            }
    }

// Seteo interrupcion - TRM 25.3.3.1
__attribute__((section(".text_pub"))) void GPIO_Set_Status_IRQ(uint8_t puerto, uint8_t pin, uint8_t status_reg)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        if(status_reg)
            {
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_IRQSTATUS_SET_1;
            }
        else
            {
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_IRQSTATUS_SET_0;
            }
        
        gpio_val = _READ_32(gpio_addr);
        gpio_val &= ~ (1 << pin);
        gpio_val |= (1 << pin);

        _WRITE_32(gpio_addr,gpio_val);
    }

__attribute__((section(".text_pub"))) void GPIO_Set_LogicLevel_IRQ(uint8_t puerto, uint8_t pin, uint8_t level_reg, uint8_t level)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        // Seteo nivel de deteccion - TRM 25.3.3
        if(level_reg)
            {
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_LEVELDETECT1;
            }
        else
            {
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_LEVELDETECT0;
            }        
        
        if(level)
            {
                gpio_val = _READ_32(gpio_addr);
                gpio_val &= ~ (1 << pin);
                gpio_val |= (1 << pin);
                _WRITE_32(gpio_addr,gpio_val);
            }
        else
            {
                gpio_val = _READ_32(gpio_addr);
                gpio_val &= ~ (1 << pin);
                _WRITE_32(gpio_addr,gpio_val);         
            }
 
    }

__attribute__((section(".text_pub"))) void GPIO_SetEdgeDetect_IRQ(uint8_t puerto, uint8_t pin, uint8_t edge)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        if(edge)
            {   
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_RISINGDETECT;
                gpio_val = _READ_32(gpio_addr);
                gpio_val &= ~ (1 << pin);
                gpio_val |= (1 << pin);
                _WRITE_32(gpio_addr,gpio_val);           
            }
        else
            {
                gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_FALLINGDETECT;
                gpio_val = _READ_32(gpio_addr);
                gpio_val &= ~ (1 << pin);
                gpio_val |= (1 << pin);
                _WRITE_32(gpio_addr,gpio_val);              
            } 
    }

__attribute__((section(".text_pub"))) void GPIO_SetDebounce(uint8_t puerto, uint8_t pin, uint8_t deb_time)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_DEBOUNCENABLE;

        gpio_val = _READ_32(gpio_addr);
        gpio_val &= ~ (1 << pin);
        gpio_val |= (1 << pin);
        _WRITE_32(gpio_addr,gpio_val);    
        
        gpio_addr = GPIO_BASE_ARRAY[puerto] + GPIO_DEBOUNCINGTIME;
        _WRITE_32(gpio_addr,deb_time);    

    }

__attribute__((section(".text_pub"))) void GPIO_ClearDebounce(uint8_t puerto, uint8_t pin)
    {
        uint32_t gpio_addr_0 = 0, gpio_val = 0;

        gpio_addr_0 = GPIO_BASE_ARRAY[puerto] + GPIO_DEBOUNCENABLE;

        gpio_val = _READ_32(gpio_addr_0);
        gpio_val &= ~ (0 << pin);
        _WRITE_32(gpio_addr_0,gpio_val);           

    }

__attribute__((section(".text_pub"))) void GPIO_SoftReset(uint8_t puerto)
    {
        uint32_t gpio_addr = 0, gpio_val = 0;

        gpio_addr = GPIO_BASE_ARRAY[puerto];
        gpio_val = 0x2;
        _WRITE_32(gpio_addr + GPIO_SYSCONFIG,gpio_val); 
        while(_READ_32(gpio_addr + GPIO_SYSSTATUS) != 0x1);

    }