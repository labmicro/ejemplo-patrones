/* === Headers files inclusions ==================================================================================== */

#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/** Tipo de datos para un cliente suscrito al teclado */
typedef struct client_s * client_t;

/** Estructura para un cliente suscrito al teclado */
struct client_s {
    char from_char;
    char to_char;
    keyboard_event_t EventHandler;
    client_t previous_client;
    client_t next_client;
};

/** Estructura del objeto teclado */
struct keyboard_s {
    client_t clients;
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Función para configurar el terminal para la lectura de teclas
 *
 * @details Configura la entrada estándar en modo no canónico y sin eco,
 *          para que cada tecla se reciba de inmediato.
 */
static void KeyboardConfigure(void);

/**
 * @brief Función para buscar un cliente por su manejador de eventos
 *
 * @param self Puntero al teclado
 * @param handler Manejador de eventos a buscar
 * @return Puntero al cliente encontrado o NULL si no existe
 */
static client_t KeyboardFind(keyboard_t self, keyboard_event_t handler);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static void KeyboardConfigure(void) {
    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= (~ICANON & ~ECHO);
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

static client_t KeyboardFind(keyboard_t self, keyboard_event_t handler) {
    client_t client = self->clients;

    while (client != NULL) {
        if (client->EventHandler == handler) {
            return client;
        }
        client = client->next_client;
    }
    return NULL;
}

/* === Public function implementation ============================================================================== */

keyboard_t KeyboardCreate(void) {
    keyboard_t self = malloc(sizeof(struct keyboard_s));

    if (self) {
        KeyboardConfigure();
        self->clients = NULL;
    }
    return self;
}

bool KeyboardSubscribe(keyboard_t self, char from, char to, keyboard_event_t handler) {
    client_t client;

    if ((!self) || (!handler) || (from > to)) {
        return false;
    }

    client = KeyboardFind(self, handler);
    if (client == NULL) {
        client = malloc(sizeof(struct client_s));
        if (client) {
            client->next_client = self->clients;
            if (client->next_client) {
                client->next_client->previous_client = client;
            }
            client->previous_client = NULL;
            self->clients = client;
        }
    }
    if (client) {
        client->from_char = from;
        client->to_char = to;
        client->EventHandler = handler;
    }
    return (client != NULL);
}

bool KeyboardRemove(keyboard_t self, keyboard_event_t handler) {
    client_t client;

    if (!self) {
        return false;
    }

    client = KeyboardFind(self, handler);
    if (client) {
        if (client->previous_client) {
            client->previous_client->next_client = client->next_client;
        } else {
            self->clients = client->next_client;
        }
        if (client->next_client) {
            client->next_client->previous_client = client->previous_client;
        }
        free(client);
    }
    return (client != NULL);
}

void KeyboardTick(keyboard_t self) {
    if (!self) {
        return;
    }

    int key = getchar();
    if (key != EOF) {
        client_t client = self->clients;
        while (client != NULL) {
            client_t next_client = client->next_client;
            if ((client->EventHandler) && (client->from_char <= key) && (key <= client->to_char)) {
                client->EventHandler(self, (char)key);
            }
            client = next_client;
        }
    }
}

/* === End of documentation ======================================================================================== */
