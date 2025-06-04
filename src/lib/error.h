#ifndef ERROR_H
#define ERROR_H

struct error
{
  const char *msg;
  int code;
};

/// @brief Creates an error struct with the given parameters
/// @param msg Error message
/// @param code Error code
/// @return An error struct containing the message and code
struct error create_error(const char *msg, int code);

#endif // ERROR_H
