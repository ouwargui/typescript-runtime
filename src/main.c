#include <stdio.h>
#include <stdbool.h>
#include <sysexits.h>

#include "fileio.h"

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
    printf("Error: %s (code: %d)\n", file_result.err.msg, file_result.err.code);
    return file_result.err.code;
  }

  file_data = file_result.ok;

  free_load_file_result(&file_data);

  return EX_OK;
}

bool is_arguments_valid(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: %s path/to/ts/file\n", PROGRAM_NAME);
    return false;
  }

  if (argv[1] == NULL || argv[1][0] == '\0')
  {
    printf("Error: No TypeScript file specified.\n");
    return false;
  }

  return true;
}
