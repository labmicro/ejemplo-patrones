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
 ** @brief Programa de ejemplo del patrón evento básico
 **/

/* === Headers files inclusions ==================================================================================== */

#include "padlock.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/**
 * @brief Función para gestionar las notificaciones de aperturas
 */
static void onSuccess(void);

/**
 * @brief Función para gestionar las notificaciones de error
 */
static void onError(void);

/* === Private function definitions ================================================================================ */

static void onSuccess(void) {
    printf("Clave correcta\r\n");
}

static void onError(void) {
    printf("Clave incorrecta\r\n");
}

/* === Public function implementation ============================================================================== */

int main(void) {
    padlock_t padlock = PadlockCreate(123456, onSuccess, onError);

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
