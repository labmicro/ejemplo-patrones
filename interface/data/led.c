/* === Headers files inclusions ==================================================================================== */

#include "led.h"
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

struct led_s {
    digital_output_interface_t digital_output;
    void * data;
};

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

led_t LedCreate(digital_output_interface_t digital_output, void * data) {
    led_t self = NULL;

    if (digital_output) {
        self = malloc(sizeof(struct led_s));
        if (self) {
            self->digital_output = digital_output;
            self->data = data;
        }
    }
    return self;
}

void LedTurnOn(led_t self) {
    if (self && self->digital_output && self->digital_output->SetState) {
        self->digital_output->SetState(self->data, true);
    }
}

void LedTurnOff(led_t self) {
    if (self && self->digital_output && self->digital_output->SetState) {
        self->digital_output->SetState(self->data, false);
    }
}

void LedToggle(led_t self) {
    if (self && self->digital_output && self->digital_output->GetState && self->digital_output->SetState) {
        bool state = self->digital_output->GetState(self->data);
        self->digital_output->SetState(self->data, !state);
    }
}

bool LedIsOn(led_t self) {
    bool state = false;

    if (self && self->digital_output && self->digital_output->GetState) {
        state = self->digital_output->GetState(self->data);
    }
    return state;
}

/* === End of documentation ======================================================================================== */
