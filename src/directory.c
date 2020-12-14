#include "directory.h"
#include "constants.h"
#include "fat.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>

DirectoryEntry deserialize_directory_entry(
  const unsigned char* serialized_directory_entry
) {
  const unsigned char fat_entry_buffer[3] = {
    serialized_directory_entry[DIRECTORY_ENTRY_SIZE_IN_BYTES - 3],
    serialized_directory_entry[DIRECTORY_ENTRY_SIZE_IN_BYTES - 2],
    serialized_directory_entry[DIRECTORY_ENTRY_SIZE_IN_BYTES - 1],
  };
  const FatTableEntry fat_table_entry = deserialize_fat_entry(fat_entry_buffer);

  DirectoryEntry entry = {
    .first_fat_table_record = fat_table_entry
  };
  strcpy(entry.filename, (char*)serialized_directory_entry);
  return entry;
}

DirectoryFile deserialize_directory_file(
  const unsigned char* serialized_directory_file
) {
  const unsigned char capacity = (unsigned char)deserialize_fat_entry(&serialized_directory_file[0]);
  const unsigned char length = (unsigned char)deserialize_fat_entry(&serialized_directory_file[1]);

  DirectoryFile directory = {
    .capacity = capacity,
    .length = length,
  };
  for (size_t i = 0; i < ROOT_DIRECTORY_MAX_FILES; i++) {
    directory.directory_entries[i] = deserialize_directory_entry(&serialized_directory_file[2 + (i * DIRECTORY_ENTRY_SIZE_IN_BYTES)]);
  }

  return directory;
}

void serialize_directory_entry(
  const DirectoryEntry* entry,
  unsigned char* output
) {
  strcpy((char*)output, entry->filename);

  unsigned char fat_table_entry_buffer[] = INITIALIZE(3, 0);
  serialize_fat_entry(entry->first_fat_table_record, fat_table_entry_buffer);
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 3] = fat_table_entry_buffer[0];
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 2] = fat_table_entry_buffer[1];
  output[DIRECTORY_ENTRY_SIZE_IN_BYTES - 1] = fat_table_entry_buffer[2];
}

void serialize_directory_file(
  const DirectoryFile* directory,
  unsigned char* output
) {
  unsigned char int_serialization_buffer[] = INITIALIZE(3, 0);
  serialize_fat_entry(directory->capacity, int_serialization_buffer);
  output[0] = int_serialization_buffer[0];

  serialize_fat_entry(directory->length, int_serialization_buffer);
  output[1] = int_serialization_buffer[0];

  for (size_t i = 0; i < directory->length; i++) {
    serialize_directory_entry(
      &directory->directory_entries[i],
      &output[2 + (i * DIRECTORY_ENTRY_SIZE_IN_BYTES)]
    );
  }
}

DirectoryFile load_directory_file() {
  FILE* fp = fopen(DIRECTORY_FILENAME, "rb");
  unsigned char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = { 0 };
  fread(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return deserialize_directory_file(buffer);
}

void persist_directory(const DirectoryFile* directory) {
  FILE* fp = fopen(DIRECTORY_FILENAME, "wb+");
  unsigned char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES] = { 0 };
  serialize_directory_file(directory, buffer);
  fwrite(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return;
}

void insert_directory_entry(
  DirectoryFile* directory_file,
  const DirectoryEntry* directory_entries
) {
  directory_file->directory_entries[directory_file->length++] = *directory_entries;
}

bool directory_is_full(const DirectoryFile* directory_file) {
  return directory_file->length == directory_file->capacity;
}

bool filename_exists_in_directory(
  const DirectoryFile* directory,
  const char* filename
) {
  for (size_t i = 0; i < ROOT_DIRECTORY_MAX_FILES; i++) {
    if (directory->directory_entries[i].filename == filename) {
      return true;
    }
  }

  return false;
}
