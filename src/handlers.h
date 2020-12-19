#pragma once
#include "directory.h"
#include "fat.h"

int handle_reserve(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const char* destination_file_name
);

typedef struct StoreReservedArgs {
  char source_file_path[100];
  char destination_file_name[MAX_FILENAME_LENGTH];
} StoreReservedArgs;
int handle_store_reserved(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  StoreReservedArgs* args
);

typedef struct StoreArgs {
  char source_file_path[100];
  char destination_file_name[MAX_FILENAME_LENGTH];
} StoreArgs;
int handle_store(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  StoreArgs* args
);

typedef struct RestoreArgs {
  char source_file_name[MAX_FILENAME_LENGTH];
  char destination_file_path[100];
} RestoreArgs;
int handle_restore(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const RestoreArgs* args
);
