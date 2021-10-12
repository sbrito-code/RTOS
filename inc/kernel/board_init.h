/**
 * Archivo: board_init.h
 * Función: archivo de definiciones para la inicialización de la BBB
 * Autor: Brito Sergio Sebastian
 **/

#ifndef __BOARD_INIT_H
#define __BOARD_INIT_H

#include "../utils/types.h"
#include "../board/tps65217.h"

typedef union {
    uint32_t bbb_info;
    struct  {
            uint32_t reserved : 1;
            uint32_t mfgr : 11;
            uint32_t partnum : 16;
            uint32_t devrev : 4;
            };
} BBB_INFO;

typedef union {
    uint32_t efuse_opp;
    struct  {
            uint32_t arm_mpu_max_freq : 13;
            uint32_t reserved1 : 3;
            uint32_t pkg_type : 2;
            uint32_t reserved2 : 14;
            };
} EFUSE_OPP;


/* EFUSE bit for OPP100 275Mhz - 1.1v */
#define EFUSE_OPP100_275_MASK                (0x00000001u)
#define EFUSE_OPP100_275                     (0x0u)

/* EFUSE bit for OPP100 500Mhz - 1.1v */
#define EFUSE_OPP100_500_MASK                (0x00000002u)
#define EFUSE_OPP100_500                     (0x1u)

/* EFUSE bit for OPP120 600Mhz - 1.2v */
#define EFUSE_OPP120_600_MASK                (0x00000004u)
#define EFUSE_OPP120_600                     (0x2u)

/* EFUSE bit for OPP TURBO 720Mhz - 1.26v */
#define EFUSE_OPPTB_720_MASK                 (0x00000008u)
#define EFUSE_OPPTB_720                      (0x3u)

/* EFUSE bit for OPP50 300Mhz - 950mv */
#define EFUSE_OPP50_300_MASK                 (0x00000010u)
#define EFUSE_OPP50_300                      (0x4u)

/* EFUSE bit for OPP100 300Mhz - 1.1v */
#define EFUSE_OPP100_300_MASK                (0x00000020u)
#define EFUSE_OPP100_300                     (0x5u)

/* EFUSE bit for OPP100 600Mhz - 1.1v */
#define EFUSE_OPP100_600_MASK                (0x00000040u)
#define EFUSE_OPP100_600                     (0x6u)

/* EFUSE bit for OPP120 720Mhz - 1.2v */
#define EFUSE_OPP120_720_MASK                (0x00000050u)
#define EFUSE_OPP120_720                     (0x7u)

/* EFUSE bit for OPP TURBO 800Mhz - 1.26v */
#define EFUSE_OPPTB_800_MASK                 (0x00000100u)
#define EFUSE_OPPTB_800                      (0x8u)

/* EFUSE bit for OPP NITRO 1000Mhz - 1.325v */
#define EFUSE_OPPNT_1000_MASK                (0x00000200u)
#define EFUSE_OPPNT_1000                     (0x9u)

#define EFUSE_OPP_MAX                        (EFUSE_OPPNT_1000 + 1)


typedef struct oppConfig
{
    uint32_t pllMult;
    uint32_t pmicVolt;
} tOPPConfig;

#define MPUPLL_M_275_MHZ        275u
#define MPUPLL_M_300_MHZ        300u
#define MPUPLL_M_500_MHZ        500u
#define MPUPLL_M_600_MHZ        600u
#define MPUPLL_M_720_MHZ        720u
#define MPUPLL_M_800_MHZ        800u
#define MPUPLL_M_1000_MHZ       1000u

#define PMIC_VOLT_SEL_0950MV    DCDC_VOLT_SEL_0950MV
#define PMIC_VOLT_SEL_1100MV    DCDC_VOLT_SEL_1100MV
#define PMIC_VOLT_SEL_1200MV    DCDC_VOLT_SEL_1200MV
#define PMIC_VOLT_SEL_1260MV    DCDC_VOLT_SEL_1275MV
#define PMIC_VOLT_SEL_1325MV    0x11u


#endif /* defined(__BOARD_INIT_H) */