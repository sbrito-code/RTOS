/**
 * Archivo: types.h
 * Función: definición de tipos de datos
 * Autor: Brito Sergio Sebastian
 *          ARM dispone 4 tipos de datos posibles:
 *          1) Byte - 8 bits (1 Byte)
 *          2) Halfword - 16 bits (2 Bytes)
 *          3) Word - 32 bits (4 Bytes)
 *          4) Doubleword - 64 bits (8 Bytes) - No disponible en todas las arquitecturas
 **/

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned short bool;

#define TRUE    ((bool) 1)
#define FALSE   ((bool) 0)

#define HIGH    ((bool) 1)
#define LOW   ((bool) 0)