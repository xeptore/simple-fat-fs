#include <stdio.h>
#include "fat.h"
#include "constants.h"
#include "macros.h"

#ifndef MAXIMUM_SOURCE_FILE_PATH_LENGTH
#define MAXIMUM_SOURCE_FILE_PATH_LENGTH 100U
#endif

FILE* open_source_file(char* source_file_path);

size_t read_block_n(
  FILE* source_file,
  const FatTableEntry block_index,
  unsigned char* output_buffer
);

void save_source_file(
  FILE* source_file,
  FILE* data_file,
  const FatTableEntry* fat_entries
);
