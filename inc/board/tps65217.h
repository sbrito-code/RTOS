/**
 * Archivo: tps65217.h
 * Función: archivo de definiciones para el uso del I2C
 * Autor: Brito
 **/


#ifndef __TPS65217_H__
#define __TPS65217_H__

// Dirección slave del PMIC en el I2C0
#define  PMIC_TPS65217_I2C_SLAVE_ADDR   0x24

// Registros
#define CHIPID                          0x00
#define POWER_PATH                      0x01
#define INTERRUPT                       0x02
#define CHGCONFIG0                      0x03
#define CHGCONFIG1                      0x04
#define CHGCONFIG2                      0x05
#define CHGCONFIG3                      0x06
#define WLEDCTRL1                       0x07
#define WLEDCTRL2                       0x08
#define MUXCTRL                         0x09
#define STATUS                          0x0A
#define PASSWORD                        0x0B
#define PGOOD                           0x0C
#define DEFPG                           0x0D
#define DEFDCDC1                        0x0E
#define DEFDCDC2                        0x0F
#define DEFDCDC3                        0x10
#define DEFSLEW                         0x11
#define DEFLDO1                         0x12
#define DEFLDO2                         0x13
#define DEFLS1                          0x14
#define DEFLS2                          0x15
#define ENABLE                          0x16
#define DEFUVLO                         0x18
#define SEQ1                            0x19
#define SEQ2                            0x1A
#define SEQ3                            0x1B
#define SEQ4                            0x1C
#define SEQ5                            0x1D
#define SEQ6                            0x1E

#define PROT_LEVEL_NONE                 0x00
#define PROT_LEVEL_1                    0x01
#define PROT_LEVEL_2                    0x02

#define PASSWORD_LOCK_FOR_WRITE         0x00
#define PASSWORD_UNLOCK                 0x7D

#define DCDC_GO                         0x80

#define MASK_ALL_BITS                   0xFF

#define USB_INPUT_CUR_LIMIT_MASK        0x03
#define USB_INPUT_CUR_LIMIT_100MA       0x00
#define USB_INPUT_CUR_LIMIT_500MA       0x01
#define USB_INPUT_CUR_LIMIT_1300MA      0x02
#define USB_INPUT_CUR_LIMIT_1800MA      0x03

#define DCDC_VOLT_SEL_1275MV            0x0F
#define DCDC_VOLT_SEL_1200MV            0x0C
#define DCDC_VOLT_SEL_1100MV            0x08
#define DCDC_VOLT_SEL_0950MV            0x02

#define LDO_MASK                        0x1F
#define LDO_VOLTAGE_OUT_3_3             0x1F

#define PWR_SRC_USB_BITMASK             0x4
#define PWR_SRC_AC_BITMASK              0x8


typedef enum {
    DCDC_900 = 900,
    DCDC_925 = 925,
    DCDC_950 = 950,
    DCDC_975 = 975,
    DCDC_1000 = 1000,
    DCDC_1025 = 1025,
    DCDC_1050 = 1050,
    DCDC_1075 = 1075,
    DCDC_1100 = 1100,
    DCDC_1125 = 1125,
    DCDC_1150 = 1150,
    DCDC_1175 = 1175,
    DCDC_1200 = 1200,
    DCDC_1225 = 1225,
    DCDC_1250 = 1250,
    DCDC_1275 = 1275, 
    DCDC_1300 = 1300,
    DCDC_1325 = 1325,
    DCDC_1350 = 1350,
    DCDC_1375 = 1375,
    DCDC_1400 = 1400,
    DCDC_1425 = 1425,
    DCDC_1450 = 1450,
    DCDC_1475 = 1475, 
    DCDC_1500 = 1500,
    DCDC_1550 = 1550,
    DCDC_1600 = 1600,
    DCDC_1650 = 1650,
    DCDC_1700 = 1700,
    DCDC_1750 = 1750,
    DCDC_1800 = 1800,
    DCDC_1850 = 1850,  
    DCDC_1900 = 1900,
    DCDC_1995 = 1995,
    DCDC_2000 = 2000,
    DCDC_2050 = 2050,
    DCDC_2100 = 2100,
    DCDC_2150 = 2150,
    DCDC_2200 = 2200,
    DCDC_2250 = 2250,
    DCDC_2300 = 2300,
    DCDC_2350 = 2350,
    DCDC_2400 = 2400,
    DCDC_2450 = 2450,
    DCDC_2500 = 2500,
    DCDC_2550 = 2550,
    DCDC_2600 = 2600,
    DCDC_2650 = 2650, 
    DCDC_2700 = 2700,
    DCDC_2750 = 2750,
    DCDC_2800 = 2800,
    DCDC_2850 = 2850,
    DCDC_2900 = 2900,
    DCDC_3000 = 3000,
    DCDC_3100 = 3100,
    DCDC_3200 = 3200, 
    DCDC_3300 = 3300,
    DCDC_3300a = 3300,
    DCDC_3300b = 3300,
    DCDC_3300c = 3300,
    DCDC_3300d = 3300,
    DCDC_3300e = 3300,
    DCDC_3300f = 3300,
    DCDC_3300g = 3300               
} DCDC_voltage;

