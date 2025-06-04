#ifndef LEXER_H
#define LEXER_H

#include <stddef.h> /* For size_t */

enum token_type
{
  TOKEN_EOF,         // End of file
  TOKEN_IDENTIFIER,  // Identifiers
  TOKEN_NUMBER,      // Numeric literals
  TOKEN_STRING,      // String literals
  TOKEN_PLUS,        // +
  TOKEN_MINUS,       // -
  TOKEN_EQUALS,      // =
  TOKEN_SEMICOLON,   // ;
  TOKEN_LEFT_PAREN,  // (
  TOKEN_RIGHT_PAREN, // )
  TOKEN_ERROR        // Error token (for unrecognized characters)
};

struct token
{
  enum token_type type;
  unsigned start;  // Pointer to the start of the token in the source code
  size_t length;   // Length of the token in bytes
  unsigned line;   // Line number where the token was found
  unsigned column; // Column number where the token was found
};

struct lexer
{
  const char *source;
  size_t source_length; // Length of the source code
  unsigned curr_pos;    // Current position in the source code
  unsigned start_pos;   // Start position of the current token
  unsigned line;        // Current line number
  unsigned column;      // Current column number
};

/// @brief Initializes a lexer with the given source code
/// @param source The source code to lex
/// @return An initialized lexer
struct lexer init_lexer(const char *source, size_t source_length);

/// @brief Retrieves the next token from the lexer
/// @param lex Pointer to the lexer
/// @return The next token found in the source code
/// @note This function updates the lexer state accordingly
struct token next_token(struct lexer *lex);

/// @brief Advances the lexer to the next character and returns it
/// @param lex Pointer to the lexer
/// @return The next character in the source code, or '\0' if at the end
/// @note This function updates the line and column numbers accordingly
char advance_lexer(struct lexer *lex);

/// @brief Peeks at the next character without advancing the lexer
/// @param lex Pointer to the lexer
/// @return The next character in the source code, or '\0' if at the end
char peek_lexer(struct lexer *lex);

/// @brief Checks if the lexer has reached the end of the source code
/// @param lex Pointer to the lexer
/// @return True if the lexer is at the end of the source code, false otherwise
bool is_at_end(struct lexer *lex);

#endif // LEXER_H
