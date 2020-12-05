#include "directory.h"
#include "constants.h"
#include <stdio.h>

DirectoryFile deserialize_directory_file(
  const char *serialized_directory_file
) {
  DirectoryFile directory = {
      .capacity = 32,
      .directory_entry = NULL,
      .length = 0,
  };
  return directory;
}

void serialize_directory_file(
  const DirectoryFile *directory,
  char *output
) {
  // TODO: fill `output` with serialized version of `directory`.
}

DirectoryFile load_directory_file() {
  FILE *fp = fopen(DIRECTORY_FILENAME, "rb");
  char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = {0};
  fread(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return deserialize_directory_file(buffer);
}

void persist_directory(const DirectoryFile *directory) {
  FILE *fp = fopen(DIRECTORY_FILENAME, "wb+");
  char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = {0};
  serialize_directory_file(directory, buffer);
  fwrite(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return;
}

void insert_directory_entry(
  DirectoryFile *directory_file,
  const DirectoryEntry *directory_entry
) {
  directory_file->directory_entry[directory_file->length++] = *directory_entry;
}

bool directory_is_full(const DirectoryFile *directory_file) {
  return directory_file->length == directory_file->capacity;
}

bool filename_exists_in_directory(
  const DirectoryFile *directory,
  const char *filename
) {
  for (size_t i = 0; i < ROOT_DIRECTORY_MAX_FILES; i++) {
    if (directory->directory_entry[i].filename == filename) {
      return true;
    }
  }

  return false;
}
