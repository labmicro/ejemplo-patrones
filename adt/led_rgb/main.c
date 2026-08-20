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
 ** @brief Programa de ejemplo del led RGB
 **/

/* === Headers files inclusions ==================================================================================== */

#include "rgb.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

#define RED_PORT   1
#define RED_PIN    1
#define GREEN_PORT 1
#define GREEN_PIN  2
#define BLUE_PORT  1
#define BLUE_PIN   3

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

int main(void) {
    pin_pwm_t red = pinCreatePwm(RED_PORT, RED_PIN);
    pin_pwm_t green = pinCreatePwm(GREEN_PORT, GREEN_PIN);
    pin_pwm_t blue = pinCreatePwm(BLUE_PORT, BLUE_PIN);
    rgb_led_t led = rgbCreate(red, green, blue);

    if ((red == NULL) || (green == NULL) || (blue == NULL) || (led == NULL)) {
        printf("Error al crear el led RGB\r\n");
        return -1;
    }

    rgbSetColor(led, (color_t){.channels = {.red = 255, .green = 127, .blue = 63}});
    rgbSetIntensity(led, 100);
    rgbTurnOn(led);

    return 0;
}

/* === End of documentation ======================================================================================== */
