/**
 * Archivo: memcopy.h
 * Función: Función para copiar memoria
 * Autor: Brito Sergio Sebastian
 **/

#include "../utils/types.h"

/**
 * @fn void memcopy(uint32_t dir_in, uint32_t dir_out, uint32_t size)
 * @brief         Memcopy
 * @param[in] dir_in
 * @param[in] dir_out
 * @param[in] size
 * @return        void
 **/
void memcopy(uint32_t dir_in, uint32_t dir_out, uint32_t size);

/**
 * @fn comparememory(uint32_t dir_origin, uint32_t dir_compare, uint32_t size)
 * @brief         Memcopy
 * @param[in] dir_origin
 * @param[in] dir_compare
 * @param[in] size
 * @return        void
 **/
void comparememory(uint32_t dir_origin, uint32_t dir_compare, uint32_t size);
