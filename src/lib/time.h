#ifndef TIME_H
#define TIME_H

#include <time.h>

/// @brief Holds the current time in seconds since the epoch.
time_t g_current_time;

/// @brief Pointer to a struct tm that holds the current local time.
struct tm *g_m_time;

/// @brief Provides functions to get the current time and date.
void get_time(void);

#endif // TIME_H
