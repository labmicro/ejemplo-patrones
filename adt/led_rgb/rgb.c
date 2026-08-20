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

/** @file rgb.c
 ** @brief Implementación del led RGB
 **/

/* === Headers files inclusions ==================================================================================== */

#include "rgb.h"
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

#ifndef MAX_RGB_INSTANCES
#define MAX_RGB_INSTANCES 10
#endif

/* === Private data type declarations ============================================================================== */

struct rgb_led_s {
    pin_pwm_t red;
    pin_pwm_t green;
    pin_pwm_t blue;
    color_t color;
    uint8_t intensity;
    bool turned_on;
#ifdef USE_STATIC_MEM
    bool used;
#endif
};

/* === Private function declarations =============================================================================== */

#ifdef USE_STATIC_MEM
/**
 * @brief Función para asignar un led RGB usando memoria estática
 *
 * @return Puntero al led RGB asignado
 */
static rgb_led_t rgbAllocate(void);
#endif

/**
 * @brief Función para actualizar los pines PWM según color e intensidad
 *
 * @param self Puntero al led RGB
 */
static void rgbUpdatePwm(rgb_led_t self);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

#ifdef USE_STATIC_MEM
static rgb_led_t rgbAllocate(void) {
    rgb_led_t result = NULL;
    static struct rgb_led_s instances[MAX_RGB_INSTANCES] = {0};

    for (int index = 0; index < MAX_RGB_INSTANCES; index++) {
        if (!instances[index].used) {
            instances[index].used = true;
            result = &instances[index];
            break;
        }
    }
    return result;
}
#endif

static void rgbUpdatePwm(rgb_led_t self) {
    if (!self) {
        return;
    }

    if (!self->turned_on) {
        pinSetPwm(self->red, 0);
        pinSetPwm(self->green, 0);
        pinSetPwm(self->blue, 0);
    } else {
        pinSetPwm(self->red, (self->color.channels.red * self->intensity) / 100);
        pinSetPwm(self->green, (self->color.channels.green * self->intensity) / 100);
        pinSetPwm(self->blue, (self->color.channels.blue * self->intensity) / 100);
    }
}

/* === Public function implementation ============================================================================== */

rgb_led_t rgbCreate(pin_pwm_t red, pin_pwm_t green, pin_pwm_t blue) {
#ifdef USE_STATIC_MEM
    rgb_led_t self = rgbAllocate();
#else
    rgb_led_t self = malloc(sizeof(struct rgb_led_s));
#endif
    if (self) {
        self->red = red;
        self->green = green;
        self->blue = blue;
        self->intensity = 0;
        self->color.encoded = 0;
        self->turned_on = false;
    }
    return self;
}

void rgbSetColor(rgb_led_t self, color_t color) {
    if (self) {
        self->color = color;
        if (self->turned_on) {
            rgbUpdatePwm(self);
        }
    }
}

color_t rgbGetColor(rgb_led_t self) {
    color_t color = {0};

    if (self) {
        color = self->color;
    }
    return color;
}

void rgbSetIntensity(rgb_led_t self, uint8_t intensity) {
    if ((self) && (intensity <= 100)) {
        self->intensity = intensity;
        if (self->turned_on) {
            rgbUpdatePwm(self);
        }
    }
}

uint8_t rgbGetIntensity(rgb_led_t self) {
    uint8_t intensity = 0;

    if (self) {
        intensity = self->intensity;
    }
    return intensity;
}

void rgbTurnOn(rgb_led_t self) {
    if (self) {
        self->turned_on = true;
        rgbUpdatePwm(self);
    }
}

void rgbTurnOff(rgb_led_t self) {
    if (self) {
        self->turned_on = false;
        rgbUpdatePwm(self);
    }
}

/* === End of documentation ======================================================================================== */
