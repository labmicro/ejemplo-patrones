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

/** @file main.c
 ** @brief Ejemplo de uso de interfaces abstractas en una clase que registra mensajes de error
 **/

/* === Headers files inclusions ==================================================================================== */

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

struct log_stream_s {
    log_stream_t file_stream;
};

/* === Private function declarations =============================================================================== */

static log_stream_t LogStreamConsoleOpen(char filename[]);

static void LogStreamConsoleWrite(log_stream_t stream, char message[]);

/* === Private variable definitions ================================================================================ */

const log_stream_interface_t LOG_STREAM_CONSOLE = &(struct log_stream_interface_s){
    .LogStreamOpen = LogStreamConsoleOpen,
    .LogStreamWrite = LogStreamConsoleWrite,
};

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static log_stream_t LogStreamConsoleOpen(char filename[]) {
    log_stream_t stream = malloc(sizeof(struct log_stream_s));
    if (stream) {
        stream->file_stream = LOG_STREAM_FILE->LogStreamOpen(filename);
    }
    return stream;
}

static void LogStreamConsoleWrite(log_stream_t stream, char message[]) {
    if (stream && stream->file_stream) {
        printf("%s\r\n", message);
        LOG_STREAM_FILE->LogStreamWrite(stream->file_stream, message);
    }
}
/* === Public function implementation ============================================================================== */

int main(void) {
    logger_t logger = LoggerCreate(LOG_STREAM_CONSOLE);

    LoggerRegister(logger, INFO, "Mensaje de información");

    while (true) {
    }
}
/* === End of documentation ======================================================================================== */
