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
