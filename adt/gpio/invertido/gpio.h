/*********************************************************************************************************************
Copyright 2016-2025, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/
Copyright 2016-2025, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file gpio.h
 ** @brief Declaraciones públicas del objeto GPIO con lógica invertible
 **/

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
 * @param output true para salida, false para entrada
 * @param inverted true si la lógica del pin está invertida
 * @return Puntero al objeto GPIO creado
 */
gpio_t gpioCreate(uint8_t port, uint8_t pin, bool output, bool inverted);

/**
 * @brief Función para establecer el estado del GPIO
 *
 * @param gpio Puntero al objeto GPIO
 * @param state Estado a establecer
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
