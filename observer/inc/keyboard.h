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
 ** @brief Public declarations for the keyboard handling class
 **/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Data type for the keyboard object */
typedef struct keyboard_s * keyboard_t;

/** Data type for keyboard event notification */
typedef void(*key_event_t)(keyboard_t, char);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Crea un nuevo objeto teclado
 *
 * @return Puntero al teclado creado
 */
keyboard_t KeyboardCreate(void);

/**
 * @brief Suscribe un manejador de eventos para un rango de teclas
 *
 * @param self    Puntero al teclado
 * @param from    Tecla inicial del rango
 * @param to      Tecla final del rango
 * @param handler Función a ejecutar cuando se presiona una tecla en el rango
 * @return true si la suscripción fue exitosa, false en caso contrario
 */
bool KeyboardSubscribe(keyboard_t self, char from, char to, key_event_t handler);

/**
 * @brief Remueve un manejador de eventos del teclado
 *
 * @param self    Puntero al teclado
 * @param handler Manejador a remover
 * @return true si el manejador fue removido, false en caso contrario
 */
bool KeyboardRemove(keyboard_t self, key_event_t handler);

/**
 * @brief Procesa los eventos de teclado (debe llamarse periódicamente)
 *
 * @param self Puntero al teclado
 */
void KeyboardTick(keyboard_t self);

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_H_ */
