/* === Headers files inclusions ==================================================================================== */

#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

#ifndef MAX_GPIO_INSTANCES
#define MAX_GPIO_INSTANCES 10
#endif

/* === Private data type declarations ============================================================================== */

struct gpio_s {
    uint8_t port;
    uint8_t pin;
    bool output;
#ifdef USE_STATIC_MEM
    bool used;
#endif
};

/* === Private function declarations =============================================================================== */

#ifdef USE_STATIC_MEM
/**
 * @brief Función para asignar un objeto GPIO usando memoria estática
 *
 * @details Asigna un objeto GPIO en reemplazo de malloc cuando se utiliza memoria estática.
 *
 * @return Puntero al objeto GPIO asignado
 */
static gpio_t gpioAllocate(void);
#endif

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

#ifdef USE_STATIC_MEM
static gpio_t gpioAllocate(void) {
    gpio_t result = NULL;
    static struct gpio_s instances[MAX_GPIO_INSTANCES] = {0};
    for (int index = 0; index < MAX_GPIO_INSTANCES; index++) {
        if (!instances[index].used) {
            instances[index].used = true;
            result = &instances[index];
            break;
        }
    }
    return result;
}
#endif

/* === Public function implementation ============================================================================== */

gpio_t gpioCreate(uint8_t port, uint8_t pin, bool output) {
#ifdef USE_STATIC_MEM
    gpio_t self = gpioAllocate();
#else
    gpio_t self = malloc(sizeof(struct gpio_s));
#endif
    if (self) {
        self->port = port;
        self->pin = pin;
        self->output = output;
    }
    return self;
}

void gpioSetState(gpio_t self, bool state) {
    if (self->output) {
        printf("Estableciendo GPIO puerto %d, pin %d en %s\r\n", self->port, self->pin, state ? "ALTO" : "BAJO");
    } else {
        printf("No se puede establecer el estado del GPIO puerto %d, pin %d porque no está configurado como salida\r\n",
               self->port, self->pin);
    }
}

bool gpioGetState(gpio_t self) {
    bool value = true; // Valor simulado de la lectura
    printf("Obteniendo el valor del GPIO puerto %d, pin %d: %s\r\n", self->port, self->pin, value ? "ALTO" : "BAJO");
    return value;
}

/* === End of documentation ======================================================================================== */
