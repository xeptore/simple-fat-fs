#pragma once
#include "directory.h"
#include "fat.h"

int handle_new_filename(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const char* destination_file_name
);

typedef struct StoreReservedArgs {
  char source_file_path[100];
  char destination_file_name[MAX_FILENAME_LENGTH];
} StoreReservedArgs;
int handle_save_file(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  StoreReservedArgs* args
);

typedef struct StoreArgs {
  char source_file_path[100];
  char destination_file_name[MAX_FILENAME_LENGTH];
} StoreArgs;
int handle_save_new_file(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  StoreArgs* args
);

typedef struct RestoreArgs {
  char source_file_name[MAX_FILENAME_LENGTH];
  char destination_file_path[100];
} RestoreArgs;
int handle_restore_file(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const RestoreArgs* args
);
