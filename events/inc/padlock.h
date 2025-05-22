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

#ifndef PADLOCK_H_
#define PADLOCK_H_

/** @file padlock.h
 ** @brief Declaraciónes publicas de la clase para el manejo de candados
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>
#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto candado */
typedef struct padlock_s * padlock_t;

/** Tipo de datos para notificar eventos del candado */
typedef void (*padlock_event_t)(padlock_t);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un candado
 *
 * @param clave Clave del candado
 * @param on_sucess función a ejecutar si la clave es correcta
 * @param on_error función a ejecutar si la clave es incorrecta

 * @return puntero al candado creado
 */
padlock_t PadlockCreate(uint32_t clave, padlock_event_t on_sucess, padlock_event_t on_error);

/**
 * @brief Función para fijar un tiempo de espera entre intentos
 *
 * @param padlock  puntero al candado
 * @param penalty tiempo de espera antes de permitir un nuevo intento
 */
void PadlockSetPenalty(padlock_t padlock, uint32_t penalty);

/**
 * @brief Función periódica para procesar los eventos de teclado
 *
 * @param padlock puntero al candado
 */
void PadlockTick(padlock_t padlock);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* PADLOCK_H_ */
