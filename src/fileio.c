#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "error.h"
#include "fileio.h"

struct load_file_result load_file(const char *file_path)
{
  struct load_file_result result;

  if (!file_path)
  {
    result.type = load_file_ERR;
    result.err = create_error("File path is NULL", EX_USAGE);
    return result;
  }

  FILE *file = fopen(file_path, "r");
  if (file == NULL)
  {
    result.type = load_file_ERR;
    result.err = create_error("Failed to open file", EX_NOINPUT);
    return result;
  }

  /* Get file size */
  if (fseek(file, 0, SEEK_END) != 0)
  {
    result.type = load_file_ERR;
    result.err = create_error("Failed to seek to end of file", EX_IOERR);
    fclose(file);
    return result;
  }

  long file_size_long = ftell(file);
  if (file_size_long < 0)
  {
    result.type = load_file_ERR;
    result.err = create_error("Failed to determine file size", EX_IOERR);
    fclose(file);
    return result;
  }

  size_t file_size = (size_t)file_size_long;

  /* Rewind to the beginning of the file */
  rewind(file);

  /* Allocate memory for file content */
  char *file_content = malloc(file_size + 1);
  if (file_content == NULL)
  {
    result.type = load_file_ERR;
    result.err = create_error("Failed to allocate memory for file content", EX_OSERR);
    fclose(file);
    return result;
  }

  /* Read file content */
  size_t bytes_read = fread(file_content, 1, file_size, file);
  if (bytes_read != file_size)
  {
    result.type = load_file_ERR;
    result.err = create_error("Failed to read file content", EX_IOERR);
    free(file_content);
    fclose(file);
    return result;
  }

  /* Null-terminate the string */
  file_content[file_size] = '\0';

  /* Create result struct */
  result.type = load_file_OK;
  result.ok = create_file_struct(
      file_path,
      file_content,
      file_size);

  /* Close file */
  fclose(file);
  return result;
}

struct load_file_t create_file_struct(const char *file_path, char *file_content, size_t file_size)
{
  struct load_file_t file;
  file.file_path = file_path;
  file.file_content = file_content;
  file.file_size = file_size;
  return file;
}

void free_load_file_result(struct load_file_t *result)
{
  if (!result)
  {
    return; /* Nothing to free if result is NULL */
  }

  /* Free file content */
  if (result->file_content)
  {
    free(result->file_content);
    result->file_content = NULL;
  }

  result->file_path = NULL;
  result->file_size = 0;
}
