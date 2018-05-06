#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdarg.h>

typedef enum log_level {
    LOG_SILENT,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
} level_t;

#define log_debug(...)     log_func_impl(LOG_DEBUG,   __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)   log_func_impl(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)      log_func_impl(LOG_INFO,    __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)     log_func_impl(LOG_ERROR,   __FILE__, __LINE__, __VA_ARGS__)
#define log_set(X)              log_enable(X)

void log_enable(level_t level);  /* Enables logging or not */
/**
 * @brief Log function implementation
 *
 * @param level
 * @param filename
 * @param line
 * @param fmt
 * @param ...
 */
void log_func_impl(level_t level, const char* filename, unsigned line, const char* fmt, ...);

#endif /*LOG_H_*/

