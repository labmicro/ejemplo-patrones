#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/* === Headers files inclusions ==================================================================================== */

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para inicializar el teclado
 *
 * @details Configura la entrada estándar en modo no canónico y sin eco,
 *          para que cada tecla se reciba de inmediato.
 */
void KeyboardInit(void);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* KEYBOARD_H_ */
