#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/utils/mmu_tools.h"
#include "../../inc/utils/mmu_config.h"

/**
 * @fn void MMU_set_domain(void)
 * @brief         Set domains
 * @details       Total = 16
 * @return        void
 **/
void MMU_set_domain(void);

/**
 * @fn void MMU_config_ttbr0(void)
 * @brief         Config TTBR0
 * @return        void
 **/
void MMU_config_ttbr0(void);

/**
 * @fn void MMU_config_ttbcr(void)
 * @brief         Config TTBCR
 * @return        void
 **/
void MMU_config_ttbcr(void);

__attribute__((section(".text_pub"))) void MMU_set_domain(void)
{
    DACR dacr_data;

    dacr_data.d0  = DOMAIN_MANAGER;
    dacr_data.d1  = DOMAIN_MANAGER;
    dacr_data.d2  = DOMAIN_MANAGER;
    dacr_data.d3  = DOMAIN_MANAGER;
    dacr_data.d4  = DOMAIN_MANAGER;
    dacr_data.d5  = DOMAIN_MANAGER;
    dacr_data.d6  = DOMAIN_MANAGER;
    dacr_data.d7  = DOMAIN_MANAGER;
    dacr_data.d8  = DOMAIN_MANAGER;
    dacr_data.d9  = DOMAIN_MANAGER;
    dacr_data.d10 = DOMAIN_MANAGER;
    dacr_data.d11 = DOMAIN_MANAGER;
    dacr_data.d12 = DOMAIN_MANAGER;
    dacr_data.d13 = DOMAIN_MANAGER;
    dacr_data.d14 = DOMAIN_MANAGER;
    dacr_data.d15 = DOMAIN_MANAGER;

    MMU_Set_DACR(dacr_data);
}

__attribute__((section(".text_pub"))) void MMU_enable(void)
{
    SCTLR sctlr_data;

    sctlr_data.M = MMUENABLE_YES;


    sctlr_data.A = ALIGNMENT_CHECK_ENABLE;
    // Data and unified caches enabled
    //sctlr_data.C;
    sctlr_data.CP15BEN = CP15BEN_YES;
    //sctlr_data.B;
    //sctlr_data.SW;
    // Branch prediction enable
    //sctlr_data.Z;
    //sctlr_data.V;
    // Normal replacement strategy, for example, random replacement
    sctlr_data.RR = 0;
    // Hardware management of Access flag disabled
    //sctlr_data.HA;
    // Regions with write permission are not forced to XN
    sctlr_data.WXN = 0;
    // Regions with unprivileged write permission are not forced to XN
    sctlr_data.UWXN = 0;
    sctlr_data.FI = 0;
    //sctlr_data.U;
    // Use the FIQ and IRQ vectors from the vector table, see the V bit entry.
    sctlr_data.VE = 0;
    sctlr_data.EE = LITTLE_ENDIAN;
    // Non-maskable FIQ (NMFI) support. B4-1701
    //sctlr_data.NMFI;
    sctlr_data.TRE = TEXREMAP_NO;
    sctlr_data.AFE = AF_NO;
    sctlr_data.TE = 0;
    // Exceptions, including reset, taken in ARM state

    
    MMU_Set_SCTLR(sctlr_data);
}

__attribute__((section(".text_pub"))) void MMU_config_ttbr0(void)
{
    TTBR0 ttbr0_data;

    ttbr0_data.ttbr0 = 0;
    // Cacheable bit. Indicates whether the translation table walk is to Inner Cacheable memory.
    ttbr0_data.IRGN_1 = 0;
    //Not Shareable(SMP)
    ttbr0_data.S = 0;
    // if 00: Normal memory, Outer Non-cacheable.
    ttbr0_data.RGN = 0b00;
    //Ignored if S = 0;
    //ttbr0_data.NOS;
    ttbr0_data.TTB0A = (DIR_TTBR0 & 0xFFFFC000) >> 7;
    
    MMU_Set_TTBR0(ttbr0_data);
}

__attribute__((section(".text_pub"))) void MMU_config_ttbcr(void)
{
    TTBCR ttbcr_data;
    /* N = 0 */
    ttbcr_data.T0SZ = 0b000;
    /* 32-bit translation system */
    ttbcr_data.EAE = 0;

    MMU_Set_TTBCR(ttbcr_data);
}

__attribute__((section(".text_pub"))) void MMU_config(void)
{
    //Establece el valor de N para la TTRB0
    MMU_config_ttbcr();
    // Translation table base 0 address
    MMU_config_ttbr0();
    // Seteo los dominios
    MMU_set_domain();
    // Seteo la base de los vectores
    MMU_Set_VBAR(DIR_VBAR);
}

