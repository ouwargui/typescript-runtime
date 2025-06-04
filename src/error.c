#include "error.h"

struct error_t create_error(const char *msg, int code)
{
  struct error_t err;
  err.msg = msg;
  err.code = code;
  return err;
}
