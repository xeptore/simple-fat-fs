#include "directory.h"
#include "constants.h"
#include <stdio.h>

DirectoryFile deserialize_directory_file(
  const char *serialized_directory_file
) {
  DirectoryFile directory = {
    .capacity = 32,
    .directory_entries = NULL,
    .length = 0,
  };
  return directory;
}

DirectoryEntry deserialize_directory_entry(
  const unsigned char *serialized_directory_file
) {
  const unsigned char fat_entry_buffer[3] = {
    serialized_directory_file[DIRECTORY_ENTRY_SIZE_IN_BYTES - 3],
    serialized_directory_file[DIRECTORY_ENTRY_SIZE_IN_BYTES - 2],
    serialized_directory_file[DIRECTORY_ENTRY_SIZE_IN_BYTES - 1],
  };
  const FatTableEntry fat_table_entry = deserialize_fat_entry(fat_entry_buffer);

  DirectoryEntry entry = {
    .first_fat_table_record = fat_table_entry
  };
  strcpy(entry.filename, (char *)serialized_directory_file);
  return entry;
}

void serialize_directory_entry(
  const DirectoryEntry *entry,
  unsigned char *output
) {
  strcpy((char *)output, entry->filename);

  unsigned char fat_table_entry_buffer[] = INITIALIZE(3, 0);
  serialize_fat_entry(entry->first_fat_table_record, fat_table_entry_buffer);
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 3] = fat_table_entry_buffer[0];
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 2] = fat_table_entry_buffer[1];
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 1] = fat_table_entry_buffer[2];
}

void serialize_directory_file(
  const DirectoryFile *directory,
  unsigned char *output
) {
  unsigned char int_serialization_buffer[] = INITIALIZE(3, 0);
  serialize_fat_entry(directory->capacity, int_serialization_buffer);
  output[0] = int_serialization_buffer[0];
  output[1] = int_serialization_buffer[1];

  serialize_fat_entry(directory->length, int_serialization_buffer);
  output[2] = int_serialization_buffer[0];
  output[3] = int_serialization_buffer[1];

  for (size_t i = 0; i < directory->length; i++) {
    serialize_directory_entry(
      &directory->directory_entries[i],
      &output[4 + (i * DIRECTORY_ENTRY_SIZE_IN_BYTES)]
    );
  }
}

DirectoryFile load_directory_file() {
  FILE *fp = fopen(DIRECTORY_FILENAME, "rb");
  unsigned char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = {0};
  fread(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return deserialize_directory_file(buffer);
}

void persist_directory(const DirectoryFile *directory) {
  FILE *fp = fopen(DIRECTORY_FILENAME, "wb+");
  unsigned char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = {0};
  serialize_directory_file(directory, buffer);
  fwrite(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return;
}

void insert_directory_entry(
  DirectoryFile *directory_file,
  const DirectoryEntry *directory_entries
) {
  directory_file->directory_entries[directory_file->length++] = *directory_entries;
}

bool directory_is_full(const DirectoryFile *directory_file) {
  return directory_file->length == directory_file->capacity;
}

bool filename_exists_in_directory(
  const DirectoryFile *directory,
  const char *filename
) {
  for (size_t i = 0; i < ROOT_DIRECTORY_MAX_FILES; i++) {
    if (directory->directory_entries[i].filename == filename) {
      return true;
    }
  }

  return false;
}
