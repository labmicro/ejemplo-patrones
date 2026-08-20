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

/** @file keyboard.c
 ** @brief Implementación del teclado con arreglo de observadores
 **/

/* === Headers files inclusions ==================================================================================== */

#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* === Macros definitions ========================================================================================== */

#define MAX_CLIENTS 10

/* === Private data type declarations ============================================================================== */

struct keyboard_s {
    struct {
        char from_char;
        char to_char;
        keyboard_event_t EventHandler;
    } clients[MAX_CLIENTS];
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para configurar el terminal para la lectura de teclas
 *
 * @details Configura la entrada estándar en modo no canónico y sin eco,
 *          para que cada tecla se reciba de inmediato.
 */
static void KeyboardConfigure(void);

/**
 * @brief Función para buscar un cliente por su manejador de eventos
 *
 * @param self Puntero al teclado
 * @param handler Manejador de eventos a buscar, o NULL para un hueco libre
 * @return Índice del cliente encontrado, o -1 si no existe
 */
static int KeyboardFind(keyboard_t self, keyboard_event_t handler);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static void KeyboardConfigure(void) {
    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= (~ICANON & ~ECHO);
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

static int KeyboardFind(keyboard_t self, keyboard_event_t handler) {
    for (int index = 0; index < MAX_CLIENTS; index++) {
        if (self->clients[index].EventHandler == handler) {
            return index;
        }
    }
    return -1;
}

/* === Public function implementation ============================================================================== */

keyboard_t KeyboardCreate(void) {
    keyboard_t self = malloc(sizeof(struct keyboard_s));

    if (self) {
        KeyboardConfigure();
        memset(self, 0, sizeof(struct keyboard_s));
    }
    return self;
}

bool KeyboardSubscribe(keyboard_t self, char from, char to, keyboard_event_t handler) {
    int index;

    if ((!self) || (!handler) || (from > to)) {
        return false;
    }

    index = KeyboardFind(self, handler);
    if (index < 0) {
        index = KeyboardFind(self, NULL);
    }
    if (index >= 0) {
        self->clients[index].from_char = from;
        self->clients[index].to_char = to;
        self->clients[index].EventHandler = handler;
    }
    return (index >= 0);
}

bool KeyboardRemove(keyboard_t self, keyboard_event_t handler) {
    int index;

    if (!self) {
        return false;
    }

    index = KeyboardFind(self, handler);
    if (index >= 0) {
        self->clients[index].EventHandler = NULL;
    }
    return (index >= 0);
}

void KeyboardTick(keyboard_t self) {
    if (!self) {
        return;
    }

    int key = getchar();
    if (key != EOF) {
        for (int index = 0; index < MAX_CLIENTS; index++) {
            if ((self->clients[index].EventHandler) && (self->clients[index].from_char <= key) &&
                (key <= self->clients[index].to_char)) {
                self->clients[index].EventHandler(self, (char)key);
            }
        }
    }
}

/* === End of documentation ======================================================================================== */
