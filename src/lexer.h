#ifndef LEXER_H
#define LEXER_H

#include <stddef.h> /* For size_t */

enum TokenType
{
  TOKEN_EOF,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_EQUALS,
  TOKEN_SEMICOLON,
};

struct Token
{
  enum TokenType type;
  const char *start; // Pointer to the start of the token in the source code
  size_t length;     // Length of the token
};

#endif // LEXER_H
