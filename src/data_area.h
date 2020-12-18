#include <stdio.h>

// Writes `block_data` at block `index` of `data_file`.
void save_block(FILE* data_file, int index, const unsigned char* block_data);
