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

/** @file calculator.h
 ** @brief Declaraciones públicas de la calculadora con operaciones intercambiables
 **/

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto calculadora */
typedef struct calculator_s * calculator_t;

/** Tipo de datos para una operación de la calculadora */
typedef int (*calculator_operation_t)(int, int);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear una calculadora
 *
 * @return Puntero a la calculadora creada
 */
calculator_t CalculatorCreate(void);

/**
 * @brief Función para agregar una operación a la calculadora
 *
 * @param calculator Puntero a la calculadora
 * @param symbol Símbolo de la operación
 * @param function Función que implementa la operación
 * @return true si la operación fue agregada, false en caso contrario
 */
bool CalculatorAdd(calculator_t calculator, char symbol, calculator_operation_t function);

/**
 * @brief Función para evaluar una expresión con las operaciones registradas
 *
 * @param calculator Puntero a la calculadora
 * @param expression Cadena con la expresión a calcular
 * @return Resultado de la operación, o 0 si no se pudo calcular
 */
int CalculatorCalculate(calculator_t calculator, char * expression);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* CALCULATOR_H_ */
