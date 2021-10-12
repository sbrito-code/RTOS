/* 
    Linker Script
    Autor: Brito Sergio Sebastian
    Referencia: los códigos desarrollados fueron tomados a partir de diferentes referencias y en base al TRM. El objetivo de esta recopilación
            fue darle un enfoque didáctico para el alumno, con comentarios pertinentes y referencias a la documentación disponible.
            Ref. 1: https://github.com/allexoll/BBB-BareMetal
            Ref. 2: https://github.com/auselen/down-to-the-bone
            Ref. 3: https://github.com/mvduin/bbb-asm-demo
            Ref. 4: Starterware de Texas Instruments
            Ref. 5: AM335x ARM Cortex-A8 - Technical Reference Manual 
            Ref. 6: ARM Architectural Reference Manual ARMv7-A and ARMv7-R Edition (ARM)
*/

/* 
    Definiciones necesarias: formato de salida, arquitectura y punto de entrada
*/
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_reset_vector)


/* 
    Definiciones de simbolos necesarios
*/
_PUBLIC_RAM_INIT      = 0x402f0400;
_PUBLIC_STACK_INIT    = 0x4030B800;
_ISR_TABLE            = 0x4030CE00;
_DDR0_INIT            = 0x80000000;
_TEXT_KERNEL_VMA      = 0x80010000;
_BSS_KERNEL_VMA       = 0x80011000;
_DATA_KERNEL_VMA      = 0x80012000;
_TABLE_PAGINATION_VMA = 0x80020000;

_TABLE_PAGINATION_TASK0_RAM = 0X80420000;
_TABLE_PAGINATION_TASK1_RAM = 0X80820000;
_TABLE_PAGINATION_TASK2_RAM = 0X80C20000;
_TABLE_PAGINATION_TASK3_RAM = 0X81020000;

/* Task 0 */
_TEXT_TASK0_RAM      = 0X82500000;
_BSS_TASK0_RAM       = 0X82501000;
_DATA_TASK0_RAM      = 0X82502000;
_STACK_IRQ_TASK0_RAM = 0X90001000;
_STACK_SYS_TASK0_RAM = 0X90002000;
_STACK_SVC_TASK0_RAM = 0X90003000;
_STACK_UND_TASK0_RAM = 0X90004000;
_STACK_ABT_TASK0_RAM = 0X90005000;

/* Task 1 */
_TEXT_TASK1_RAM      = 0X82510000;
_BSS_TASK1_RAM       = 0X82511000;
_DATA_TASK1_RAM      = 0X82512000;
_STACK_IRQ_TASK1_RAM = 0X90011000;
_STACK_SYS_TASK1_RAM = 0X90012000;
_STACK_SVC_TASK1_RAM = 0X90013000;
_STACK_UND_TASK1_RAM = 0X90014000;
_STACK_ABT_TASK1_RAM = 0X90015000;

/* Task 2 */
_TEXT_TASK2_RAM      = 0X82520000;
_BSS_TASK2_RAM       = 0X82521000;
_DATA_TASK2_RAM      = 0X82522000;
_STACK_IRQ_TASK2_RAM = 0X90021000;
_STACK_SYS_TASK2_RAM = 0X90022000;
_STACK_SVC_TASK2_RAM = 0X90023000;
_STACK_UND_TASK2_RAM = 0X90024000;
_STACK_ABT_TASK2_RAM = 0X90025000;

/* Task 3 */
_TEXT_TASK3_RAM      = 0X82530000;
_BSS_TASK3_RAM       = 0X82531000;
_DATA_TASK3_RAM      = 0X82532000;
_STACK_IRQ_TASK3_RAM = 0X90031000;
_STACK_SYS_TASK3_RAM = 0X90032000;
_STACK_SVC_TASK3_RAM = 0X90033000;
_STACK_UND_TASK3_RAM = 0X90034000;
_STACK_ABT_TASK3_RAM = 0X90035000;

C_STACK_SIZE   = 4K;
IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;

/* 
    Definición del mapa de memoria
*/
MEMORY
{
	/* El mapa de memoria de la Public RAM delimita la zona de "Descarga de Imagen" 
    entre 0x402F0400 y 0x4030B7FF. Por lo tanto, definimos el origen en 0x402F0400 y
    un tamabaño de 0x1B400 (109KB). TRM - 26.1.3.2
    */
    public_ram	: org = _PUBLIC_RAM_INIT, len = 0x1B400 
	/* El mapa de memoria de la Public RAM delimita la zona de "Stack Público" 
    entre 0x4030B800 y 0x4030CDFF. Por lo tanto, definimos el origen en 0x4030B800 y
    un tamabaño de 0x1800 (6KB). TRM - 26.1.3.2
    */
    public_stack : org = _PUBLIC_STACK_INIT, len = 0x1800
    /* El mapa de memoria del "L3 Interconnect" mapea la RAM externa entre 0x80000000 
    y 0xBFFFFFFF (1 GB de espacio). La BeagleBone Black dispone de 512 MB de RAM nada
    más, por lo cual, iniciamos en 0x80000000 y le damos 512 MB de longitud.
    TRM - 2.1
    */
    DDR0        : org = _DDR0_INIT, len = 0x20000000
}

