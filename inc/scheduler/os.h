#include "../../inc/utils/types.h"
#include "../../inc/tasks/task0.h"
#include "../../inc/tasks/task1.h"
#include "../../inc/tasks/task2.h"
#include "../../inc/tasks/task3.h"

#define NUMBER_TASK 4 /*tasks number*/
#define OS_TASK_STACK_SIZE_WORDS 1024

typedef enum {
    TASK_STATE_READY,
    TASK_STATE_RUNNING,
    TASK_STATE_WAITING
} os_task_state_e;

typedef void (*os_task_t)(void);
void os_context_switch(void);

typedef struct {
    uint32_t * sp;
    os_task_t entry_point;
    void * argument;
    bool op_fpu;
    os_task_state_e state;
    uint32_t ticks;
    uint32_t stack_irq;
    uint32_t stack[OS_TASK_STACK_SIZE_WORDS];
}os_tcb_t;

void os_start(void);
void os_init_task_list(void);