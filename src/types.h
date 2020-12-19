#pragma once
#include "constants.h"

typedef unsigned int FatTableEntry;

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
