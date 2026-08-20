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

/** @file main.c
 ** @brief Programa de ejemplo del patrón evento con datos de usuario
 **/

/* === Headers files inclusions ==================================================================================== */

#include "padlock.h"
#include "gpio.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/**
 * @brief Estructura para el hardware del candado
 *
 * @param out_lock GPIO de salida para la cerradura
 * @param led_success GPIO de salida para el led de éxito
 * @param led_error GPIO de salida para el led de error
 */
typedef struct hardware_s {
    gpio_t out_lock;
    gpio_t led_success;
    gpio_t led_error;
} hardware_t;

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/**
 * @brief Función para gestionar las notificaciones de aperturas
 *
 * @param padlock Puntero al objeto candado que genera el evento
 * @param data Puntero a la estructura con el hardware
 */
static void onSuccess(padlock_t padlock, void * data);

/**
 * @brief Función para gestionar las notificaciones de error
 *
 * @param padlock Puntero al objeto candado que genera el evento
 * @param data Puntero a la estructura con el hardware
 */
static void onError(padlock_t padlock, void * data);

/* === Private function definitions ================================================================================ */

static void onSuccess(padlock_t padlock, void * data) {
    hardware_t * outs = (hardware_t *) data;
    printf("Clave correcta\r\n");
    gpioSetState(outs->out_lock, true);
    gpioSetState(outs->led_success, true);
}

static void onError(padlock_t padlock, void * data) {
    hardware_t * outs = (hardware_t *) data;
    printf("Clave incorrecta\r\n");
    PadlockSetPenalty(padlock, 50);
    gpioSetState(outs->led_error, true);
}

/* === Public function implementation ============================================================================== */

int main(void) {
    static hardware_t outs;

    outs.out_lock = gpioCreate(1, 1, true);
    outs.led_success = gpioCreate(1, 2, true);
    outs.led_error = gpioCreate(1, 3, true);

    padlock_t padlock = PadlockCreate(123456, onSuccess, onError, &outs);

    if (padlock == NULL) {
        printf("Error al crear el candado\r\n");
        return -1;
    } else {
        printf("Candado creado\r\n");
    }

    while (true) {
        PadlockTick(padlock);
    }
}

/* === End of documentation ======================================================================================== */
