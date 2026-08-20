/* === Headers files inclusions ==================================================================================== */

#include "padlock.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/**
 * @brief Función para gestionar las notificaciones de aperturas
 *
 * @param padlock Puntero al objeto candado que genera el evento
 */
static void onSuccess(padlock_t padlock);

/**
 * @brief Función para gestionar las notificaciones de error
 *
 * @param padlock Puntero al objeto candado que genera el evento
 */
static void onError(padlock_t padlock);

/* === Private function definitions ================================================================================ */

static void onSuccess(padlock_t padlock) {
    printf("Clave correcta\r\n");
}

static void onError(padlock_t padlock) {
    printf("Clave incorrecta\r\n");
    PadlockSetPenalty(padlock, 50);
}

/* === Public function implementation ============================================================================== */

int main(void) {
    padlock_t padlock = PadlockCreate(123456, onSuccess, onError);

    if (padlock == NULL) {
        printf("Error al crear el candado\r\n");
        return -1;
    } else {
        printf("Candado creado\r\n");
    }

    while (true) {
        PadlockTick(padlock);
    }
}

/* === End of documentation ======================================================================================== */
