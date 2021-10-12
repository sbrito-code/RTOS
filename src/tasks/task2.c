#include "../../inc/utils/types.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/tasks/task2.h"

static uint32_t count = 1000;

 __attribute__((section(".text_pub"))) void task2(void *r0)
{
    count--;
    ConsoleUtilsPrintf("\n\rValor contador tarea 2: %d", count);
    asm("WFI");
}