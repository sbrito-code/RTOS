#include "../../inc/utils/types.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/board/led.h"
#include "../../inc/tasks/task3.h"

__attribute__((section(".text_pub"))) void task3(void *r0)
{   
    ConsoleUtilsPrintf("\n\rTarea 3");
    LED_invert(LED2);
}