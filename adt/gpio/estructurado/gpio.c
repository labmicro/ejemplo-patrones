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

/** @file gpio.c
 ** @brief Implementación del GPIO con diseño estructurado
 **/

/* === Headers files inclusions ==================================================================================== */

#include "gpio.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

void gpioSetDirection(uint8_t port, uint8_t pin, bool output) {
    printf("Configurando GPIO puerto %d, pin %d como %s\r\n", port, pin, output ? "salida" : "entrada");
}

void gpioSetState(uint8_t port, uint8_t pin, bool state) {
    printf("Estableciendo GPIO puerto %d, pin %d en %s\r\n", port, pin, state ? "ALTO" : "BAJO");
}

bool gpioGetState(uint8_t port, uint8_t pin) {
    bool value = true; // Valor simulado de la lectura

    printf("Obteniendo el valor del GPIO puerto %d, pin %d: %s\r\n", port, pin, value ? "ALTO" : "BAJO");
    return value;
}

/* === End of documentation ======================================================================================== */
