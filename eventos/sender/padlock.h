#ifndef PADLOCK_H_
#define PADLOCK_H_

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>
#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para el objeto candado */
typedef struct padlock_s * padlock_t;

/** Tipo de datos para notificar eventos del candado */
typedef void (*padlock_event_t)(padlock_t);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear un candado
 *
 * @param key Clave del candado
 * @param on_success Función a ejecutar si la clave es correcta
 * @param on_error Función a ejecutar si la clave es incorrecta
 *
 * @return Puntero al candado creado
 */
padlock_t PadlockCreate(uint32_t key, padlock_event_t on_success, padlock_event_t on_error);

/**
 * @brief Función para fijar un tiempo de espera entre intentos
 *
 * @param padlock Puntero al candado
 * @param penalty Tiempo de espera antes de permitir un nuevo intento
 */
void PadlockSetPenalty(padlock_t padlock, uint32_t penalty);

/**
 * @brief Función periódica para procesar los eventos de teclado
 *
 * @param padlock Puntero al candado
 */
void PadlockTick(padlock_t padlock);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* PADLOCK_H_ */
