#include <stdio.h>
#include <stdbool.h>

#include "lexer.h"
#include "lib/logger.h"

static void skip_whitespace(struct lexer *lex);
static bool is_alpha(char c);
static bool is_digit(char c);
static struct token identifier(struct lexer *lex);
static struct token number(struct lexer *lex);
static struct token string(struct lexer *lex);
static struct token error_token(const char *message, struct lexer *lex);
static struct token make_token(enum token_type type, struct lexer *lex);
static void log_token(const struct token *tok);

struct lexer init_lexer(const char *source, size_t source_length)
{
  struct lexer lex;
  lex.source = source;
  lex.source_length = source_length;
  lex.curr_pos = 0;
  lex.start_pos = 0;
  lex.line = 1;
  lex.column = 1;
  return lex;
}

struct token next_token(struct lexer *lex)
{
  skip_whitespace(lex);
  lex->start_pos = lex->curr_pos;

  if (is_at_end(lex))
  {
    return make_token(TOKEN_EOF, lex);
  }

  char c = advance_lexer(lex);

  switch (c)
  {
  case '+':
    return make_token(TOKEN_PLUS, lex);
  case '-':
    return make_token(TOKEN_MINUS, lex);
  case '=':
    return make_token(TOKEN_EQUALS, lex);
  case ';':
    return make_token(TOKEN_SEMICOLON, lex);
  case '(':
    return make_token(TOKEN_LEFT_PAREN, lex);
  case ')':
    return make_token(TOKEN_RIGHT_PAREN, lex);
  }

  if (is_alpha(c))
  {
    return identifier(lex);
  }

  if (is_digit(c))
  {
    return number(lex);
  }

  if (c == '"')
  {
    return string(lex);
  }

  return error_token("Unexpected character", lex);
}

char advance_lexer(struct lexer *lex)
{
  if (is_at_end(lex))
  {
    DEBUG("LEXER: Reached end of source at line %u, column %u", lex->line, lex->column);
    return '\0';
  }

  char c = lex->source[lex->curr_pos++];

  if (c == '\n')
  {
    DEBUG("LEXER: New line at line %u, column %u", lex->line, lex->column);
    lex->line++;
    lex->column = 1;
  }
  else
  {
    DEBUG("LEXER: Advancing to character '%c' at line %u, column %u", c, lex->line, lex->column);
    lex->column++;
  }

  return c;
}

char peek_lexer(struct lexer *lex)
{
  if (is_at_end(lex))
  {
    return '\0';
  }

  return lex->source[lex->curr_pos];
}

char peek_next(struct lexer *lex)
{
  if (lex->curr_pos + 1 >= lex->source_length)
  {
    return '\0';
  }
  return lex->source[lex->curr_pos + 1];
}

static bool is_alpha(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c)
{
  return (c >= '0' && c <= '9');
}

static void skip_whitespace(struct lexer *lex)
{
  while (!is_at_end(lex))
  {
    char c = peek_lexer(lex);
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
    {
      DEBUG("LEXER: Skipping whitespace at line %u, column %u", lex->line, lex->column);
      advance_lexer(lex);
    }
    else
    {
      break;
    }
  }
}

bool is_at_end(struct lexer *lex)
{
  return lex->source[lex->curr_pos] == '\0';
}

static struct token identifier(struct lexer *lex)
{
  while (!is_at_end(lex) && (is_alpha(peek_lexer(lex)) || is_digit(peek_lexer(lex))))
  {
    advance_lexer(lex);
  }

  return make_token(TOKEN_IDENTIFIER, lex);
}

static struct token number(struct lexer *lex)
{
  while (!is_at_end(lex) && is_digit(peek_lexer(lex)))
  {
    advance_lexer(lex);
  }

  if (!is_at_end(lex) && peek_lexer(lex) == '.' && peek_next(lex) != '\0' && is_digit(peek_next(lex)))
  {
    advance_lexer(lex); // Consume the '.'

    while (!is_at_end(lex) && is_digit(peek_lexer(lex)))
    {
      advance_lexer(lex);
    }
  }

  return make_token(TOKEN_NUMBER, lex);
}

static struct token string(struct lexer *lex)
{
  while (!is_at_end(lex) && peek_lexer(lex) != '"')
  {
    char c = peek_lexer(lex);
    if (c == '\n')
    {
      return error_token("Unterminated string literal", lex);
    }
    advance_lexer(lex);
  }

  if (is_at_end(lex))
  {
    return error_token("Unterminated string literal", lex);
  }

  advance_lexer(lex);

  return make_token(TOKEN_STRING, lex);
}

static struct token error_token(const char *message, struct lexer *lex)
{
  DEBUG("LEXER: Error at line %u, column %u: %s", lex->line, lex->column, message);
  struct token tok;
  tok.type = TOKEN_ERROR;
  tok.start = lex->start_pos;
  tok.length = lex->curr_pos - lex->start_pos;
  tok.line = lex->line;
  tok.column = lex->column - tok.length; // Adjust column to the start of the token
  return tok;
}

static struct token make_token(enum token_type type, struct lexer *lex)
{
  struct token tok;
  tok.type = type;
  tok.start = lex->start_pos;
  tok.length = lex->curr_pos - lex->start_pos;
  tok.line = lex->line;
  tok.column = lex->column - tok.length; // Adjust column to the start of the token
  DEBUG("LEXER: Created token of type %d at line %u, column %u", type, tok.line, tok.column);
  log_token(&tok);
  return tok;
}

static void log_token(const struct token *tok)
{
  const char *type_str;
  switch (tok->type)
  {
  case TOKEN_EOF:
    type_str = "EOF";
    break;
  case TOKEN_IDENTIFIER:
    type_str = "IDENTIFIER";
    break;
  case TOKEN_NUMBER:
    type_str = "NUMBER";
    break;
  case TOKEN_STRING:
    type_str = "STRING";
    break;
  case TOKEN_PLUS:
    type_str = "PLUS";
    break;
  case TOKEN_MINUS:
    type_str = "MINUS";
    break;
  case TOKEN_EQUALS:
    type_str = "EQUALS";
    break;
  case TOKEN_SEMICOLON:
    type_str = "SEMICOLON";
    break;
  case TOKEN_LEFT_PAREN:
    type_str = "LEFT_PAREN";
    break;
  case TOKEN_RIGHT_PAREN:
    type_str = "RIGHT_PAREN";
    break;
  case TOKEN_ERROR:
    type_str = "ERROR";
    break;
  default:
    type_str = "UNKNOWN";
  }

  DEBUG("Token: Type=%s, Start=%u, Length=%zu, Line=%u, Column=%u",
        type_str, tok->start, tok->length, tok->line, tok->column);
}
