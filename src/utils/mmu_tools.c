/**
 * Archivo: mmu_tools.c
 * Función: Tiene las funciones necesarias para leer y escribir registros de la MMU.
 * Autor: Brito Sergio Sebastian
 * Referencia: 
 *             Ref. 1: ARM Architectural Reference Manual ARMv7-A and ARMv7-R Edition (ARM)
 *             Ref. 2: https://developer.arm.com/documentation/ddi0406/b/System-Level-Architecture/Virtual-Memory-System-Architecture--VMSA-/Translation-tables/Translation-table-walks
 *             Ref. 3: https://stackoverflow.com/questions/23328471/problems-enabling-mmu-on-arm-cortex-a
 **/

#include "../../inc/utils/mmu_tools.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/debug_tools.h"
#include "../../inc/utils/low_level_cpu_access.h"

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) ID_MMFR0 MMU_Get_ID_MMFR0(void)
{
    ID_MMFR0 mmfr0;

    asm("MRC p15, 0, R0, c0, c1, 4");
    asm("STR R0,%0" : "=m"(mmfr0));

    return mmfr0;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) ID_MMFR1 MMU_Get_ID_MMFR1(void)
{
    ID_MMFR1 mmfr1;

    asm("MRC p15, 0, R0, c0, c1, 5");
    asm("STR R0,%0" : "=m"(mmfr1));

    return mmfr1;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) ID_MMFR2 MMU_Get_ID_MMFR2(void)
{
    ID_MMFR2 mmfr2;

    asm("MRC p15, 0, R0, c0, c1, 6");
    asm("STR R0,%0" : "=m"(mmfr2));

    return mmfr2;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) ID_MMFR3 MMU_Get_ID_MMFR3(void)
{
    ID_MMFR3 mmfr3;

    asm("MRC p15, 0, R0, c0, c1, 7");
    asm("STR R0,%0" : "=m"(mmfr3));

    return mmfr3;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) TTBCR MMU_Get_TTBCR(void)
{
    TTBCR ttbcr;

    asm("MRC p15, 0, R0, c2, c0, 2");
    asm("STR R0,%0" : "=m"(ttbcr));

    return ttbcr;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_TTBCR(TTBCR ttbcr)
{
    asm("LDR R0,%0" : "=m"(ttbcr));
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    asm("MCR p15, 0, R0, c2, c0, 2");
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) DACR MMU_Get_DACR(void)
{
    DACR dacr;

    asm("MRC p15, 0, R0, c3, c0, 0");
    asm("STR R0,%0" : "=m"(dacr));

    return dacr;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_DACR(DACR dacr)
{
    asm("LDR R0,%0" : "=m"(dacr));
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    asm("MCR p15, 0, R0, c3, c0, 0");
}


/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) TTBR0 MMU_Get_TTBR0()
{
    TTBR0 ttbr0;

    asm("MRC p15, 0, R0, c2, c0, 0");
    asm("STR R0,%0" : "=m"(ttbr0));

    return ttbr0;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_TTBR0(TTBR0 ttbr0)
{
    asm("LDR R0,%0" : "=m"(ttbr0.ttbr0));
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    asm("MCR p15, 0, R0, c2, c0, 0");
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) TTBR1 MMU_Get_TTBR1()
{
    TTBR1 ttbr1;

    asm("MRC p15, 0, R0, c2, c0, 1");
    asm("STR R0,%0" : "=m"(ttbr1));

    return ttbr1;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_TTBR1(TTBR1 ttbr1)
{
    asm("LDR R0,%0" : "=m"(ttbr1));
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    asm("MCR p15, 0, R0, c2, c0, 1");
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) SCTLR MMU_Get_SCTLR()
{
    SCTLR sctlr;

    asm("MRC p15, 0, R0, c1, c0, 0");
    asm("STR R0,%0" : "=m"(sctlr.sctlr));

    return sctlr;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_SCTLR(SCTLR sctlr)
{
    asm("LDR R0,%0" : "=m"(sctlr.sctlr));
    asm("ISB");                     // Instruction Synchronization Barrier
    asm("DSB");                     // Data Synchronization Barrier
    asm("MCR p15, 0, R0, c1, c0, 0");
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) uint32_t MMU_Get_VBAR()
{
    uint32_t vbar;

    asm("MRC p15, 0, R0, c12, c0, 0");
    asm("STR R0,%0" : "=m"(vbar));

    return vbar;
}

/**
 * @brief 
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Set_VBAR(uint32_t vbar)
{
    asm("LDR R0,%0" : "=m"(vbar));
    asm("MCR p15, 0, R0, c12, c0, 0");
}

/**
 * @brief Esta función obtiene el valor de la dirección física de la primer tabla de traducción de la MMU
 * 
 */
__attribute__((section(".text_pub"))) uint32_t MMU_Get_FirstLevelTranslationTable_PhysicalAddress(void)
{
    TTBCR ttbcr = MMU_Get_TTBCR();
    TTBR0 ttbr0 = MMU_Get_TTBR0();
    //TTBR1 ttbr1 = MMU_Get_TTBR1();
    uint8_t tt_size = ttbcr.T0SZ;
    uint32_t tt_ph_addr = 0;

    if(tt_size == 0)
    {
        // Solamente se usa TTBR0 para la traducción, ver TRM B3.5.5
        tt_ph_addr = ttbr0.ttbr0 & 0xFFFFC000;
    }

    return tt_ph_addr;
}

/**
 * @brief Invalida todas las entradas de la TLB siguiendo el TRM B3.18.7
 * 
 */
__attribute__((section(".text_pub"))) void MMU_Invalidate_TLB(void)
{
    asm("MCR p15, 0, R0, c8, c6, 0"); // Invalidate entire DATA TLB
    asm("MCR p15, 0, R0, c8, c5, 0"); // Invalidate entire INSTRUCTION TLB
    asm("MCR p15, 0, R0, c8, c7, 0"); // Invalidate entire UNIFIED TLB
}

/**
 * @brief Esta función recorre la estructura de tablas de paginación, e imprime las direcciones mapeadas
 * 
 */
__attribute__((section(".text_pub"))) void MMU_PrintMappedMemory(void)
{
    FIRSTLEVEL_PAGETABLE_DESCRIPTOR firstlevel_pagetable_desc;
    //FIRSTLEVEL_SECTION_DESCRIPTOR firstlevel_section_desc;
    SECONDLEVEL_LARGEPAGE_DESCRIPTOR secondlevel_largepage_desc;
    SECONDLEVEL_SMALLPAGE_DESCRIPTOR secondlevel_smallpage_desc;
    TTBCR ttbcr = MMU_Get_TTBCR();
    uint8_t tt_size = ttbcr.T0SZ;
    uint32_t firstlevel_base_physical_address = MMU_Get_FirstLevelTranslationTable_PhysicalAddress();
    uint32_t secondlevel_base_physical_address;
    uint32_t firstlevel_index = 0;
    uint32_t secondlevel_index = 0;
    uint32_t descriptor = 0;
    uint32_t page_physical_address;
    uint32_t page_virtual_address;
    uint32_t firstlevel_offset = 0;
    uint32_t secondlevel_offset = 0;
    uint32_t section_base_physical_address = 0;

    // TODO: Habria que desactivar la MMU acá para poder acceder a todas estas direcciones sin problema? Y activarla al final?

    ConsoleUtilsPrintf("\r\n---------------------------------------------");
    ConsoleUtilsPrintf("\r\nMapped memory addresses:");

    if(tt_size == 0)
    {
        // Solamente se usa TTBR0 para la traducción, ver TRM B3.5.5
        // La primera pagina es de 16Kb si o si cuando N = 0, por eso el 0x4000
        // Con este for se recorre el primer nivel
        for(firstlevel_offset = 0; firstlevel_offset < 0x4000; firstlevel_offset += 4)
        {
            descriptor = _READ_32(firstlevel_base_physical_address + firstlevel_offset);
            if((descriptor & 0b11) != INVALID && (descriptor & 0b11) != RESERVED)
            {
                // Si el descriptor no es invalido (primeros bits 0b00) y no es el descriptor reservado (primeros bits 0b11) entro al if
                if((descriptor & 0b11) == PAGETABLE)
                {
                    // ConsoleUtilsPrintf("\r\n\tHay un descriptor de PAGETABLE en 0x%x. Contenido 0x%x",firstlevel_base_physical_address + firstlevel_offset,descriptor);
                    // Es un descriptor de Page Table
                    firstlevel_pagetable_desc.descriptor = descriptor;
                    secondlevel_base_physical_address = firstlevel_pagetable_desc.descriptor & 0xFFFFFC00;
                    // Cada Page Table tiene 256 entradas, asi que las recorro todas
                    // ConsoleUtilsPrintf("\r\n\tsecondlevel_base_physical_address: 0x%x",secondlevel_base_physical_address);
                    for(secondlevel_offset = 0; secondlevel_offset < 256*4; secondlevel_offset += 4)
                    {
                        descriptor = _READ_32(secondlevel_base_physical_address + secondlevel_offset);
                        // ConsoleUtilsPrintf("\r\n\tIndex %d dirección: 0x%x. Contenido 0x%x",secondlevel_offset,secondlevel_base_physical_address + secondlevel_offset,descriptor);
                        if((descriptor & 0b11) == LARGEPAGE)
                        {
                            // Es un descriptor de Large Page
                            // ConsoleUtilsPrintf("\r\n\tHay un descriptor de LARGEPAGE en 0x%x. Contenido 0x%x",secondlevel_base_physical_address + secondlevel_offset,descriptor);
                            secondlevel_largepage_desc.descriptor = descriptor;
                            page_physical_address = secondlevel_largepage_desc.descriptor & 0xFFFF0000;
                            firstlevel_index = firstlevel_offset >> 2;
                            secondlevel_index = secondlevel_offset >> 2;
                            page_virtual_address = (firstlevel_index << 20) | (secondlevel_index << 12);
                            // La pagina que arranca en page_physical_addres y es de 64k está bien mapeada
                            // ConsoleUtilsPrintf("\r\n\tLarge page: 0x%x/0x%x -> 0x%x/0x%x",page_virtual_address,page_virtual_address+0xFFFF,page_physical_address,page_physical_address+0xFFFF);
                        }
                        else if((descriptor & 0b10) == 2)
                        {
                            // Es un descriptor de Small Page
                            // ConsoleUtilsPrintf("\r\n\tHay un descriptor de SMALLPAGE en 0x%x. Contenido 0x%x",secondlevel_base_physical_address + secondlevel_offset,descriptor);
                            secondlevel_smallpage_desc.descriptor = descriptor;
                            page_physical_address = secondlevel_smallpage_desc.descriptor & 0xFFFFF000;
                            firstlevel_index = firstlevel_offset >> 2;
                            secondlevel_index = secondlevel_offset >> 2;
                            page_virtual_address = (firstlevel_index << 20) | (secondlevel_index << 12);
                            // La pagina que arranca en page_physical_addres y es de 4k está bien mapeada
                            ConsoleUtilsPrintf("\r\n\tSmall page: 0x%x/0x%x -> 0x%x/0x%x : Descriptor 1 0x%x : Descriptor 2 0x%x",page_virtual_address,page_virtual_address+0xFFF,page_physical_address,page_physical_address+0xFFF,firstlevel_pagetable_desc.descriptor,descriptor);
                        }
                    }
                }
                else if((descriptor & 0b10) == 2 && (descriptor & 0x40000) == 0)
                {
                    // Es un descriptor de Section
                    //firstlevel_section_desc.descriptor = descriptor;
                    firstlevel_index = firstlevel_offset >> 2;
                    section_base_physical_address = descriptor & 0xFFF00000;
                    page_virtual_address = (firstlevel_index << 20);
                    // La pagina que arranca en section_base_physical_address y es de 1Mb está bien mapeada
                    ConsoleUtilsPrintf("\r\n\tSection: 0x%x/0x%x -> 0x%x/0x%x : Descriptor 0x%x",page_virtual_address,page_virtual_address+0x100000,section_base_physical_address,section_base_physical_address+0x100000,descriptor);     
                }
                else
                {
                    // Es un descriptor de SuperSection
                    // TODO: implementar
                }
            }
        }

    }
    else
    {
        // TODO: implementar
        ConsoleUtilsPrintf("\r\nTTBCR.T0SZ != 0 no está soportado todavía! No se recorrerá la estructura de tablas de paginación.");
    }

    ConsoleUtilsPrintf("\r\n---------------------------------------------");
}

/**
 * @brief Función que devuelve el registro PAR de la MMU, a partir de una determinada dirección virtual va
 * 
 */
__attribute__((section(".text_pub"))) uint32_t MMU_TranslateVAToPA(uint32_t va)
{
    uint32_t pa = 0;

    asm("LDR R0,%0" : "=m"(va));
    asm("MCR p15, 0, R0, c7, c8, 0");
    asm("MRC p15, 0, R0, c7, c4, 0");
    asm("STR R0,%0" : "=m"(pa));
    return pa;
}