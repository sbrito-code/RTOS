 /**
 * Archivo: debug_tools.c
 * Función: Realiza la inicialización básica de la UART, que oficia de debbuger para la guía de TP.
 * Autor: Brito Sergio Sebastian
 **/

#include "../../inc/board/gpio.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/utils/console_utils.h"

void PrintRegisters(void);
void PrintGPIORegisters(uint16_t);
void PrintGPIOPortRegister(uint16_t , uint32_t );
void PrintIRQRegisters(uint16_t );
void PrintStack(uint32_t );
void PrintStatusRegisters(void);
void PrintPC(void);
void PrintMemoryRegion(uint32_t , uint32_t );

/**
 * @brief Esta función imprime los valores de los registros del procesador. Con mucho cuidado.
 * 
 */
__attribute__((section(".text_pub"))) void PrintRegisters(void)
{
    uint32_t r0_int;
    uint32_t r1_int;
    uint32_t r2_int;
    uint32_t r3_int;
    uint32_t r4_int;
    uint32_t r5_int;
    uint32_t r6_int;
    uint32_t r7_int;
    uint32_t r8_int;
    uint32_t r9_int;
    uint32_t r10_int;
    uint32_t r11_int;
    uint32_t r12_int;
    uint32_t r13_int;
    uint32_t r14_int;

    asm("STR R0,%0" : "=m"(r0_int));
    asm("STR R1,%0" : "=m"(r1_int));
    asm("STR R2,%0" : "=m"(r2_int));
    asm("STR R3,%0" : "=m"(r3_int));
    asm("STR R4,%0" : "=m"(r4_int));
    asm("STR R5,%0" : "=m"(r5_int));
    asm("STR R6,%0" : "=m"(r6_int));
    asm("STR R7,%0" : "=m"(r7_int));
    asm("STR R8,%0" : "=m"(r8_int));
    asm("STR R9,%0" : "=m"(r9_int));
    asm("STR R10,%0" : "=m"(r10_int));
    asm("STR R11,%0" : "=m"(r11_int));
    asm("STR R12,%0" : "=m"(r12_int));
    asm("STR R13,%0" : "=m"(r13_int));
    asm("STR R14,%0" : "=m"(r14_int));

    /*
    * Se guardan los registros en el STACK por si los ConsoleUtils los modifican
    */
    asm("STMFD SP!,{R0-R10,R12}");

    ConsoleUtilsPrintf("\r\n---------------------------------------");

    ConsoleUtilsPrintf("\r\nRegisters...");

    ConsoleUtilsPrintf("\r\n\tR0: 0x%x",r0_int);
    ConsoleUtilsPrintf("\r\n\tR1: 0x%x",r1_int);
    ConsoleUtilsPrintf("\r\n\tR2: 0x%x",r2_int);
    ConsoleUtilsPrintf("\r\n\tR3: 0x%x",r3_int);
    ConsoleUtilsPrintf("\r\n\tR4: 0x%x",r4_int);
    ConsoleUtilsPrintf("\r\n\tR5: 0x%x",r5_int);
    ConsoleUtilsPrintf("\r\n\tR6: 0x%x",r6_int);
    ConsoleUtilsPrintf("\r\n\tR7: 0x%x",r7_int);
    ConsoleUtilsPrintf("\r\n\tR8: 0x%x",r8_int);
    ConsoleUtilsPrintf("\r\n\tR9: 0x%x",r9_int);
    ConsoleUtilsPrintf("\r\n\tR10: 0x%x",r10_int);
    ConsoleUtilsPrintf("\r\n\tFP: 0x%x",r11_int);
    ConsoleUtilsPrintf("\r\n\tR12: 0x%x",r12_int);
    /*
    * Se le suma al stack pointer un offset de 0x48, que es la cantidad de bytes que se pushean
    * al stack al momento de llamar a esta función. Esto se hace para mostrar el valor que tenía el SP
    * justo antes de la función, que es donde importa
    */
    ConsoleUtilsPrintf("\r\n\tSP: 0x%x",r13_int+0x48);
    ConsoleUtilsPrintf("\r\n\tLR: 0x%x",r14_int);

    ConsoleUtilsPrintf("\r\n---------------------------------------");
    /*
    * Se recuperan los registros del STACK por si los ConsoleUtils los modificaron
    */
    asm("LDMFD SP!,{R0-R10,R12}");
}

