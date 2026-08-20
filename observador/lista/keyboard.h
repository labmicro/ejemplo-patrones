#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto teclado */
typedef struct keyboard_s * keyboard_t;

/** Tipo de datos para notificar eventos de teclado */
typedef void (*keyboard_event_t)(keyboard_t, char);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un teclado
 *
 * @return Puntero al teclado creado
 */
keyboard_t KeyboardCreate(void);

/**
 * @brief Función para suscribir un manejador de eventos a un rango de teclas
 *
 * @param self Puntero al teclado
 * @param from Tecla inicial del rango
 * @param to Tecla final del rango
 * @param handler Función a ejecutar cuando se pulsa una tecla en el rango
 * @return true si la suscripción fue exitosa, false en caso contrario
 */
bool KeyboardSubscribe(keyboard_t self, char from, char to, keyboard_event_t handler);

/**
 * @brief Función para quitar un manejador de eventos del teclado
 *
 * @param self Puntero al teclado
 * @param handler Manejador a quitar
 * @return true si el manejador fue quitado, false en caso contrario
 */
bool KeyboardRemove(keyboard_t self, keyboard_event_t handler);

/**
 * @brief Función periódica para procesar los eventos de teclado
 *
 * @param self Puntero al teclado
 */
void KeyboardTick(keyboard_t self);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_H_ */
