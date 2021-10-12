#include "../../inc/board/led.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/board/switch.h"
#include "../../inc/irq/nvic_handlers.h"
#include "../../inc/utils/console_utils.h"
#include "../../inc/board/gpio.h"
#include "../../inc/utils/debug_tools.h"

__attribute__((section(".kernel_handler"))) void GPIOINT2A_IRQHandler(void)
{
    uint32_t aux_reg = 0;
    ConsoleUtilsPrintf("\n\n\rInvirtiendo led...\n");
    LED_invert(LED2);
    aux_reg = _READ_32(GPIO_BASE_ARRAY[GPIO2] + GPIO_IRQSTATUS_0);
    aux_reg = aux_reg | (0b01 << 8);
    _WRITE_32((GPIO_BASE_ARRAY[GPIO2] + GPIO_IRQSTATUS_0), aux_reg);
    asm("DSB");
}