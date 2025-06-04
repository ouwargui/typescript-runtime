#include "error.h"

error_t create_error(const char *msg, int code)
{
  error_t err;
  err.msg = msg;
  err.code = code;
  return err;
}
