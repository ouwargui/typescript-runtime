#include "lexer.h"

struct token create_token(enum token_type type, const char *start, size_t length)
{
  struct token token;
  token.type = type;
  token.start = start;
  token.length = length;
  return token;
}
