/* === Headers files inclusions ==================================================================================== */

#include "calculator.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para sumar dos operandos
 *
 * @param a Primer operando
 * @param b Segundo operando
 * @return Suma de a y b
 */
static int Add(int a, int b);

/**
 * @brief Función para restar dos operandos
 *
 * @param a Primer operando
 * @param b Segundo operando
 * @return Resta de a y b
 */
static int Subtract(int a, int b);

/**
 * @brief Función para multiplicar dos operandos
 *
 * @param a Primer operando
 * @param b Segundo operando
 * @return Producto de a y b
 */
static int Multiply(int a, int b);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int Add(int a, int b) {
    return a + b;
}

static int Subtract(int a, int b) {
    return a - b;
}

static int Multiply(int a, int b) {
    return a * b;
}

/* === Public function implementation ============================================================================== */

int main(void) {
    calculator_t calculator = CalculatorCreate();

    if (calculator == NULL) {
        printf("Error al crear la calculadora\r\n");
        return -1;
    }

    CalculatorAdd(calculator, '+', Add);
    CalculatorAdd(calculator, '-', Subtract);
    CalculatorAdd(calculator, '*', Multiply);

    printf("Resultado %i\r\n", CalculatorCalculate(calculator, "23+12"));
    printf("Resultado %i\r\n", CalculatorCalculate(calculator, "2*4"));

    return 0;
}

/* === End of documentation ======================================================================================== */
