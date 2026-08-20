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
 ** @brief Programa de ejemplo del patrón observador con arreglo fijo
 **/

/* === Headers files inclusions ==================================================================================== */

#include "keyboard.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para gestionar las notificaciones de cualquier tecla
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void AllKeys(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de letras minúsculas
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void LowerCase(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de dígitos
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void Digits(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de letras mayúsculas
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void UpperCase(keyboard_t sender, char key);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static void AllKeys(keyboard_t sender, char key) {
    printf("Se ha pulsado una tecla\r\n");

    if (key == 'X') {
        KeyboardRemove(sender, AllKeys);
    }
}

static void LowerCase(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a una letra minuscula\r\n");
}

static void Digits(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a un digito\r\n");
}

static void UpperCase(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a una letra mayuscula\r\n");
}

/* === Public function implementation ============================================================================== */

int main(void) {
    keyboard_t keyboard = KeyboardCreate();

    if (keyboard == NULL) {
        printf("Error al crear el teclado\r\n");
        return -1;
    }

    KeyboardSubscribe(keyboard, '!', '}', AllKeys);
    KeyboardSubscribe(keyboard, 'A', 'Z', UpperCase);
    KeyboardSubscribe(keyboard, 'a', 'z', LowerCase);
    KeyboardSubscribe(keyboard, '0', '9', Digits);

    while (true) {
        KeyboardTick(keyboard);
    }
}

/* === End of documentation ======================================================================================== */
