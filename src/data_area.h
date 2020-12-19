#include <stdio.h>

// So... It opens data file 😃
FILE* open_data_file();

// Writes `block_data` at block `index` of `data_file`.
void save_block(FILE* data_file, int index, const unsigned char* block_data);
