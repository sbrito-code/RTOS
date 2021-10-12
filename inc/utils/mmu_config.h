// Define translation table base 0 address
#define DIR_TTBR0 0x80020000
// Define exceptions VMSA address
#define DIR_VBAR 0x4030CE00
//Define base of TTBR0 kernel for MMU
#define TTBR0_KERNEL 0x80020000
//Define base of TTBR0 task0 for MMU
#define TTBR0_TASK0  0x80420000
//Define base of TTBR0 task1 for MMU
#define TTBR0_TASK1  0x80820000
//Define base of TTBR0 task2 for MMU
#define TTBR0_TASK2  0x80C20000
//Define base of TTBR0 task3 for MMU
#define TTBR0_TASK3  0x81020000

#define MASK_FIRST_LEVEL  0xFFF00000
#define MASK_SECOND_LEVEL 0x000FF000
#define MASK_OFFSET_LEVEL 0x00000FFF

#define FIRST_LEVEL  20
#define SECOND_LEVEL 12
#define OFFSET_LEVEL 0 
#define MASK_TABLE(address,mask,level) ((address&mask)>>level)


#define OFFSET_FIRST_LEVEL(address) ((address&MASK_FIRST_LEVEL)>>FIRST_LEVEL)
#define OFFSET_SECOND_LEVEL(address) ((address&MASK_SECOND_LEVEL)>>SECOND_LEVEL)


#define SHIFT_LEFT(value,shift)  (value << shift)
#define SHIFT_RIGHT(value,shift) (value >> shift)

#define MASK_12_MSB(data) (data & 0xFFF00000)
#define MASK_20_MSB(data) (data & 0xFFFFF000)
#define MASK_22_MSB(data) (data & 0xFFFFFC00)



/**
 * @fn void MMU_Write_Tables(uint32_t va, uint32_t fa)
 * @brief         Write positions of MMU tables
 * @param         va: virtual address
 * @param         fa: fisical address
 * @return        void
 **/
void MMU_Write_Tables(uint32_t va, uint32_t fa, uint32_t size, uint32_t ttbr0);

/**
 * @fn void MMU_config(void)
 * @brief         Config MMU
 * @return        void
 **/
void MMU_config(void);

/**
 * @fn void MMU_enable(void)
 * @brief         Enable MMU
 * @return        void
 **/
void MMU_enable(void);


