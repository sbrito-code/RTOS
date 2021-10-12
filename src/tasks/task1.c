#include "../../inc/utils/types.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/tasks/task1.h"

static uint32_t count = 0;

 __attribute__((section(".text_pub"))) void task1(void * r0)
{   
    count++;
    ConsoleUtilsPrintf("\n\rValor contador tarea 1: %d", count);
    asm("WFI");
}