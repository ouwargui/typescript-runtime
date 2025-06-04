#include "lexer.h"

struct Token create_token(enum TokenType type, const char *start, size_t length)
{
  struct Token token;
  token.type = type;
  token.start = start;
  token.length = length;
  return token;
}
