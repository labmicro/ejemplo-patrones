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

/** @file calculator.c
 ** @brief Implementación de la calculadora con operaciones por estrategia
 **/

/* === Headers files inclusions ==================================================================================== */

#include "calculator.h"
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/** Tipo de datos para una operación registrada */
typedef struct operation_s * operation_t;

/** Estructura para una operación de la calculadora */
struct operation_s {
    char symbol;
    calculator_operation_t Function;
    operation_t next;
};

/** Estructura del objeto calculadora */
struct calculator_s {
    operation_t operations;
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para buscar una operación por su símbolo
 *
 * @param self Puntero a la calculadora
 * @param symbol Símbolo de la operación a buscar
 * @return Puntero a la operación encontrada o NULL si no existe
 */
static operation_t FindOperation(calculator_t self, char symbol);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static operation_t FindOperation(calculator_t self, char symbol) {
    operation_t operation = NULL;

    if (self) {
        operation = self->operations;
        while (operation != NULL) {
            if (operation->symbol == symbol) {
                return operation;
            }
            operation = operation->next;
        }
    }
    return NULL;
}

/* === Public function implementation ============================================================================== */

calculator_t CalculatorCreate(void) {
    calculator_t self = malloc(sizeof(struct calculator_s));

    if (self) {
        self->operations = NULL;
    }
    return self;
}

bool CalculatorAdd(calculator_t self, char symbol, calculator_operation_t function) {
    operation_t operation = NULL;

    if ((!self) || (!function)) {
        return false;
    }

    if (FindOperation(self, symbol) == NULL) {
        operation = malloc(sizeof(struct operation_s));
        if (operation) {
            operation->symbol = symbol;
            operation->Function = function;
            operation->next = self->operations;
            self->operations = operation;
        }
    }
    return (operation != NULL);
}

int CalculatorCalculate(calculator_t self, char * expression) {
    int result = 0;
    char symbol = '\0';
    int left = 0;
    int right = 0;

    if ((!self) || (!expression)) {
        return 0;
    }

    for (int index = 0; expression[index] != '\0'; index++) {
        if ((expression[index] < '0') || (expression[index] > '9')) {
            symbol = expression[index];
            left = atoi(expression);
            right = atoi(expression + index + 1);
            break;
        }
    }

    operation_t operation = FindOperation(self, symbol);
    if (operation) {
        result = operation->Function(left, right);
    }
    return result;
}

/* === End of documentation ======================================================================================== */
