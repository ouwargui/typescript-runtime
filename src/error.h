#ifndef ERROR_H
#define ERROR_H

typedef struct
{
  const char *msg;
  int code;
} error_t;

/// @brief Creates an error struct with the given parameters
/// @param msg Error message
/// @param code Error code
/// @return An error_t struct containing the message and code
error_t create_error(const char *msg, int code);

#endif // ERROR_H