__attribute__((section(".text_pub")))void MMU_Write_Tables(uint32_t va, uint32_t fa, uint32_t size, uint32_t ttbr0)
{
    FIRSTLEVEL_PAGETABLE_DESCRIPTOR descriptor;

    descriptor.descriptor = 0;
    //B3.5.1 Short-descriptor translation table format descriptors
    descriptor.DESC_TYPE = PAGETABLE;
    //B3.5.2 PXN, Privileged execute-never
    //Genera fallos de permiso si el procesador intenta ejecutar espacio de memoria estando en PL1
    descriptor.PXN = XN_ALLOWEXECUTION;
    //B3.5.2 NS bit Non-secure bit
    //Bit que especifica si la implementación incluye las extensiones de seguridad
    //NS == 0 Access the Secure physical address space.
    descriptor.NS = NS_NONSECURE;
    //B3.3.5 Access to the Secure or Non-secure physical address map
    descriptor.SBZ = 1;
    //B3.7.3 Domains, Short-descriptor format only
    //Selecciona el valor de uno de los 16 domain
    descriptor.DOMAIN = 0b0000;

    SECONDLEVEL_SMALLPAGE_DESCRIPTOR descriptor2;

    descriptor2.descriptor = 0;
    // TEX[2:0] = 0, B = 0, C = 0 => Description: Strongly-ordered, Memory type: Strongly-ordered, Page Shareable: Shareable
    descriptor2.XN = XN_ALLOWEXECUTION;
    descriptor2.DESC_TYPE = SMALLPAGE;
    // B3.8.2 Short-descriptor format memory region attributes, without TEX remap
    // Como SCTLR.TRE = 0, TEX Remap está deshabilitado
    descriptor2.B = WA_YES;
    // B3.8.2 Short-descriptor format memory region attributes, without TEX remap
    // Como SCTLR.TRE = 0, TEX Remap está deshabilitado
    descriptor2.C = WA_YES;
    // B3.7.1 Access permissionsTable B3-8
    // Full access
    descriptor2.AP_10 = 0b11;
    // B3.8.2 Short-descriptor format memory region attributes, without TEX remap
    // Como SCTLR.TRE = 0, TEX Remap está deshabilitado
    
    // ESTO TENIA ORIGINALMENTE !!!!!!!!!!!!!!!!!!!!!
    // descriptor.TEX = STRONGLYORDERED;

    descriptor2.TEX = SHAREABLE;
    // B3.7.1 Access permissionsTable B3-8
    // Read-Write 
    descriptor2.AP_2 = RW;
    descriptor2.S = S_NONSHAREABLE;
    // B3.9.1 Global and process-specific translation table entries
    // nG == 0, The translation is global

    // ESTO TENIA ORIGINALMENTE !!!!!!!!!!!!!!!!!!!!!
    // descriptor.NG = NG_GLOBAL;

    descriptor2.NG = NG_NOTGLOBAL;

    uint32_t size_1_descriptor = (va - size) / 0x100000;
    uint32_t size_2_descriptor = ((va - size) % 0x100000) / 0x1000;

    for(uint32_t i = 0x00 ; i <= (size_1_descriptor * 4) ; i += 0x04)
    {
        uint32_t direction = ttbr0 + SHIFT_LEFT(OFFSET_FIRST_LEVEL(va),2) + i;
        uint32_t value = ttbr0+0x4000 + SHIFT_LEFT((SHIFT_LEFT(OFFSET_FIRST_LEVEL(va),2) + i),8);

        if (size_2_descriptor != 0)
        { 
            descriptor.PAGETABLE_BASE_ADDRESS = SHIFT_RIGHT(value,10);
            _WRITE_32(direction, descriptor.descriptor);
            for (uint32_t j = 0x00 ; j <= (size_2_descriptor * 4) ; j += 0x04)
            {
                descriptor2.SMALLPAGE_BASE_ADDRESS = SHIFT_RIGHT(MASK_20_MSB((fa + (j << 10) + (i << 18))),12);

                direction = ttbr0+0x4000 + SHIFT_LEFT((SHIFT_LEFT(OFFSET_FIRST_LEVEL(va),2) + i),8);
                direction += SHIFT_LEFT(OFFSET_SECOND_LEVEL(va),2) + j;

                _WRITE_32(direction , descriptor2.descriptor);
            }
        }
    }
}