#include <stdio.h>

// So... It opens data file 😃
FILE* open_data_file();

// Reads block `block_index`th of `source_file` and copied into `output_buffer`.
size_t read_block_n(
  FILE* source_file,
  const FatTableEntry block_index,
  unsigned char* output_buffer
);

// Writes `block_buffer` to `block_index`th block of `destination_file`.
void write_block_n(
  FILE* destination_file,
  const unsigned int block_index,
  const unsigned char* block_buffer
);
