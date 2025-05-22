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

#ifndef LOGGER_H_
#define LOGGER_H_

/** @file logger.h
 ** @brief Declaraciones publicas para la clase de manejo de bitacoras
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/** Tipo de datos para un flujo de datos de bitacora */
typedef struct log_stream_s * log_stream_t;

/** Puntero a función para la apertura de un flujo de datos de bitacora */
typedef log_stream_t (*log_stream_open_t)(char[]);

/** Puntero a función para la escritura de datos de un flujo de bitacora */
typedef void (*log_stream_write_t)(log_stream_t, char[]);

/** Tipo de datos para la interfaz de un flujo de datos de bitacora */
typedef struct log_stream_interface_s {
    log_stream_open_t LogStreamOpen;
    log_stream_write_t LogStreamWrite;
} const * log_stream_interface_t;

/** Tipo de datos para el nivel de gravedad de un evento de bitacora */
typedef enum log_level_e {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
} log_level_t;

/** Tipo de datos para una bitacora */
typedef struct logger_s * logger_t;

/* === Public variable declarations ================================================================================ */

extern const log_stream_interface_t LOG_STREAM_FILE;

/* === Public function declarations ================================================================================ */

/**
 * @brief Función para crear una bitacora
 *
 * @param interface Interfaz para el flujo de datos de la bitacora
 * @return logger_t Puntero a la bitacora creada
 */
logger_t LoggerCreate(log_stream_interface_t interface);

/**
 * @brief Función registrar un evento en una bitacora
 *
 * @param self Puntero a la bitacora
 * @param level Gravedad del evento que se registra
 * @param message Mensaje con la descripción del evento
 */
void LoggerRegister(logger_t self, log_level_t level, char * message);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H_ */
