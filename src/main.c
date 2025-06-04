#include <stdio.h>
#include <stdbool.h>
#include <sysexits.h>

#include "fileio.h"
#include "lexer.h"
#include "lib/logger.h"

bool is_arguments_valid(int argc, char **argv);
const char *PROGRAM_NAME = "typescript-runtime";

int main(int argc, char **argv)
{
  if (!is_arguments_valid(argc, argv))
  {
    return EX_USAGE;
  }

  struct load_file_result file_result = load_file(argv[1]);
  struct load_file file_data;

  if (file_result.type == load_file_ERR)
  {
    ERROR("%s (code: %d)", file_result.err.msg, file_result.err.code);
    return file_result.err.code;
  }

  file_data = file_result.ok;

  struct lexer lex = init_lexer(file_data.file_content, file_data.file_size);

  while (true)
  {
    struct token tok = next_token(&lex);

    if (tok.type == TOKEN_EOF)
    {
      break;
    }
  }

  free_load_file_result(&file_data);

  return EX_OK;
}

bool is_arguments_valid(int argc, char **argv)
{
  if (argc != 2)
  {
    ERROR("Usage: %s path/to/ts/file\n", PROGRAM_NAME);
    return false;
  }

  if (argv[1] == NULL || argv[1][0] == '\0')
  {
    ERROR("No TypeScript file specified.\n");
    return false;
  }

  return true;
}
