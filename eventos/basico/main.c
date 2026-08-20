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
 */
static void onSuccess(void);

/**
 * @brief Función para gestionar las notificaciones de error
 */
static void onError(void);

/* === Private function definitions ================================================================================ */

static void onSuccess(void) {
    printf("Clave correcta\r\n");
}

static void onError(void) {
    printf("Clave incorrecta\r\n");
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
