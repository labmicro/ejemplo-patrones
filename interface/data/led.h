#ifndef LED_H_
#define LED_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>
#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para leer el estado de una salida digital */
typedef bool (*digital_output_get_state_t)(void * data);

/** Tipo de datos para escribir el estado de una salida digital */
typedef void (*digital_output_set_state_t)(void * data, bool state);

/** Tipo de datos para la interfaz de salida digital */
typedef struct digital_output_interface_s {
    digital_output_get_state_t GetState;
    digital_output_set_state_t SetState;
} const * digital_output_interface_t;

/** Tipo de datos para el objeto led */
typedef struct led_s * led_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un led
 *
 * @param digital_output Interfaz de salida digital que usa el led
 * @param data Puntero a datos u objetos que se usarán en las funciones de la interfaz
 * @return Puntero al led creado
 */
led_t LedCreate(digital_output_interface_t digital_output, void * data);

/**
 * @brief Función para encender un led
 *
 * @param led Puntero al led
 */
void LedTurnOn(led_t led);

/**
 * @brief Función para apagar un led
 *
 * @param led Puntero al led
 */
void LedTurnOff(led_t led);

/**
 * @brief Función para conmutar el estado de un led
 *
 * @param led Puntero al led
 */
void LedToggle(led_t led);

/**
 * @brief Función para consultar si un led está encendido
 *
 * @param led Puntero al led
 * @return true si el led está encendido, false en caso contrario
 */
bool LedIsOn(led_t led);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LED_H_ */
