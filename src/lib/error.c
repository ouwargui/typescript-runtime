#include "error.h"

struct error create_error(const char *msg, int code)
{
  struct error err;
  err.msg = msg;
  err.code = code;
  return err;
}
