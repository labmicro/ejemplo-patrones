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

/** @file rgb.h
 ** @brief Declaraciones públicas del led RGB
 **/

#ifndef RGB_H_
#define RGB_H_

/* === Headers files inclusions ==================================================================================== */

#include "pin.h"
#include <stdint.h>
#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para un color RGB */
typedef union color_s {
    uint32_t encoded;
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } channels;
} color_t;

/** Tipo de datos para el objeto led RGB */
typedef struct rgb_led_s * rgb_led_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un led RGB
 *
 * @param red Pin PWM del canal rojo
 * @param green Pin PWM del canal verde
 * @param blue Pin PWM del canal azul
 * @return Puntero al led RGB creado
 */
rgb_led_t rgbCreate(pin_pwm_t red, pin_pwm_t green, pin_pwm_t blue);

/**
 * @brief Función para establecer el color del led
 *
 * @param led Puntero al led RGB
 * @param color Color a establecer
 */
void rgbSetColor(rgb_led_t led, color_t color);

/**
 * @brief Función para obtener el color del led
 *
 * @param led Puntero al led RGB
 * @return Color actual
 */
color_t rgbGetColor(rgb_led_t led);

/**
 * @brief Función para establecer la intensidad del led
 *
 * @param led Puntero al led RGB
 * @param intensity Intensidad entre 0 y 100
 */
void rgbSetIntensity(rgb_led_t led, uint8_t intensity);

/**
 * @brief Función para obtener la intensidad del led
 *
 * @param led Puntero al led RGB
 * @return Intensidad actual
 */
uint8_t rgbGetIntensity(rgb_led_t led);

/**
 * @brief Función para encender el led
 *
 * @param led Puntero al led RGB
 */
void rgbTurnOn(rgb_led_t led);

/**
 * @brief Función para apagar el led
 *
 * @param led Puntero al led RGB
 */
void rgbTurnOff(rgb_led_t led);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* RGB_H_ */