/**
 * @brief Esta función muestra los último len elementos del stack. Con mucho cuidado, para mostrar solo
 * el stack que le interesa al usuario.
 * \param len: cantidad de elementos a mostrar del STACK
 */
__attribute__((section(".text_pub"))) void PrintStack(uint32_t len)
{
    int i = 0;
    uint32_t sp;

    /*
    * Se lee el stack pointer y se le suma un offset, para mostrar el stack que le interesa al usuario,
    * que es el que estaba justo antes de llamar a esta función. Al usuario no le interesa ver impreso en 
    * pantalla lo que pushea el gcc cuando se llama a esta función!!
    */
    asm("STR R13,%0" : "=m"(sp));

    /*
    * Se guardan los registros en el STACK por si los ConsoleUtils los modifican
    */
    asm("STMFD SP!,{R0-R10,R12}");

    // Acá se suma el offset!
    sp += 0x20;

    ConsoleUtilsPrintf("\r\n-------------------------------------------------------------------");
    ConsoleUtilsPrintf("\r\nCurrent stack pointer 0x%x. Showing last %d items...",sp,len);
    
    for(i = 0; i < 0+len*4; i += 4) ConsoleUtilsPrintf("\r\n\t(0x%x) -> 0x%x",sp+i,_READ_32(sp+i));

    ConsoleUtilsPrintf("\r\n-------------------------------------------------------------------");

    /*
    * Se recuperan los registros del STACK por si los ConsoleUtils los modificaron
    */
    asm("LDMFD SP!,{R0-R10,R12}");
}


