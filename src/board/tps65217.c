 /**
 * Archivo: pll_init.c
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
#include "../../inc/board/tps65217.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/utils/clock_modules.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/board/i2c.h"
#include "../../inc/utils/console_utils.h"

void TPS65217_Read(uint8_t, uint8_t *);
void TPS65217_Write(uint8_t , uint8_t , uint8_t , uint8_t );
void TPS65217_V_Update(uint8_t , uint8_t );
void TPS65217_Power_Status(void);

__attribute__((section(".text_pub"))) void TPS65217_Power_Status(void)
    {
        uint8_t pmic_status = 0;

        TPS65217_Read(STATUS,&pmic_status);
        switch(pmic_status)
            {
                case 0x1:
                    ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) status: power button pulled low");
                    break;
                case 0x4:
                    ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) status: alimentación desde USB (rango valido para carga)");
                    break;
                case 0x8:
                    ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) status: alimentación desde AC (rango valido para carga)");
                    break;
                default:
                    ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) status: alimentación presente pero no válida para carga");
                    break;
            }

        pmic_status = 0;
        TPS65217_Read(POWER_PATH,&pmic_status);
        switch (pmic_status & 0x3)
            {
            case 0x0:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente USB: 100 mA");
                break;
            case 0x1:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente USB: 500 mA");
                break;
            case 0x2:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente USB: 1300 mA");
                break;
            case 0x3:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente USB: 1800 mA");
                break;                                            
            }
        switch (pmic_status & 0xC)
            {
            case 0x0:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente actual AC: 100 mA");
                break;
            case 0x1:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente actual AC: 500 mA");
                break;
            case 0x2:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente actual AC: 1300 mA");
                break;
            case 0x3:
                ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) limite de corriente actual AC: 2500 mA");
                break;                                            
            }

        pmic_status = 0;    
        TPS65217_Read(DEFDCDC1,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor DCDC1 (DDR): %d mV",DCDC_voltage_table[pmic_status & 0x3F]);
        pmic_status = 0;    
        TPS65217_Read(DEFDCDC2,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor DCDC2 (MPU): %d mV",DCDC_voltage_table[pmic_status & 0x3F]);
        pmic_status = 0;    
        TPS65217_Read(DEFDCDC3,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor DCDC3 (CORE): %d mV",DCDC_voltage_table[pmic_status & 0x3F]);        
        pmic_status = 0;    
        TPS65217_Read(DEFLDO1,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor LDO1 (VDDS, VDDS_RTC): %d mV",LDO_A_voltage_table[pmic_status & 0xF]);   
        pmic_status = 0;    
        TPS65217_Read(DEFLDO2,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor LDO2 (Power LED): %d mV",DCDC_voltage_table[pmic_status & 0x3F]);    // Si. Es correcto. Es la misma tabla de tensiones para este caso de LDO2
        pmic_status = 0;    
        TPS65217_Read(DEFLS1,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor LDO3 (LS1): %d mV",LDO_B_voltage_table[pmic_status & 0x1F]);            
        pmic_status = 0;    
        TPS65217_Read(DEFLS2,&pmic_status);
        ConsoleUtilsPrintf("\n\r\tPMIC (TPS65217) valor LDO4 (LS2): %d mV",LDO_B_voltage_table[pmic_status & 0x1F]);          
    }

__attribute__((section(".text_pub"))) void TPS65217_Read(uint8_t reg_to_read, uint8_t *data)
    {
        uint8_t send_data[3];
        uint8_t received_data[2];

        send_data[0] = reg_to_read;

        I2C0_Setup_InputData(1,send_data,0,received_data);
        *data = received_data[0];
    }


__attribute__((section(".text_pub"))) void TPS65217_Write(uint8_t protection_level, uint8_t reg_to_read, uint8_t value_to_write, uint8_t mask)
    {
        uint8_t send_data[3];
        uint8_t received_data[2];
        uint8_t read_data;
        uint32_t xor_reg;

        send_data[0] = reg_to_read;
        
        if(mask != MASK_ALL_BITS)
            {
                I2C0_Setup_InputData(1,send_data,0,received_data);
                read_data = received_data[0];
                read_data &= ~(mask);
                read_data |= (value_to_write & mask);
                value_to_write = read_data;
            }
        
        if(protection_level > 0)
            {
                xor_reg = reg_to_read ^ PASSWORD_UNLOCK;

                send_data[0] = PASSWORD;
                send_data[1] = xor_reg;

                I2C0_Setup_OutputData(2, send_data, 0);
            }

        send_data[0] = reg_to_read;
        send_data[1] = value_to_write;
        I2C0_Setup_OutputData(2, send_data, 0);

        if(protection_level == PROT_LEVEL_2)
            {
                send_data[0] = PASSWORD;
                send_data[1] = xor_reg;
                I2C0_Setup_OutputData(2, send_data, 0);

                send_data[0] = reg_to_read;
                send_data[1] = value_to_write;
                I2C0_Setup_OutputData(2, send_data, 0);
            }


    }

__attribute__((section(".text_pub"))) void TPS65217_V_Update(uint8_t dcdc_ctrl_reg_addr, uint8_t volt_value)
    {   
        // Configuramos el nivel de tensión
        TPS65217_Write(PROT_LEVEL_2, dcdc_ctrl_reg_addr, volt_value, MASK_ALL_BITS);

        // Mandamos el bit de GO, para iniciar la transición de cambio de tensión
        TPS65217_Write(PROT_LEVEL_2, DEFSLEW, DCDC_GO, DCDC_GO);
    }

