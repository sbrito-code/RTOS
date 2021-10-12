 /**
 * Archivo: i2c.c
 * Función: Realiza la inicialización básica I2C0, sin FPU. 
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
#include "../../inc/board/i2c.h"
#include "../../inc/utils/console_utils.h"

void I2C0_Setup(void);
void I2C_Master_Ctrl(uint32_t ,uint32_t);
void I2C_Master_SlaveAddrs_Set(uint32_t , uint32_t );
void I2C_Master_Clear_IRQ(uint32_t , uint32_t );
void I2C_Set_Data_Count(uint32_t , uint32_t );
void I2C_Send_Data(uint32_t , uint8_t );
uint8_t I2C_Get_Data(uint32_t );
void I2C0_Setup_InputData(uint32_t , uint8_t *, uint32_t , uint8_t *);
void I2C0_Setup_OutputData(uint32_t , uint8_t *, uint32_t );

__attribute__((section(".text_pub"))) void I2C0_Setup(void)
    {   
        uint32_t config = 0, prescaler = 0, divider = 0;

        // Se configura el clock
        config = _READ_32(CKM_WKUP + CKM_WKUP_I2C0_CLKCTRL);
        config |= 0x2;
        _WRITE_32(CKM_WKUP + CKM_WKUP_I2C0_CLKCTRL,config);
        while((_READ_32(CKM_WKUP + CKM_WKUP_I2C0_CLKCTRL) & 0x3) != 0x2);

        while((_READ_32(CKM_WKUP + CKM_WKUP_I2C0_CLKCTRL) & 0x00030000) != 0x0);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(CKM_WKUP + CKM_WKUP_I2C0_CLKCTRL));

        // Configuramos los pines
        config = 0;
        config = I2C0_SDA_CONFIG_RXACTIVE | I2C0_SDA_CONFIG_SLEWCTRL | I2C0_SDA_CONFIG_PUTYPESEL;
        _WRITE_32(CM_BASE_DIR + CM_conf_i2c0_sda,config);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(CM_BASE_DIR + CM_conf_i2c0_sda));

        config = 0;
        config = I2C0_SCL_CONFIG_RXACTIVE | I2C0_SCL_CONFIG_SLEWCTRL | I2C0_SCL_CONFIG_PUTYPESEL;
        _WRITE_32(CM_BASE_DIR + CM_conf_i2c0_scl,config);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(CM_BASE_DIR + CM_conf_i2c0_scl));

        // Ponemos el I2C en reset (disable)       
        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_DISABLE);

        // Hacemos un soft-reset
        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_RESET);

        // Desactivamos auto-idle
        config = _READ_32(I2C0_BASE_ADDR + I2C_SYSC);
        config &= ~0x00000001;
        _WRITE_32(I2C0_BASE_ADDR + I2C_SYSC,config);  

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(I2C0_BASE_ADDR + I2C_SYSC));
        /* 
            Configuramos el canal a 100 KHz
            Por ahora seguimos sin FPU, asique todo esto va a mano:
                SYS_CLOCK = 48 MHz
                INT_CLOCK = 12 MHz
                BUS_CLOCK = 100 KHz

                prescaler = (48 MHz / 12 MHz) - 1
                prescaler = 4 - 1
                prescaler = 3

                divider_dum = 12 MHz / 100 KHz
                divider_dum = 120

                divider = divider_dum / 2 = 60
                    I2C_SCLL = divider - 7 = 60 - 7 = 53
                    I2C_SCLH = divider - 5 = 60 - 5 = 55        
        */

        prescaler = 3;
        divider = 60;
        
        // Configuramos el prescaler
        _WRITE_32(I2C0_BASE_ADDR + I2C_PSC,prescaler);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(I2C0_BASE_ADDR + I2C_PSC));
        // Configuramos el divisor
        _WRITE_32(I2C0_BASE_ADDR + I2C_SCLL,divider - 7);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(I2C0_BASE_ADDR + I2C_SCLL));
        _WRITE_32(I2C0_BASE_ADDR + I2C_SCLH,divider - 5);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(I2C0_BASE_ADDR + I2C_SCLH));

        // Habilitamos el I2C - Master
        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_ENABLE);

        // Esperamos a que se configure efectivamente
        while((_READ_32(I2C0_BASE_ADDR + I2C_SYSC) & 0x1) != 0x0);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup: 0x%x ", _READ_32(I2C0_BASE_ADDR + I2C_SYSC));
    }

__attribute__((section(".text_pub"))) void I2C_Master_Ctrl(uint32_t i2c_base, uint32_t order)
    {
        uint32_t config = 0;

 
        switch(order)
            {
                case I2C_DISABLE:
                    config = _READ_32(i2c_base + I2C_CON);
                    config &= ~0x00008000;
                    _WRITE_32(i2c_base + I2C_CON,config);
                    break;
                case I2C_ENABLE:
                    config = _READ_32(i2c_base + I2C_CON);
                    config |= 0x00008000;
                    _WRITE_32(i2c_base + I2C_CON,config);
                    break;
                case I2C_RESET:
                    config = _READ_32(i2c_base + I2C_SYSC);
                    config |= 0x2;
                    _WRITE_32(i2c_base + I2C_SYSC,config);
                    break;
                case I2C_START:
                    config = _READ_32(i2c_base + I2C_CON);
                    config |= 0x1;
                    _WRITE_32(i2c_base + I2C_CON,config);
                    break;
                case I2C_STOP:
                    config = _READ_32(i2c_base + I2C_CON);
                    config |= 0x2;
                    _WRITE_32(i2c_base + I2C_CON,config);
                    break;
                default:
                    config = order | 0x00008000;            // Fuerza con Enable
                    _WRITE_32(i2c_base + I2C_CON,config);
                    //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Master_Ctrl: 0x%x ",_READ_32(I2C0_BASE_ADDR + I2C_CON));
                    break;
            }


    }


