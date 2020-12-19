#include "constants.h"
#include "types.h"
#include <stdio.h>

FILE* open_data_file() {
  FILE* partition_file = fopen(PARTITION_FILENAME, "r+b");
  fseek(partition_file, FAT_TABLE_SIZE_IN_BYTES, SEEK_SET);

  return partition_file;
}

size_t read_block_n(
  FILE* source_file,
  const FatTableEntry block_index,
  unsigned char* output_buffer
) {
  fpos_t before_seek_position;
  fgetpos(source_file, &before_seek_position);
  fseek(source_file, block_index * BLOCK_SIZE_IN_BYTES, SEEK_CUR);
  const size_t n_read_bytes = fread(output_buffer, BLOCK_SIZE_IN_BYTES, 1, source_file);
  fsetpos(source_file, &before_seek_position);
  return n_read_bytes;
}

void write_block_n(
  FILE* destination_file,
  const unsigned int block_index,
  const unsigned char* block_buffer
) {
  fpos_t before_seek_position;
  fgetpos(destination_file, &before_seek_position);
  fseek(destination_file, block_index * BLOCK_SIZE_IN_BYTES, SEEK_CUR);
  fwrite(block_buffer, BLOCK_SIZE_IN_BYTES, 1, destination_file);
  fsetpos(destination_file, &before_seek_position);
}
