#ifndef ERROR_H
#define ERROR_H

struct error_t
{
  const char *msg;
  int code;
};

/// @brief Creates an error struct with the given parameters
/// @param msg Error message
/// @param code Error code
/// @return An error_t struct containing the message and code
struct error_t create_error(const char *msg, int code);

#endif // ERROR_H
