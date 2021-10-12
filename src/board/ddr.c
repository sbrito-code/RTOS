 /**
 * Archivo: ddr.c
 * Función: Realiza la inicialización de la RAM externa. 
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
#include "../../inc//utils/low_level_cpu_access.h"
#include "../../inc/utils/clock_modules.h"
#include "../../inc/utils/control_module.h"
#include "../../inc/board/pll.h"
#include "../../inc/board/ddr.h" 


void DDR3_Init(void);
void Clean_DDR(void);

/*
    Datos para configurar la DDR3 en base a la disponible en la BBB:

        - Micron DDR3L, P/N: MT41K256M16HA-125:E
        - DDR3L: 400MHz (parece que hay una limitacion por parte de TI, porque segun specs puede ir a 800 MHz)
        - BBB clock ppal: 24MHz
*/
__attribute__((section(".text_pub"))) void DDR3_Init(void)
    {   
        uint32_t config = 0, VTP_REGISTER = 0, read_dummy;

        // Se configura el clock (se habilita)
        config = 0x02;          // TRM 8.1.12.1.9
        _WRITE_32(CKM_PER + CKM_PER_EMIF_FW_CLKCTRL,config);
        _WRITE_32(CKM_PER + CKM_PER_EMIF_CLKCTRL,config);
        // Esperamos que la configuración se aplique
        while(_READ_32(CKM_PER + CKM_PER_EMIF_CLKCTRL) != 0x02);

        // Configuramos la tabla VTP 
        // Lo que hacemos es configurar el controlador VTP, que es el controlador
        // de "voltage, temperature and process". Se configuran impendancias y demás.
        // vean el TRM 7.3.3.3.4 - VTP Controller Macro

        // TRM 9.3.54
        // Limpiamos el registro
        VTP_REGISTER = CM_BASE_DIR + CM_vtp_ctrl;
        _WRITE_32(VTP_REGISTER,0x0);
        // Configuramos el filtro
        _WRITE_32(VTP_REGISTER,0x6);
        // Habilitamos el controlador VTP
        read_dummy = _READ_32(VTP_REGISTER);
        _WRITE_32(VTP_REGISTER,read_dummy | 0x00000040);
        // Ahora reiniciamos el contador y los Flip-Flops
        // Escribimos un 0 en clrz
        read_dummy = _READ_32(VTP_REGISTER);
        _WRITE_32(VTP_REGISTER,read_dummy & 0xFFFFFFFE);
        // Escribimos un 1
        read_dummy = _READ_32(VTP_REGISTER);
        _WRITE_32(VTP_REGISTER,read_dummy | 0x00000001);
        // Verificamos que esté listo
        while((_READ_32(VTP_REGISTER) & 0x00000020) != 0x00000020);

        // Configuramos el CMD (Command Macro) - TRM 7.3.3.3.3
        // Es decir, actuamos sobre el EMIF
        // Configuración para DDR3 a 400 MHz
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD0_REG_PHY_CTRL_SLAVE_RATIO_0, 0x80); // TRM 7.3.6.1
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD0_REG_PHY_DLL_LOCK_DIFF_0, 0x01); // TRM 7.3.6.2
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD0_REG_PHY_INVERT_CLKOUT_0, 0x0); // TRM 7.3.6.3
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD1_REG_PHY_CTRL_SLAVE_RATIO_0, 0x80); 
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD1_REG_PHY_DLL_LOCK_DIFF_0, 0x01); 
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD1_REG_PHY_INVERT_CLKOUT_0, 0x0); 
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD2_REG_PHY_CTRL_SLAVE_RATIO_0, 0x80);
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD2_REG_PHY_DLL_LOCK_DIFF_0, 0x01);
        _WRITE_32(DDR_PHY_ADDR + DDR_CMD2_REG_PHY_INVERT_CLKOUT_0, 0x0); 
        
        // Configuramos Data Macro - TRM 7.3.3.3.2
        // DATA 0
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_RD_DQS_SLAVE_RATIO_0,0x38);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_WR_DQS_SLAVE_RATIO_0,0x44);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_WRLVL_INIT_RATIO_0,0x00);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_WRLVL_INIT_MODE_0,0x00);;
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_FIFO_WE_SLAVE_RATIO_0,0x94);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_WR_DATA_SLAVE_RATIO_0,0x7D);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_USE_RANK0_DELAYS,0x00);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA0_REG_PHY_DLL_LOCK_DIFF_0,0x00);

        // Data 1
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_RD_DQS_SLAVE_RATIO_0,0x38);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_WR_DQS_SLAVE_RATIO_0,0x44);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_WRLVL_INIT_RATIO_0,0x00);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_WRLVL_INIT_MODE_0,0x00);;
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_FIFO_WE_SLAVE_RATIO_0,0x94);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_WR_DATA_SLAVE_RATIO_0,0x7D);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_USE_RANK0_DELAYS,0x00);
        _WRITE_32(DDR_PHY_ADDR + DDR_DATA1_REG_PHY_DLL_LOCK_DIFF_0,0x00);

        // Ahora configuramos los Control Registers ddr_cmdn_ioctrl y ddr_datan_ioctrl
        // Ver TRM 9.3.88 a 9.3.92, y para el valor cargado, TRM 9.2.5
        _WRITE_32(CM_BASE_DIR + CM_ddr_cmd0_ioctrl,0x18B); 
        _WRITE_32(CM_BASE_DIR + CM_ddr_cmd1_ioctrl,0x18B);
        _WRITE_32(CM_BASE_DIR + CM_ddr_cmd2_ioctrl,0x18B);
        _WRITE_32(CM_BASE_DIR + CM_ddr_data0_ioctrl,0x18B);
        _WRITE_32(CM_BASE_DIR + CM_ddr_data1_ioctrl,0x18B);

        // IO 
        read_dummy = _READ_32(CM_BASE_DIR + CM_ddr_io_ctrl);
        _WRITE_32(CM_BASE_DIR + CM_ddr_io_ctrl,read_dummy & ~0x10000000);   // TRM 9.3.53

        // Normal Operation - Controlado por EMIF/DDR PHY
        read_dummy = _READ_32(CM_BASE_DIR + CM_ddr_cke_ctrl);
        _WRITE_32(CM_BASE_DIR + CM_ddr_cke_ctrl, read_dummy | 0x000000001); // TRM 9.3.77

        // Ahora configuramos los registros para Timing del EMIF
        _WRITE_32(EMIF_ADDR + EMIF_DDR_PHY_CTRL_1,0x00100007);      // TRM 7.3.5.33
        _WRITE_32(EMIF_ADDR + EMIF_DDR_PHY_CTRL_1_SHDW,0x00100007); // TRM 7.3.5.34
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_1,0x0AAAD4DB);         // TRM 7.3.5.7
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_1_SHDW,0x0AAAD4DB);    // TRM 7.3.5.8
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_2,0x266B7FDA);         // TRM 7.3.5.9
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_2_SHDW,0x266B7FDA);    // TRM 7.3.5.10
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_3,0x501F867F);         // TRM 7.3.5.11
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_TIM_3_SHDW,0x501F867F);    // TRM 7.3.5.12

        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_REF_CTRL,0x2800);  // TRM 7.3.5.5
        _WRITE_32(EMIF_ADDR + EMIF_ZQ_CONFIG,0x50074BE4);   // TRM 7.3.5.29

        _WRITE_32(CM_BASE_DIR + CM_control_emif_sdram_config,0x61C05332);   // TRM 9.3.5
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_CONFIG,0x61C05332);                // TRM 7.3.5.3
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_REF_CTRL,0x00000C30);              // TRM 7.3.5.5
        _WRITE_32(EMIF_ADDR + EMIF_SDRAM_REF_CTRL_SHDW,0x00000C30);         // TRM 7.3.5.6

        
    }

/*
   Limpia la memoria DDR
*/
__attribute__((section(".text_pub"))) void Clean_DDR(void)
{
    uint32_t i = 0;

    for(i = (uint32_t)&_DDR0_INIT; i < (uint32_t)&_DDR0_INIT + 0x2000000; i+= 4)
    {     
        _WRITE_32(i,0);
    }
}