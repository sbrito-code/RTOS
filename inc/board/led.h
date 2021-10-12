/**
 * Archivo: led.h
 * Función: Uso de LEDs de la BeagleBone Black - Rev. C
 * Autor: Brito Sergio Sebastian
 **/

#include "../utils/types.h"
#include "../board/gpio.h"

typedef enum
{
    LED0 = PIN21,
    LED1 = PIN22,
    LED2 = PIN23,
    LED3 = PIN24
} LED_typedef;


/**
 * @fn void LED_init(void)
 * @brief         Initialize the Leds GPIOs
 * @return        void
 **/
extern void LED_init(void);

/**
 * @fn void LED_on(LED_typedef led)
 * @brief            Turn a led on.
 * @param[in] led    Led to turn on.
 * @return           void
 **/
extern void LED_on(LED_typedef);


/**
 * @fn void LED_off(LED_typedef led)
 * @brief            Turn a led off.
 * @param[in] led    Led to turn off.
 * @return           void
 **/
extern void LED_off(LED_typedef);

/**
 * @fn void LED_invert(LED_typedef led)
 * @brief            Invert a led on.
 * @param[in] led    Led to turn invert.
 * @return           void
 **/
extern void LED_invert(LED_typedef);