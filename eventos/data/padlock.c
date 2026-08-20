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

/** @file padlock.c
 ** @brief Implementación del candado con datos en los eventos
 **/

/* === Headers files inclusions ==================================================================================== */

#include "padlock.h"
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions ========================================================================================== */

#define MAX_LENGTH 9

/* === Private data type declarations ============================================================================== */

struct padlock_s {
    uint32_t key;
    uint32_t penalty;
    padlock_event_t OnSuccess;
    padlock_event_t OnError;
    char entry[MAX_LENGTH];
    void * data;
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para limpiar la entrada de un candado
 *
 * @param self Puntero al objeto candado
 */
static void ClearEntry(padlock_t self);

/**
 * @brief Función para agregar un nuevo caracter a la entrada
 *
 * @param self Puntero al objeto candado
 * @param key Caracter a agregar
 */
static void NewEntry(padlock_t self, char key);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static void ClearEntry(padlock_t self) {
    memset(self->entry, 0, sizeof(self->entry));
}

static void NewEntry(padlock_t self, char key) {
    self->entry[strlen(self->entry)] = key;
}

/* === Public function implementation ============================================================================== */

padlock_t PadlockCreate(uint32_t key, padlock_event_t on_success, padlock_event_t on_error, void * data) {
    padlock_t self = malloc(sizeof(struct padlock_s));

    if (self) {
        self->key = key;
        self->penalty = 0;
        self->OnSuccess = on_success;
        self->OnError = on_error;
        self->data = data;

        KeyboardInit();
        ClearEntry(self);
    }
    return self;
}

void PadlockSetPenalty(padlock_t self, uint32_t penalty) {
    if (self) {
        self->penalty = penalty;
    }
}

void PadlockTick(padlock_t self) {
    if (!self) {
        return;
    }

    if (self->penalty) {
        self->penalty--;
    } else {
        int key = getchar();
        if ((key >= '0') && (key <= '9')) {
            if (strlen(self->entry) < sizeof(self->entry) - 1) {
                NewEntry(self, key);
                if (self->key == atoi(self->entry)) {
                    if (self->OnSuccess) {
                        self->OnSuccess(self, self->data);
                    }
                    ClearEntry(self);
                }
            } else {
                if (self->OnError) {
                    self->OnError(self, self->data);
                }
                ClearEntry(self);
            }
        } else if (key == ' ') {
            ClearEntry(self);
        }
    }
}

/* === End of documentation ======================================================================================== */
