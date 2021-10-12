/**
 * Archivo: ddr.h
 * Función: definición para el uso dela memoria volátil para BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/


// Registros DDR PHY
// Command Macro Registers
#define DDR_CMD0_REG_PHY_CTRL_SLAVE_RATIO_0 0x01C
#define DDR_CMD0_REG_PHY_DLL_LOCK_DIFF_0    0x028    
#define DDR_CMD0_REG_PHY_INVERT_CLKOUT_0    0x02C
#define DDR_CMD1_REG_PHY_CTRL_SLAVE_RATIO_0 0x050
#define DDR_CMD1_REG_PHY_DLL_LOCK_DIFF_0    0x05C
#define DDR_CMD1_REG_PHY_INVERT_CLKOUT_0    0x060
#define DDR_CMD2_REG_PHY_CTRL_SLAVE_RATIO_0 0x084
#define DDR_CMD2_REG_PHY_DLL_LOCK_DIFF_0    0x090
#define DDR_CMD2_REG_PHY_INVERT_CLKOUT_0    0x094
// Data Macro Registers
#define DDR_DATA0_REG_PHY_RD_DQS_SLAVE_RATIO_0      0x0C8
#define DDR_DATA0_REG_PHY_WR_DQS_SLAVE_RATIO_0      0x0DC
#define DDR_DATA0_REG_PHY_WRLVL_INIT_RATIO_0        0x0F0
#define DDR_DATA0_REG_PHY_WRLVL_INIT_MODE_0         0x0F8
#define DDR_DATA0_REG_PHY_GATELVL_INIT_RATIO_0      0x0FC
#define DDR_DATA0_REG_PHY_GATELVL_INIT_MODE_0       0x104
#define DDR_DATA0_REG_PHY_FIFO_WE_SLAVE_RATIO_0     0x108
#define DDR_DATA0_REG_PHY_DQ_OFFSET_0               0x11C
#define DDR_DATA0_REG_PHY_WR_DATA_SLAVE_RATIO_0     0x120
#define DDR_DATA0_REG_PHY_USE_RANK0_DELAYS          0x134
#define DDR_DATA0_REG_PHY_DLL_LOCK_DIFF_0           0x138
#define DDR_DATA1_REG_PHY_RD_DQS_SLAVE_RATIO_0      0x16C
#define DDR_DATA1_REG_PHY_WR_DQS_SLAVE_RATIO_0      0x180
#define DDR_DATA1_REG_PHY_WRLVL_INIT_RATIO_0        0x194
#define DDR_DATA1_REG_PHY_WRLVL_INIT_MODE_0         0x19C
#define DDR_DATA1_REG_PHY_GATELVL_INIT_RATIO_0      0x1A0
#define DDR_DATA1_REG_PHY_GATELVL_INIT_MODE_0       0x1A8
#define DDR_DATA1_REG_PHY_FIFO_WE_SLAVE_RATIO_0     0x1AC
#define DDR_DATA1_REG_PHY_DQ_OFFSET_1               0x1C0
#define DDR_DATA1_REG_PHY_WR_DATA_SLAVE_RATIO_0     0x1C4
#define DDR_DATA1_REG_PHY_USE_RANK0_DELAYS          0x1D8
#define DDR_DATA1_REG_PHY_DLL_LOCK_DIFF_0           0x1DC

// Registros EMIF
#define EMIF_EMIF_MOD_ID_REV        0x0
#define EMIF_STATUS                 0x4
#define EMIF_SDRAM_CONFIG           0x8
#define EMIF_SDRAM_CONFIG_2         0xC
#define EMIF_SDRAM_REF_CTRL         0x10
#define EMIF_SDRAM_REF_CTRL_SHDW    0x14
#define EMIF_SDRAM_TIM_1            0x18
#define EMIF_SDRAM_TIM_1_SHDW       0x1C
#define EMIF_SDRAM_TIM_2            0x20
#define EMIF_SDRAM_TIM_2_SHDW       0x24
#define EMIF_SDRAM_TIM_3            0x28
#define EMIF_SDRAM_TIM_3_SHDW       0x2C
#define EMIF_PWR_MGMT_CTRL          0x38
#define EMIF_PWR_MGMT_CTRL_SHDW     0x3C
#define EMIF_INT_CONFIG             0x54
#define EMIF_INT_CFG_VAL_1          0x58
#define EMIF_INT_CFG_VAL_2          0x5C
#define EMIF_PERF_CNT_1             0x80
#define EMIF_PERF_CNT_2             0x84
#define EMIF_PERF_CNT_CFG           0x88
#define EMIF_PERF_CNT_SEL           0x8C
#define EMIF_PERF_CNT_TIM           0x90
#define EMIF_READ_IDLE_CTRL         0x98
#define EMIF_READ_IDLE_CTRL_SHDW    0x9C
#define EMIF_IRQSTATUS_RAW_SYS      0xA4
#define EMIF_IRQSTATUS_SYS          0xAC
#define EMIF_IRQENABLE_SET_SYS      0xB4
#define EMIF_IRQENABLE_CLR_SYS      0xBC
#define EMIF_ZQ_CONFIG              0xC8
#define EMIF_RDWR_LVL_RMP_WIN       0xD4
#define EMIF_RDWR_LVL_RMP_CTRL      0xD8
#define EMIF_RDWR_LVL_CTRL          0xDC
#define EMIF_DDR_PHY_CTRL_1         0xE4
#define EMIF_DDR_PHY_CTRL_1_SHDW    0xE8
#define EMIF_PRI_COS_MAP            0x100
#define EMIF_CONNID_COS_1_MAP       0x104
#define EMIF_CONNID_COS_2_MAP       0x108
#define EMIF_RD_WR_EXEC_THRSH       0x120



// Direcciones base
#define DDR_PHY_ADDR 0x44E12000                             // TRM 2.1 - Tabla 2-2 - L4
#define EMIF_ADDR 0x4C000000                                // TRM 2.1 - Tabla 2-1 - L3

extern const void _DDR0_INIT;

extern void DDR3_Init(void);
extern void Clean_DDR(void);