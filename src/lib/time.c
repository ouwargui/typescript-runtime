#include <time.h>

#include "time.h"

time_t g_current_time;
struct tm *g_m_time;

void get_time(void)
{
  time(&g_current_time);
  g_m_time = localtime(&g_current_time);
}
