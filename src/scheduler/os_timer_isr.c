#include "../../inc/utils/types.h"
#include "../../inc/scheduler/os_timer_isr.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/irq/timertick.h"
#include "../../inc/board/led.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/scheduler/os.h"

uint32_t context_switch_required;
static uint32_t ms_counter = 0;

/*
** Function: os_timer1_isr()
** Description: This function is loaded from IRQ_HANDLER every 1ms
*/
 __attribute__((section(".text_pub"))) void os_timer1_isr(void)
{
    //Esto invierte en LED
     _WRITE_32(TIMER_1MS_BASE + TIMER_1MS_TISR,0x2);
     asm("DSB");
     ms_counter++;

    if (ms_counter == 1000)
    {
        ms_counter = 0;
        ConsoleUtilsPrintf("\n\rDentro del ISR:Invierto led");
        LED_invert(LED2);
    }
}