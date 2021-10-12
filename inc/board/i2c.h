/**
 * Archivo: i2c.h
 * Función: archivo de definiciones para el uso del I2C
 * Autor: Brito Sergio Sebastian
 **/

#ifndef __I2C_H__
#define __I2C_H__


// I2C0 
#define I2C0_BASE_ADDR              0x44E0B000
#define I2C0_SYS_CLOCK              48000000        // Frecuencia del clock de ref
#define I2C0_INT_CLOCK              12000000        // Frecuencia interna
#define I2C0_BUS_CLOCK              1000000         // Frecuencia deseada del bus


// SDA
#define I2C0_SDA_CONFIG_RXACTIVE    0x00000020
#define I2C0_SDA_CONFIG_SLEWCTRL    0x00000040
#define I2C0_SDA_CONFIG_MMODE       0x00000007
#define I2C0_SDA_CONFIG_PUDEN       0x00000008
#define I2C0_SDA_CONFIG_PUTYPESEL   0x00000010
#define I2C0_SDA_CONFIG_RSVD        0x000FFF80

// SCL
#define I2C0_SCL_CONFIG_RXACTIVE    0x00000020
#define I2C0_SCL_CONFIG_SLEWCTRL    0x00000040
#define I2C0_SCL_CONFIG_MMODE       0x00000007
#define I2C0_SCL_CONFIG_PUDEN       0x00000008
#define I2C0_SCL_CONFIG_PUTYPESEL   0x00000010
#define I2C0_SCL_CONFIG_RSVD        0x000FFF80


#define I2C_REVNB_LO            0x00
#define I2C_REVNB_HI            0x04
#define I2C_SYSC                0x10
#define I2C_IRQSTATUS_RAW       0x24
#define I2C_IRQSTATUS           0x28
#define I2C_IRQENABLE_SET       0x2C
#define I2C_IRQENABLE_CLR       0x30
#define I2C_WE                  0x34
#define I2C_DMARXENABLE_SET     0x38
#define I2C_DMATXENABLE_SET     0x3C
#define I2C_DMARXENABLE_CLR     0x40
#define I2C_DMATXENABLE_CLR     0x44
#define I2C_DMARXWAKE_EN        0x48
#define I2C_DMATXWAKE_EN        0x4C
#define I2C_SYSS                0x90
#define I2C_BUF                 0x94
#define I2C_CNT                 0x98
#define I2C_DATA                0x9C
#define I2C_CON                 0xA4
#define I2C_OA                  0xA8
#define I2C_SA                  0xAC
#define I2C_PSC                 0xB0
#define I2C_SCLL                0xB4
#define I2C_SCLH                0xB8
#define I2C_SYSTEST             0xBC
#define I2C_BUFSTAT             0xC0
#define I2C_OA1                 0xC4
#define I2C_OA2                 0xC8
#define I2C_OA3                 0xCC
#define I2C_ACTOA               0xD0
#define I2C_SBLOCK              0xD4

#define I2C_DISABLE             0x0
#define I2C_ENABLE              0x1
#define I2C_RESET               0x2
#define I2C_START               0x3
#define I2C_STOP                0x4


extern void I2C0_Setup(void);
extern void I2C_Master_Ctrl(uint32_t ,uint32_t);
extern void I2C_Master_SlaveAddrs_Set(uint32_t , uint32_t );
extern void I2C_Master_Clear_IRQ(uint32_t , uint32_t );
extern void I2C_Set_Data_Count(uint32_t , uint32_t );
extern void I2C_Send_Data(uint32_t , uint8_t );
extern uint8_t I2C_Get_Data(uint32_t );
extern void I2C0_Setup_InputData(uint32_t , uint8_t *, uint32_t , uint8_t *);
extern void I2C0_Setup_OutputData(uint32_t , uint8_t *, uint32_t );

#endif /* defined(__I2C_H__) */