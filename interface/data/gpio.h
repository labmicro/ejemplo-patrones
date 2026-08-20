#ifndef GPIO_H_
#define GPIO_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdint.h>
#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto GPIO */
typedef struct gpio_s * gpio_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un objeto GPIO
 *
 * @param port Puerto del GPIO
 * @param pin Pin del GPIO
 * @param output Modo de salida
 * @return Puntero al objeto GPIO creado
 */
gpio_t gpioCreate(uint8_t port, uint8_t pin, bool output);

/**
 * @brief Función para establecer el estado del GPIO
 *
 * @param gpio Puntero al objeto GPIO
 * @param state Estado del GPIO
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Función para obtener el estado del GPIO
 *
 * @param gpio Puntero al objeto GPIO
 * @return Estado del GPIO
 */
bool gpioGetState(gpio_t gpio);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H_ */
