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
