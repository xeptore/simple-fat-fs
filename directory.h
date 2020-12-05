#include <stdio.h>
#include "constants.h"

typedef struct
{
  char *filename;
  int first_fat_table_record;
} DirectoryEntry;

typedef struct
{
  size_t capacity;
  size_t length;
  DirectoryEntry *directory_entry;
} DirectoryFile;

DirectoryFile load_directory_file();

void persist_directory(const DirectoryFile *directory);

void insert_directory_entry(
  DirectoryFile *directory_file,
  const DirectoryEntry *directory_entry
);

bool directory_is_full(const DirectoryFile *directory_file);

bool filename_exists_in_directory(
  const DirectoryFile *directory,
  const char *filename
);