__attribute__((section(".text_pub")))void PrintGPIORegisters(uint16_t gpio_port)
    {   
        uint32_t gpio_addr = 0;
        uint32_t GPIO_port_REVISION = 0;  
        uint32_t GPIO_port_SYSCONFIG = 0;      
        uint32_t GPIO_port_EOI = 0;            
        uint32_t GPIO_port_IRQSTATUS_RAW_0 = 0;
        uint32_t GPIO_port_IRQSTATUS_RAW_1 = 0;
        uint32_t GPIO_port_IRQSTATUS_0 = 0;    
        uint32_t GPIO_port_IRQSTATUS_1 = 0;    
        uint32_t GPIO_port_IRQSTATUS_SET_0 = 0;
        uint32_t GPIO_port_IRQSTATUS_SET_1 = 0;
        uint32_t GPIO_port_IRQSTATUS_CLR_0 = 0;
        uint32_t GPIO_port_IRQSTATUS_CLR_1 = 0;
        uint32_t GPIO_port_IRQWAKEN_0 = 0;     
        uint32_t GPIO_port_IRQWAKEN_1 = 0;     
        uint32_t GPIO_port_SYSSTATUS = 0;      
        uint32_t GPIO_port_CTRL = 0;           
        uint32_t GPIO_port_OE = 0;             
        uint32_t GPIO_port_DATAIN = 0;         
        uint32_t GPIO_port_DATAOUT = 0;        
        uint32_t GPIO_port_LEVELDETECT0 = 0;   
        uint32_t GPIO_port_LEVELDETECT1 = 0;   
        uint32_t GPIO_port_RISINGDETECT = 0;   
        uint32_t GPIO_port_FALLINGDETECT = 0;  
        uint32_t GPIO_port_DEBOUNCENABLE = 0;  
        uint32_t GPIO_port_DEBOUNCINGTIME = 0; 
        uint32_t GPIO_port_CLEARDATAOUT = 0;   
        uint32_t GPIO_port_SETDATAOUT = 0;   

        // Lectura de los registros - 26 Registros
        gpio_addr = GPIO_BASE_ARRAY[gpio_port];
        GPIO_port_REVISION        = _READ_32(gpio_addr + GPIO_REVISION       );
        GPIO_port_SYSCONFIG       = _READ_32(gpio_addr + GPIO_SYSCONFIG      );
        GPIO_port_EOI             = _READ_32(gpio_addr + GPIO_EOI            );
        GPIO_port_IRQSTATUS_RAW_0 = _READ_32(gpio_addr + GPIO_IRQSTATUS_RAW_0);
        GPIO_port_IRQSTATUS_RAW_1 = _READ_32(gpio_addr + GPIO_IRQSTATUS_RAW_1);
        GPIO_port_IRQSTATUS_0     = _READ_32(gpio_addr + GPIO_IRQSTATUS_0    );
        GPIO_port_IRQSTATUS_1     = _READ_32(gpio_addr + GPIO_IRQSTATUS_1    );
        GPIO_port_IRQSTATUS_SET_0 = _READ_32(gpio_addr + GPIO_IRQSTATUS_SET_0);
        GPIO_port_IRQSTATUS_SET_1 = _READ_32(gpio_addr + GPIO_IRQSTATUS_SET_1);
        GPIO_port_IRQSTATUS_CLR_0 = _READ_32(gpio_addr + GPIO_IRQSTATUS_CLR_0);
        GPIO_port_IRQSTATUS_CLR_1 = _READ_32(gpio_addr + GPIO_IRQSTATUS_CLR_1);
        GPIO_port_IRQWAKEN_0      = _READ_32(gpio_addr + GPIO_IRQWAKEN_0     );
        GPIO_port_IRQWAKEN_1      = _READ_32(gpio_addr + GPIO_IRQWAKEN_1     );
        GPIO_port_SYSSTATUS       = _READ_32(gpio_addr + GPIO_SYSSTATUS      );
        GPIO_port_CTRL            = _READ_32(gpio_addr + GPIO_CTRL           );
        GPIO_port_OE              = _READ_32(gpio_addr + GPIO_OE             );
        GPIO_port_DATAIN          = _READ_32(gpio_addr + GPIO_DATAIN         );
        GPIO_port_DATAOUT         = _READ_32(gpio_addr + GPIO_DATAOUT        );
        GPIO_port_LEVELDETECT0    = _READ_32(gpio_addr + GPIO_LEVELDETECT0   );
        GPIO_port_LEVELDETECT1    = _READ_32(gpio_addr + GPIO_LEVELDETECT1   );
        GPIO_port_RISINGDETECT    = _READ_32(gpio_addr + GPIO_RISINGDETECT   );
        GPIO_port_FALLINGDETECT   = _READ_32(gpio_addr + GPIO_FALLINGDETECT  );
        GPIO_port_DEBOUNCENABLE   = _READ_32(gpio_addr + GPIO_DEBOUNCENABLE  );
        GPIO_port_DEBOUNCINGTIME  = _READ_32(gpio_addr + GPIO_DEBOUNCINGTIME );
        GPIO_port_CLEARDATAOUT    = _READ_32(gpio_addr + GPIO_CLEARDATAOUT   );
        GPIO_port_SETDATAOUT      = _READ_32(gpio_addr + GPIO_SETDATAOUT     );
            
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |-----------------------------------------------|");
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |                  REGISTROS GPIO               |");
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |-----------------------------------------------|");
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |    REGISTROS           |  PUERTO GPIO: %d      |",gpio_port);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |------------------------|----------------------|");      
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_REVISION         |   0x%x\t\t         |",GPIO_port_REVISION);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_SYSCONFIG        |   0x%x\t\t         |",GPIO_port_SYSCONFIG      );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_EOI              |   0x%x\t\t         |",GPIO_port_EOI            );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_RAW_0  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_RAW_0);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_RAW_1  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_RAW_1);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_0      |   0x%x\t\t         |",GPIO_port_IRQSTATUS_0    );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_1      |   0x%x\t\t         |",GPIO_port_IRQSTATUS_1    );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_SET_0  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_SET_0);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_SET_1  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_SET_1);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_CLR_0  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_CLR_0);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQSTATUS_CLR_1  |   0x%x\t\t         |",GPIO_port_IRQSTATUS_CLR_1);
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQWAKEN_0       |   0x%x\t\t         |",GPIO_port_IRQWAKEN_0     );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_IRQWAKEN_1       |   0x%x\t\t         |",GPIO_port_IRQWAKEN_1     );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_SYSSTATUS        |   0x%x\t\t         |",GPIO_port_SYSSTATUS      );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_CTRL             |   0x%x\t\t         |",GPIO_port_CTRL           );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_OE               |   0x%x\t\t         |",GPIO_port_OE             );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_DATAIN           |   0x%x\t\t         |",GPIO_port_DATAIN         );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_DATAOUT          |   0x%x\t\t         |",GPIO_port_DATAOUT        );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_LEVELDETECT0     |   0x%x\t\t         |",GPIO_port_LEVELDETECT0   );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_LEVELDETECT1     |   0x%x\t\t         |",GPIO_port_LEVELDETECT1   );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_RISINGDETECT     |   0x%x\t\t         |",GPIO_port_RISINGDETECT   );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_FALLINGDETECT    |   0x%x\t\t         |",GPIO_port_FALLINGDETECT  );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_DEBOUNCENABLE    |   0x%x\t\t         |",GPIO_port_DEBOUNCENABLE  );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_DEBOUNCINGTIME   |   0x%x\t\t         |",GPIO_port_DEBOUNCINGTIME );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_CLEARDATAOUT     |   0x%x\t\t         |",GPIO_port_CLEARDATAOUT   );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |  GPIO_SETDATAOUT       |   0x%x\t\t         |",GPIO_port_SETDATAOUT     );
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ |-----------------------------------------------|");



    }

