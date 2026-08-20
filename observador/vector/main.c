/* === Headers files inclusions ==================================================================================== */

#include "keyboard.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para gestionar las notificaciones de cualquier tecla
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void AllKeys(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de letras minúsculas
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void LowerCase(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de dígitos
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void Digits(keyboard_t sender, char key);

/**
 * @brief Función para gestionar las notificaciones de letras mayúsculas
 *
 * @param sender Puntero al teclado que genera el evento
 * @param key Tecla pulsada
 */
static void UpperCase(keyboard_t sender, char key);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static void AllKeys(keyboard_t sender, char key) {
    printf("Se ha pulsado una tecla\r\n");

    if (key == 'X') {
        KeyboardRemove(sender, AllKeys);
    }
}

static void LowerCase(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a una letra minuscula\r\n");
}

static void Digits(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a un digito\r\n");
}

static void UpperCase(keyboard_t sender, char key) {
    printf("Tecla pulsada corresponde a una letra mayuscula\r\n");
}

/* === Public function implementation ============================================================================== */

int main(void) {
    keyboard_t keyboard = KeyboardCreate();

    if (keyboard == NULL) {
        printf("Error al crear el teclado\r\n");
        return -1;
    }

    KeyboardSubscribe(keyboard, '!', '}', AllKeys);
    KeyboardSubscribe(keyboard, 'A', 'Z', UpperCase);
    KeyboardSubscribe(keyboard, 'a', 'z', LowerCase);
    KeyboardSubscribe(keyboard, '0', '9', Digits);

    while (true) {
        KeyboardTick(keyboard);
    }
}

/* === End of documentation ======================================================================================== */
