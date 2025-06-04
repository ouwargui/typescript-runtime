#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

enum log_level
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_LEN
};

void ulogger_log(enum log_level level, const char *fmt, ...);

#define DEBUG(...) ulogger_log(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define INFO(...) ulogger_log(LOG_LEVEL_INFO, __VA_ARGS__)
#define WARNING(...) ulogger_log(LOG_LEVEL_WARNING, __VA_ARGS__)
#define ERROR(...) ulogger_log(LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG ulogger_log

#endif