/* 
    Definición de las secciones
*/
SECTIONS
{
    . = 0x402f0400;
    .text : { 
        *(._reset_vector_code*)
        *(._start_code*)
        /* *(.text._start)  */
        *(.text_pub*)
        *(.text*)
        *(.rodata*)
        } > public_ram
    
    .data : { *(.data*) } > public_ram

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
        } > public_ram

    _HANDLERS_LMA = .;
    .kernel_handler _DDR0_INIT : AT(_HANDLERS_LMA) 
        {
        *(.kernel_handler*)
        } > DDR0
    _kernel_handler_size_ = SIZEOF(.kernel_handler);

    _TEXT_KERNEL_LMA = _kernel_handler_size_ + LOADADDR(.kernel_handler);
    .kernel_text _TEXT_KERNEL_VMA : AT(_TEXT_KERNEL_LMA)
        {
        *(.kernel_text*)
        } > DDR0
    _kernel_text_size_ = SIZEOF(.kernel_text);

    _BSS_KERNEL_LMA = _kernel_text_size_ + LOADADDR(.kernel_text);
    .kernel_bss _BSS_KERNEL_VMA : AT(_BSS_KERNEL_LMA)
        {
        *(.kernel_bss*)
        } > DDR0
    _kernel_bss_size_ = SIZEOF(.kernel_bss);

    _DATA_KERNEL_LMA = _kernel_bss_size_ + LOADADDR(.kernel_bss);
    .kernel_data _DATA_KERNEL_VMA : AT(_DATA_KERNEL_LMA)
        {
        *(.kernel_data*)
        } > DDR0
    _kernel_data_size_ = SIZEOF(.kernel_data);

    /* Tablas de paginación */
    _TABLE_PAGINATION_LMA = _kernel_data_size_ + LOADADDR(.kernel_data);
    .kernel_table _TABLE_PAGINATION_VMA : AT(_TABLE_PAGINATION_LMA)
        {
        *(.kernel_table*)
        } > DDR0
    _kernel_table_size_ = SIZEOF(.kernel_table);

/************************************************************************************************************/
/* Tablas de paginación de las tareas */
/************************************************************************************************************/
  /* Tablas de paginación task 0*/
    _TABLE_PAGINATION_TASK0_PUBLIC_RAM = _kernel_table_size_ + LOADADDR(.kernel_table);
    .kernel_table_task0 _TABLE_PAGINATION_TASK0_RAM : AT(_TABLE_PAGINATION_TASK0_PUBLIC_RAM)
        {
        *(.kernel_table_task0*)
        } > DDR0
    _kernel_table_task0_size_ = SIZEOF(.kernel_table_task0);

    /* Tablas de paginación task 1*/
    _TABLE_PAGINATION_TASK1_PUBLIC_RAM = _kernel_table_task0_size_ + LOADADDR(.kernel_table_task0);
    .kernel_table_task1 _TABLE_PAGINATION_TASK1_RAM : AT(_TABLE_PAGINATION_TASK1_PUBLIC_RAM)
        {
        *(.kernel_table_task1*)
        } > DDR0
    _kernel_table_task1_size_ = SIZEOF(.kernel_table_task1);

    /* Tablas de paginación task 2*/
    _TABLE_PAGINATION_TASK2_PUBLIC_RAM = _kernel_table_task1_size_ + LOADADDR(.kernel_table_task1);
    .kernel_table_task2 _TABLE_PAGINATION_TASK2_RAM : AT(_TABLE_PAGINATION_TASK2_PUBLIC_RAM)
        {
        *(.kernel_table_task2*)
        } > DDR0
    _kernel_table_task2_size_ = SIZEOF(.kernel_table_task2);

    /* Tablas de paginación task 3*/
    _TABLE_PAGINATION_TASK3_PUBLIC_RAM = _kernel_table_task2_size_ + LOADADDR(.kernel_table_task2);
    .kernel_table_task3 _TABLE_PAGINATION_TASK3_RAM : AT(_TABLE_PAGINATION_TASK3_PUBLIC_RAM)
        {
        *(.kernel_table_task3*)
        } > DDR0
    _kernel_table_task3_size_ = SIZEOF(.kernel_table_task3);
/************************************************************************************************************/




    .stack :
        {
        __stack_start__ = .;
        . += IRQ_STACK_SIZE;
        . = ALIGN(4);
        __irq_stack_top__ = .;

        . += FIQ_STACK_SIZE;
        . = ALIGN(4);
        __fiq_stack_top__ = .;

        . += SVC_STACK_SIZE;
        . = ALIGN(4);
        __svc_stack_top__ = .;

        . += ABT_STACK_SIZE;
        . = ALIGN(4);
        __abt_stack_top__ = .;

        . += UND_STACK_SIZE;
        . = ALIGN(4);
        __und_stack_top__ = .;

        . += C_STACK_SIZE;
        . = ALIGN(4);
        __sys_stack_top__ = .;

        __stack_end__ = .;
        } > public_stack

    . = _ISR_TABLE;
    __isr_table_start__ = .;
}