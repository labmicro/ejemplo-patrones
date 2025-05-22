/*********************************************************************************************************************
Copyright 2016-2025, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/
Copyright 2016-2025, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file logger.c
 ** @brief Implementación privada de la clase de manejo de bitacoras
 **/

/* === Headers files inclusions ==================================================================================== */

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

struct log_stream_s {
    FILE * file;
};

struct logger_s {
    log_stream_t stream;
    log_stream_interface_t interface;
};

/* === Private function declarations =============================================================================== */

static log_stream_t LogStreamFileOpen(char filename[]);

static void LogStreamFileWrite(log_stream_t stream, char message[]);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

const log_stream_interface_t LOG_STREAM_FILE = &(struct log_stream_interface_s){
    .LogStreamOpen = LogStreamFileOpen,
    .LogStreamWrite = LogStreamFileWrite,
};

/* === Private function definitions ================================================================================ */

static log_stream_t LogStreamFileOpen(char filename[]) {
    log_stream_t stream = malloc(sizeof(struct log_stream_s));
    if (stream) {
        stream->file = fopen(filename, "a");
    }
    return stream;
}

static void LogStreamFileWrite(log_stream_t stream, char message[]) {
    if (stream && stream->file) {
        fprintf(stream->file, "%s\n", message);
        fflush(stream->file);
    }
}

/* === Public function implementation ============================================================================== */

logger_t LoggerCreate(log_stream_interface_t interface) {
    logger_t self = malloc(sizeof(struct logger_s));
    if (self) {
        self->interface = interface;
        self->stream = self->interface->LogStreamOpen("bitacora.txt");
    }
    return self;
}

void LoggerRegister(logger_t self, log_level_t level, char * message) {
    static const char * LEVELS[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
    };
    char string[128];
    snprintf(string, sizeof(string), "%s:%s", LEVELS[level], message);
    self->interface->LogStreamWrite(self->stream, string);
}

/* === End of documentation ======================================================================================== */
