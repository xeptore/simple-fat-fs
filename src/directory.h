#pragma once
#include <stdio.h>
#include "constants.h"
#include "fat.h"

typedef struct
{
  FatTableEntry first_fat_table_record;
  char filename[MAX_FILENAME_LENGTH + 1]; // 1 more byte for null-terminator
} DirectoryEntry;

typedef struct
{
  unsigned char capacity;
  unsigned char length;
  DirectoryEntry directory_entries[ROOT_DIRECTORY_MAX_FILES];
} DirectoryFile;

DirectoryFile load_directory_file();

void serialize_directory_file(const DirectoryFile* directory, unsigned char* output);

void serialize_directory_entry(const DirectoryEntry* entry, unsigned char* output);

DirectoryEntry deserialize_directory_entry(const unsigned char* serialized_directory_file);

DirectoryFile deserialize_directory_file(const unsigned char* serialized_directory_file);

void persist_directory(const DirectoryFile* directory);

void insert_directory_entry(
  DirectoryFile* directory_file,
  const DirectoryEntry* directory_entries
);

bool directory_is_full(const DirectoryFile* directory_file);

bool filename_exists_in_directory(
  const DirectoryFile* directory,
  const char* filename
);

FatTableEntry get_file_fat_first_entry(
  const DirectoryFile* directory,
  const char* filename
);