__attribute__((section(".text_pub"))) void I2C_Master_SlaveAddrs_Set(uint32_t i2c_base, uint32_t slave_addr)
    {   
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Master_SlaveAddrs_Set: 0x%x | 0x%x",i2c_base,slave_addr);
        _WRITE_32(i2c_base + I2C_SA, slave_addr);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Master_SlaveAddrs_Set: 0x%x ", _READ_32(i2c_base + I2C_SA));
    }

__attribute__((section(".text_pub"))) void I2C_Master_Clear_IRQ(uint32_t i2c_base, uint32_t value)
    {   
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Master_Clear_IRQ: 0x%x | 0x%x",i2c_base,value);
        _WRITE_32(i2c_base + I2C_IRQSTATUS, value);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Master_Clear_IRQ: 0x%x ", _READ_32(i2c_base + I2C_IRQSTATUS));
    }

__attribute__((section(".text_pub"))) void I2C_Set_Data_Count(uint32_t i2c_base, uint32_t count)
    {   
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Set_Data_Count: 0x%x | 0x%x",i2c_base,count);
        _WRITE_32(i2c_base + I2C_CNT, count);
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Set_Data_Count: 0x%x ", _READ_32(i2c_base + I2C_CNT));
    }

__attribute__((section(".text_pub"))) void I2C_Send_Data(uint32_t i2c_base, uint8_t data)
    {   
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C_Send_Data: 0x%x | 0x%x",i2c_base,data);
        _WRITE_32(i2c_base + I2C_DATA, data);
    }

__attribute__((section(".text_pub"))) uint8_t I2C_Get_Data(uint32_t i2c_base)
    {   
        uint8_t in_data;

        in_data = _READ_8(i2c_base + I2C_DATA);
        return in_data;
    }

__attribute__((section(".text_pub"))) void I2C0_Setup_InputData(uint32_t bytes_num, uint8_t *send_data, uint32_t send_data_idx, uint8_t *received_data)
    {   
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ In ]: %d | 0x%x | %d",bytes_num,send_data[send_data_idx],send_data_idx);
        // Configuramos cuantas palabras va a enviar en una configuración master modo transmisión
        I2C_Set_Data_Count(I2C0_BASE_ADDR,1);

        // Limpiamos las interrupciones que puedan haber en el I2C
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x7FF);

        // Lo configuramos (al master) como master - transmitter
        I2C_Master_Ctrl(I2C0_BASE_ADDR,0x00000600);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data: 0x%x ",_READ_32(I2C0_BASE_ADDR + I2C_CON));

        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_START);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data: 0x%x ",_READ_32(I2C0_BASE_ADDR + I2C_CON));
        // Esperamos a que el bus esté libre:
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00001000) == 0);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ post - while]");

        // Colocamos el dato en el Data Transmit Register
        I2C_Send_Data(I2C0_BASE_ADDR,send_data[send_data_idx]);

        // Avisamos al slave que el transmitter está listo
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x10);

        // Esperamos a que el slave este listo (ARDY)
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00000004) == 0);
        
        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ post - while 2]");

        // Configuramos cuantos datos vamos a recibir
        I2C_Set_Data_Count(I2C0_BASE_ADDR,bytes_num);

        // Limpiamos las interrupciones que puedan haber en el I2C
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x7FF);

        // Configuramos al Master ahora como Master Receiver
        I2C_Master_Ctrl(I2C0_BASE_ADDR,0x00000400);

        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_START);

        // Esperamos a que el bus de datos esté libre
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00001000) == 0);

        //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ post - while 3]");

        // Leemos los datos enviados por el slave
        while(bytes_num--)
            {   
                //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ In - while 4]: %d",bytes_num);
                while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00000008) == 0);
                //ConsoleUtilsPrintf("\n\r[0.3.3] I2C0_Setup_Input_data [ In - while 4 - Post while 5]");
                received_data[bytes_num] = I2C_Get_Data(I2C0_BASE_ADDR);
                I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x00000008);
            }
        
        // Stop
        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_STOP);
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00000100) == 0);
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x00000100);
    }   

__attribute__((section(".text_pub"))) void I2C0_Setup_OutputData(uint32_t bytes_num, uint8_t *send_data, uint32_t send_data_idx)
    {
        // Configuramos cuantas palabras va a enviar en una configuración master modo transmisión
        I2C_Set_Data_Count(I2C0_BASE_ADDR,bytes_num);

        // Limpiamos las interrupciones que puedan haber en el I2C
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x7FF);

        // Lo configuramos (al master) como master - transmitter
        I2C_Master_Ctrl(I2C0_BASE_ADDR,0x00000600);

        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_START);

        // Esperamos a que el bus esté libre:
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00001000) == 0);

        // Enviamos los datos
        while(((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00000010) == 0x00000010) &&  bytes_num--)
            {
                // Colocamos el dato en el Data Transmit Register
                I2C_Send_Data(I2C0_BASE_ADDR,send_data[send_data_idx++]);
                // Avisamos al slave que el transmitter está listo
                I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x10);
            }

        // Stop
        I2C_Master_Ctrl(I2C0_BASE_ADDR,I2C_STOP);
        while((_READ_32(I2C0_BASE_ADDR + I2C_IRQSTATUS_RAW) & 0x00000100) == 0);
        I2C_Master_Clear_IRQ(I2C0_BASE_ADDR,0x00000100);   
    }