typedef enum {
    LDO_A_1000 = 1000, 
    LDO_A_1100 = 1100, 
    LDO_A_1200 = 1200, 
    LDO_A_1250 = 1250, 
    LDO_A_1300 = 1300, 
    LDO_A_1350 = 1350, 
    LDO_A_1400 = 1400, 
    LDO_A_1500 = 1500, 
    LDO_A_1600 = 1600, 
    LDO_A_1800 = 1800, 
    LDO_A_2500 = 2500,
    LDO_A_2750 = 2750,
    LDO_A_2800 = 2800,
    LDO_A_3000 = 3000,
    LDO_A_3100 = 3100,
    LDO_A_3300 = 3300
} LDO_A_voltage;

typedef enum {
    LDO_B_1500 = 1500, 
    LDO_B_1550 = 1550, 
    LDO_B_1600 = 1600, 
    LDO_B_1650 = 1650, 
    LDO_B_1700 = 1700, 
    LDO_B_1750 = 1750, 
    LDO_B_1800 = 1800, 
    LDO_B_1850 = 1850, 
    LDO_B_1900 = 1900, 
    LDO_B_2000 = 2000, 
    LDO_B_2100 = 2100,
    LDO_B_2200 = 2200,
    LDO_B_2300 = 2300,
    LDO_B_2400 = 2400,
    LDO_B_2450 = 2450,
    LDO_B_2500 = 2500,
    LDO_B_2550 = 2550,
    LDO_B_2600 = 2600,
    LDO_B_2650 = 2650,
    LDO_B_2700 = 2700,
    LDO_B_2750 = 2750,
    LDO_B_2800 = 2800,
    LDO_B_2850 = 2850,
    LDO_B_2900 = 2900,
    LDO_B_2950 = 2950,
    LDO_B_3000 = 3000,
    LDO_B_3050 = 3050,
    LDO_B_3100 = 3100,
    LDO_B_3150 = 3150,
    LDO_B_3200 = 3200,
    LDO_B_3250 = 3250,
    LDO_B_3300 = 3300
} LDO_B_voltage;

static const DCDC_voltage DCDC_voltage_table[64] = {DCDC_900,DCDC_925,DCDC_950,DCDC_975,DCDC_1000,DCDC_1025,DCDC_1050,
DCDC_1075,DCDC_1100,DCDC_1125,DCDC_1150,DCDC_1175,DCDC_1200,DCDC_1225,DCDC_1250,DCDC_1275,DCDC_1300,DCDC_1325,DCDC_1350,
DCDC_1375,DCDC_1400,DCDC_1425,DCDC_1450,DCDC_1475,DCDC_1500,DCDC_1550,DCDC_1600,DCDC_1650,DCDC_1700,DCDC_1750,DCDC_1800,
DCDC_1850,DCDC_1900,DCDC_1995,DCDC_2000,DCDC_2050,DCDC_2100,DCDC_2150,DCDC_2200,DCDC_2250,DCDC_2300,DCDC_2350,DCDC_2400,
DCDC_2450,DCDC_2500,DCDC_2550,DCDC_2600,DCDC_2650,DCDC_2700,DCDC_2750,DCDC_2800,DCDC_2850,DCDC_2900,DCDC_3000,DCDC_3100,
DCDC_3200,DCDC_3300,DCDC_3300a,DCDC_3300b,DCDC_3300c,DCDC_3300d,DCDC_3300e,DCDC_3300f,DCDC_3300g};

static const LDO_A_voltage LDO_A_voltage_table[16] = {LDO_A_1000,LDO_A_1100,LDO_A_1200,LDO_A_1250,LDO_A_1300,LDO_A_1350,
LDO_A_1400,LDO_A_1500,LDO_A_1600,LDO_A_1800,LDO_A_2500,LDO_A_2750,LDO_A_2800,LDO_A_3000,LDO_A_3100,LDO_A_3300};

static const LDO_B_voltage LDO_B_voltage_table[32] = {LDO_B_1500,LDO_B_1550,LDO_B_1600,LDO_B_1650,LDO_B_1700,LDO_B_1750,
LDO_B_1800,LDO_B_1850,LDO_B_1900,LDO_B_2000,LDO_B_2100,LDO_B_2200,LDO_B_2300,LDO_B_2400,LDO_B_2450,LDO_B_2500,LDO_B_2550,
LDO_B_2600,LDO_B_2650,LDO_B_2700,LDO_B_2750,LDO_B_2800,LDO_B_2850,LDO_B_2900,LDO_B_2950,LDO_B_3000,LDO_B_3050,LDO_B_3100,
LDO_B_3150,LDO_B_3200,LDO_B_3250,LDO_B_3300};

extern void TPS65217_Read(uint8_t, uint8_t *);
extern void TPS65217_Write(uint8_t , uint8_t , uint8_t , uint8_t );
extern void TPS65217_V_Update(uint8_t , uint8_t );
extern void TPS65217_Power_Status(void);

#endif /* defined(__TPS65217_H__) */