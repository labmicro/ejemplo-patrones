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

/** @file led.h
 ** @brief Declaraciones públicas del led con salida digital intercambiable
 **/

#ifndef LED_H_
#define LED_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para leer el estado de una salida digital */
typedef bool (*digital_output_get_state_t)(void);

/** Tipo de datos para escribir el estado de una salida digital */
typedef void (*digital_output_set_state_t)(bool state);

/** Tipo de datos para la interfaz de salida digital */
typedef struct digital_output_interface_s {
    digital_output_get_state_t GetState;
    digital_output_set_state_t SetState;
} const * digital_output_interface_t;

/** Tipo de datos para el objeto led */
typedef struct led_s * led_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un led
 *
 * @param digital_output Interfaz de salida digital que usa el led
 * @return Puntero al led creado
 */
led_t LedCreate(digital_output_interface_t digital_output);

/**
 * @brief Función para encender un led
 *
 * @param led Puntero al led
 */
void LedTurnOn(led_t led);

/**
 * @brief Función para apagar un led
 *
 * @param led Puntero al led
 */
void LedTurnOff(led_t led);

/**
 * @brief Función para conmutar el estado de un led
 *
 * @param led Puntero al led
 */
void LedToggle(led_t led);

/**
 * @brief Función para consultar si un led está encendido
 *
 * @param led Puntero al led
 * @return true si el led está encendido, false en caso contrario
 */
bool LedIsOn(led_t led);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LED_H_ */
