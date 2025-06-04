#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h> /* For size_t */

#include "lib/error.h"
#include "../include/result.h"

/// @struct load_file_t
/// @brief Structure to hold loaded file data
/// @param file_path Path to the file
/// @param file_content Content of the file as a null-terminated string
/// @param file_size Size of the file content in bytes (excluding null terminator)
struct load_file
{
  const char *file_path;
  char *file_content;
  size_t file_size;
};

/// Using the error_t from error.h
DECL_RESULT(load_file, struct load_file, struct error)

/// @brief Loads a file from the given path
/// @param file_path Path to the file to load
/// @return Result containing either loaded file data or an error
struct load_file_result load_file(const char *file_path);

/// @brief Creates a file struct with the given parameters
/// @param file_path Path to the file
/// @param file_content Content of the file
/// @param file_size Size of the file content
/// @return load_file_t struct
struct load_file create_file_struct(const char *file_path, char *file_content, size_t file_size);

/// @brief Frees resources associated with a load_file_result_t
/// @param result Pointer to the result to free
void free_load_file_result(struct load_file *result);

#endif // FILEIO_H
