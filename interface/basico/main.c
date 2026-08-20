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
 ** @brief Programa de ejemplo del patrón interfaz
 **/

/* === Headers files inclusions ==================================================================================== */

#include "led.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para leer un bit a través de un expansor I2C
 *
 * @return Estado simulado del bit I2C
 */
static bool I2cGetState(void);

/**
 * @brief Función para escribir un bit a través de un expansor I2C
 *
 * @param state Estado a establecer
 */
static void I2cSetState(bool state);

/**
 * @brief Función para leer el estado de un GPIO
 *
 * @return Estado simulado del GPIO
 */
static bool GpioGetState(void);

/**
 * @brief Función para escribir el estado de un GPIO
 *
 * @param state Estado a establecer
 */
static void GpioSetState(bool state);

/* === Private variable definitions ================================================================================ */

static bool i2c_bit = false;
static bool gpio_bit = false;

static const digital_output_interface_t I2C_EXPANDER = &(struct digital_output_interface_s){
    .GetState = I2cGetState,
    .SetState = I2cSetState,
};

static const digital_output_interface_t GPIO_BASE = &(struct digital_output_interface_s){
    .GetState = GpioGetState,
    .SetState = GpioSetState,
};

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static bool I2cGetState(void) {
    printf("Obteniendo bit I2C: %s\r\n", i2c_bit ? "ALTO" : "BAJO");
    return i2c_bit;
}

static void I2cSetState(bool state) {
    i2c_bit = state;
    printf("Estableciendo bit I2C en %s\r\n", state ? "ALTO" : "BAJO");
}

static bool GpioGetState(void) {
    printf("Obteniendo GPIO: %s\r\n", gpio_bit ? "ALTO" : "BAJO");
    return gpio_bit;
}

static void GpioSetState(bool state) {
    gpio_bit = state;
    printf("Estableciendo GPIO en %s\r\n", state ? "ALTO" : "BAJO");
}

/* === Public function implementation ============================================================================== */

int main(void) {
    led_t led = LedCreate(I2C_EXPANDER);
    led_t alert = LedCreate(GPIO_BASE);

    if ((led == NULL) || (alert == NULL)) {
        printf("Error al crear el led\r\n");
        return -1;
    }

    LedTurnOn(led);
    LedTurnOn(alert);
    
    LedToggle(led);

    return 0;
}

/* === End of documentation ======================================================================================== */
