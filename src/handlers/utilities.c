#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "fat.h"
#include "constants.h"
#include "macros.h"
#include "data_area.h"

const unsigned short int MAXIMUM_SOURCE_FILE_PATH_LENGTH = 100U;

FILE* open_source_file(char* source_file_path) {
  FILE* source_file = fopen(source_file_path, "rb");
  if (source_file == NULL) {
    fprintf(
      stderr,
      "Error opening file '%s': %s\n",
      source_file_path,
      strerror(errno)
    );
    exit(errno);
  }
  return source_file;
}

void save_source_file(
  FILE* source_file,
  FILE* data_file,
  const FatTableEntry* fat_entries
) {
  for (size_t i = 0; i < 10; i++) {
    unsigned char block_buffer[] = INITIALIZE(BLOCK_SIZE_IN_BYTES, '\000');
    read_block_n(source_file, i, block_buffer);
    write_block_n(data_file, fat_entries[i], block_buffer);
  }
}