__attribute__((section(".text_pub")))void PrintGPIOPortRegister(uint16_t gpio_port, uint32_t gpio_reg)
    {
        uint32_t gpio_addr = 0;
        uint32_t gpio_val = 0;  
  
        // Lectura de los registros - 26 Registros
        gpio_addr = GPIO_BASE_ARRAY[gpio_port];
        gpio_val = _READ_32(gpio_addr + gpio_reg);
        
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ GPIO Port: %d (Addr.: 0x%x) | Reg.: 0x%x | Contenido: 0x%x",gpio_port,gpio_addr,gpio_reg,gpio_val);
    }

__attribute__((section(".text_pub"))) void PrintIRQRegisters(uint16_t irq_reg)
    {  
        uint32_t nvic_register = 0;
        uint32_t nvic_register_value = 0;


        nvic_register = NVIC + irq_reg;
        nvic_register_value = _READ_32(nvic_register);

        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ NVIC Controller | Reg.: 0x%x | Contenido: 0x%x",nvic_register,nvic_register_value);
 
    }

__attribute__((section(".text_pub"))) void PrintPC(void)
    {
    uint32_t r14_int;

    asm("STR R14,%0" : "=m"(r14_int));
    ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ PC : 0x%x",r14_int);
    }

__attribute__((section(".text_pub"))) void PrintCPSR(void)
    {   
        uint32_t reg_cpsr;
        reg_cpsr = _READ_CPSR_REGS();
        ConsoleUtilsPrintf("\r\n[TD3_uBoot]:~$ CPSR : 0x%x",reg_cpsr);
    }

__attribute__((section(".text_pub"))) void PrintMemoryRegion(uint32_t dir_base, uint32_t len)
{
    uint32_t i = 0;
    ConsoleUtilsPrintf("\r\nContenido de región de memoria:\n\r\tDirección base 0x%x\n\r\tCantidad de bytes %d",dir_base,len*4);
    for(i = 0; i < len*3 + 1; i+= 4)
    {
        ConsoleUtilsPrintf("\n\r\tDirección: 0x%x",dir_base+i);
        ConsoleUtilsPrintf(" | Contenido: 0x%x",_READ_32(dir_base+i));
    }
}