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

/** @file keyboard.h
 ** @brief Declaraciones públicas del teclado con observadores en lista
 **/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto teclado */
typedef struct keyboard_s * keyboard_t;

/** Tipo de datos para notificar eventos de teclado */
typedef void (*keyboard_event_t)(keyboard_t, char);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un teclado
 *
 * @return Puntero al teclado creado
 */
keyboard_t KeyboardCreate(void);

/**
 * @brief Función para suscribir un manejador de eventos a un rango de teclas
 *
 * @param self Puntero al teclado
 * @param from Tecla inicial del rango
 * @param to Tecla final del rango
 * @param handler Función a ejecutar cuando se pulsa una tecla en el rango
 * @return true si la suscripción fue exitosa, false en caso contrario
 */
bool KeyboardSubscribe(keyboard_t self, char from, char to, keyboard_event_t handler);

/**
 * @brief Función para quitar un manejador de eventos del teclado
 *
 * @param self Puntero al teclado
 * @param handler Manejador a quitar
 * @return true si el manejador fue quitado, false en caso contrario
 */
bool KeyboardRemove(keyboard_t self, keyboard_event_t handler);

/**
 * @brief Función periódica para procesar los eventos de teclado
 *
 * @param self Puntero al teclado
 */
void KeyboardTick(keyboard_t self);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_H_ */
