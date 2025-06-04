#include <stdarg.h>
#include <stdio.h>

#include "logger.h"
#include "time.h"

char *type[LOG_LEVEL_LEN] = {
    "DEBUG",
    "SUCCESS",
    "WARN",
    "ERR"};

char *colors[LOG_LEVEL_LEN] = {
    "\x1b[0m",
    "\x1b[32m",
    "\x1b[1;33m",
    "\x1b[31m"};

void ulogger_log(enum log_level level, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  get_time();

  // printf("[%d/%d/%d -> %.2d:%.2d:%.2d][%s] ", g_m_time->tm_mday,
  //        g_m_time->tm_mon,
  //        g_m_time->tm_year + 1900,
  //        g_m_time->tm_hour,
  //        g_m_time->tm_min,
  //        g_m_time->tm_sec,
  //        type[level]);

  printf("[%s] ", type[level]);
  vfprintf(stdout, fmt, args);
  printf("\n%s", colors[LOG_LEVEL_DEBUG]);
  va_end(args);
}
