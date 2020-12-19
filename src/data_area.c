#include "constants.h"
#include <stdio.h>

FILE* open_data_file() {
  FILE* partition_file = fopen(PARTITION_FILENAME, "r+b");
  fseek(partition_file, FAT_TABLE_SIZE_IN_BYTES, SEEK_SET);

  return partition_file;
}

void save_block(
  FILE* data_file,
  const int index,
  const unsigned char* block_data
) {
  fpos_t before_seek_position;
  fgetpos(data_file, &before_seek_position);
  fseek(data_file, index * BLOCK_SIZE_IN_BYTES, SEEK_CUR);
  fwrite(block_data, BLOCK_SIZE_IN_BYTES, 1, data_file);
  fsetpos(data_file, &before_seek_position);
}
