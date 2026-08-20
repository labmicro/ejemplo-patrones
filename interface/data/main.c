/* === Headers files inclusions ==================================================================================== */

#include "led.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>

/* === Macros definitions ========================================================================================== */

#define LED_PORT   1
#define LED_PIN    1

#define ALERT_PORT 1
#define ALERT_PIN  2

#define I2C_ADDRESS  0x20
#define I2C_REGISTER 0x01
#define I2C_BIT      3

/* === Private data type declarations ============================================================================== */

/** Datos de un bit en un expansor I2C */
typedef struct i2c_s {
    uint8_t address;
    uint8_t reg;
    uint8_t bit;
} i2c_t;

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para leer un bit a través de un expansor I2C
 *
 * @param data Puntero a la estructura con dirección, registro y bit
 * @return Estado simulado del bit
 */
static bool I2cGetState(void * data);

/**
 * @brief Función para escribir un bit a través de un expansor I2C
 *
 * @param data Puntero a la estructura con dirección, registro y bit
 * @param state Estado a establecer
 */
static void I2cSetState(void * data, bool state);

/**
 * @brief Función para leer el estado de un GPIO
 *
 * @param data Puntero al objeto GPIO
 * @return Estado del GPIO
 */
static bool GpioGetState(void * data);

/**
 * @brief Función para escribir el estado de un GPIO
 *
 * @param data Puntero al objeto GPIO
 * @param state Estado a establecer
 */
static void GpioSetState(void * data, bool state);

/* === Private variable definitions ================================================================================ */

static i2c_t i2c_led = {I2C_ADDRESS, I2C_REGISTER, I2C_BIT};

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

static bool I2cGetState(void * data) {
    i2c_t * i2c = data;
    bool value = true;

    printf("Obteniendo bit I2C dirección 0x%02X, registro 0x%02X, bit %d: %s\r\n", i2c->address, i2c->reg, i2c->bit,
           value ? "ALTO" : "BAJO");
    return value;
}

static void I2cSetState(void * data, bool state) {
    i2c_t * i2c = data;

    printf("Estableciendo bit I2C dirección 0x%02X, registro 0x%02X, bit %d en %s\r\n", i2c->address, i2c->reg, i2c->bit,
           state ? "ALTO" : "BAJO");
}

static bool GpioGetState(void * data) {
    return gpioGetState((gpio_t) data);
}

static void GpioSetState(void * data, bool state) {
    gpioSetState((gpio_t) data, state);
}

/* === Public function implementation ============================================================================== */

int main(void) {
    gpio_t gpio_led = gpioCreate(LED_PORT, LED_PIN, true);
    gpio_t gpio_alert = gpioCreate(ALERT_PORT, ALERT_PIN, true);

    led_t led = LedCreate(GPIO_BASE, gpio_led);
    led_t alert = LedCreate(GPIO_BASE, gpio_alert);
    led_t expander = LedCreate(I2C_EXPANDER, &i2c_led);

    if ((gpio_led == NULL) || (gpio_alert == NULL) || (led == NULL) || (alert == NULL) || (expander == NULL)) {
        printf("Error al crear el led\r\n");
        return -1;
    }

    LedTurnOn(led);
    LedTurnOn(alert);
    LedTurnOn(expander);

    return 0;
}

/* === End of documentation ======================================================================================== */
