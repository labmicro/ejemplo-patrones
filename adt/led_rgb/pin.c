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

/** @file pin.c
 ** @brief Implementación del pin con salida PWM
 **/

/* === Headers files inclusions ==================================================================================== */

#include "pin.h"
#include <stdio.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

#ifndef MAX_PIN_INSTANCES
#define MAX_PIN_INSTANCES 10
#endif

/* === Private data type declarations ============================================================================== */

struct pin_pwm_s {
    uint8_t port;
    uint8_t pin;
    uint8_t value;
#ifdef USE_STATIC_MEM
    bool used;
#endif
};

/* === Private function declarations =============================================================================== */

#ifdef USE_STATIC_MEM
/**
 * @brief Función para asignar un pin PWM usando memoria estática
 *
 * @return Puntero al pin asignado
 */
static pin_pwm_t pinAllocate(void);
#endif

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

#ifdef USE_STATIC_MEM
static pin_pwm_t pinAllocate(void) {
    pin_pwm_t result = NULL;
    static struct pin_pwm_s instances[MAX_PIN_INSTANCES] = {0};

    for (int index = 0; index < MAX_PIN_INSTANCES; index++) {
        if (!instances[index].used) {
            instances[index].used = true;
            result = &instances[index];
            break;
        }
    }
    return result;
}
#endif

/* === Public function implementation ============================================================================== */

pin_pwm_t pinCreatePwm(uint8_t port, uint8_t pin) {
#ifdef USE_STATIC_MEM
    pin_pwm_t self = pinAllocate();
#else
    pin_pwm_t self = malloc(sizeof(struct pin_pwm_s));
#endif
    if (self) {
        self->port = port;
        self->pin = pin;
        self->value = 0;
    }
    return self;
}

void pinSetPwm(pin_pwm_t self, uint8_t value) {
    if (self) {
        self->value = value;
        printf("Estableciendo PWM puerto %d, pin %d en %d\r\n", self->port, self->pin, value);
    }
}

uint8_t pinGetPwm(pin_pwm_t self) {
    uint8_t value = 0;

    if (self) {
        value = self->value;
    }
    return value;
}

/* === End of documentation ======================================================================================== */
