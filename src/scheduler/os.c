#include "../../inc/utils/types.h"
#include "../../inc/irq/timertick.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/scheduler/os.h"
#include "../../inc/scheduler/os_timer_isr.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/utils/types.h"

#include "../../inc/tasks/task0.h"
#include "../../inc/tasks/task1.h"
#include "../../inc/tasks/task2.h"
#include "../../inc/tasks/task3.h"

/*==================[macros and definitions]=================================*/
/*
* Set system mode
* CPSR: bits[3:0]
* 00: USER  -   01: FIQ  -   02:IRQ  -   03:SUPERVISOR  -   06:MONITOR       
* 07: ABORT -   0A: HYP  -   0B:UNDEFINED               -   0F:SYSTEM       
*/
#define OS_INITIAL_SPSR	((uint32_t) 0x5F) /* System mode, ARM mode, IRQ enabled FIQ disabled. */

// Definitions in linker script
extern const void _STACK_IRQ_TASK0_RAM;
extern const void _STACK_IRQ_TASK1_RAM;
extern const void _STACK_IRQ_TASK2_RAM;
extern const void _STACK_IRQ_TASK3_RAM;

static uint32_t current_task = 0;

/*
** Function: task_list[]
** Description: Set context of tasks
    ** sp: value sp of task                                                     **
    ** entry_point: task                                                        **
    ** state: store the status of the task, can be                              **
    **  TASK_STATE_READY- TASK_STATE_WAITING - TASK_STATE_RUNNING               **
    ** ticks: time for task                                                     ** 
*/
os_tcb_t task_list[NUMBER_TASK+1] = {
    {.sp = 0 }, /* initial context, won't be used anymore */
    {.sp = 0, .entry_point = task0, .argument = (void *)0x00000000, .op_fpu = FALSE, .state = TASK_STATE_READY, .ticks = 40, .stack_irq = (uint32_t)&_STACK_IRQ_TASK0_RAM}, /* task 0 context */
    {.sp = 0, .entry_point = task1, .argument = (void *)0x11111111, .op_fpu = FALSE, .state = TASK_STATE_READY, .ticks = 20, .stack_irq = (uint32_t)&_STACK_IRQ_TASK1_RAM}, /* task 1 context */
    {.sp = 0, .entry_point = task2, .argument = (void *)0x22222222, .op_fpu = FALSE, .state = TASK_STATE_READY, .ticks = 20, .stack_irq = (uint32_t)&_STACK_IRQ_TASK2_RAM}, /* task 2 context */
    {.sp = 0, .entry_point = task3, .argument = (void *)0x33333333, .op_fpu = FALSE, .state = TASK_STATE_READY, .ticks = 20, .stack_irq = (uint32_t)&_STACK_IRQ_TASK3_RAM} /* task 3 context */
};

 __attribute__((section(".text_pub"))) void os_init_task_list(void)
{
    for (int i = 1; i <= NUMBER_TASK ; i++) {
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 1] = OS_INITIAL_SPSR;
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 2] = (uint32_t)task_list[i].entry_point; /* pc */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 3] = 0; /* r14 lr, return hook */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 4] = 0; /* r12 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 5] = 0; /* r11 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 6] = 0; /* r10 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 7] = 0; /* r9 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 8] = 0; /* r8 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 9] = 0; /* r7 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 10] = 0; /* r6 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 11] = 0; /* r5 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 12] = 0; /* r4 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 13] = 0; /* r3 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 14] = 0; /* r2 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 15] = 0; /* r1 */
        task_list[i].stack[OS_TASK_STACK_SIZE_WORDS - 16] = (uint32_t)(task_list[i].argument); /* r0, argument*/
        task_list[i].sp = task_list[i].stack_irq - 16; /* task stack pointer value */
    }
}

 __attribute__((section(".text_pub"))) void os_start(void)
{
    ConsoleUtilsPrintf("\n\rInstalando func a IRQ ...");
    NVIC_Install_IRQ_Handler(os_timer1_isr, TINT1_1MS_IRQn);
    ConsoleUtilsPrintf("OK");

    /* Initialize the TimerTick */
    ConsoleUtilsPrintf("\n\rIniciando Timer ...");
    TimerTick_Start();
    ConsoleUtilsPrintf("OK");

    os_context_switch();
}

 __attribute__((section(".text_pub"))) void os_context_switch(void)
{

}

uint32_t * os_get_next_context(uint32_t * current_sp)
{
    task_list[current_task].sp = current_sp;
    (current_task < NUMBER_TASK+1)?(current_task++):(current_task = 1);

    return task_list[current_task].sp;
}