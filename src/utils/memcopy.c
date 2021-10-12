#include "../../inc/utils/types.h"
#include "../../inc/utils/low_level_cpu_access.h"
#include "../../inc/utils/console_utils.h"

__attribute__((section(".text_pub"))) void memcopy(uint32_t dir_in, uint32_t dir_out, uint32_t size)
{
    for (uint8_t i = 0; i < size; i += 4)
    {
        _READ_32(dir_in + i);
        _WRITE_32((dir_out + i),_READ_32(dir_in + i));
    }
}

__attribute__((section(".text_pub"))) void comparememory(uint32_t dir_origin, uint32_t dir_compare, uint32_t size)
{
    bool exit = FALSE;
    uint32_t i = 0;

    while (exit != TRUE && i < size)
    {
        ((_READ_32(dir_origin + i)) == (_READ_32(dir_compare + i)))?(exit = TRUE):(exit = FALSE);
        i += 4;
    }

    (exit == FALSE)?(ConsoleUtilsPrintf("Datos idénticos")):(ConsoleUtilsPrintf("Datos distintos"));
}