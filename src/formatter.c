#include <stdio.h>
#include "constants.h"
#include "macros.h"
#include "formatter.h"
#include "directory.h"

void format_fat_area(FILE* fp) {
  unsigned char fat_table_buffer[] = INITIALIZE(FAT_ENTRIES * 3, '\000');
  for (size_t i = 0; i < FAT_ENTRIES * 3; i += 3)
  {
    fat_table_buffer[i + 0] = (FAT_EMPTY_ENTRY >> 0) % 256;
    fat_table_buffer[i + 1] = (FAT_EMPTY_ENTRY >> 8) % 256;
    fat_table_buffer[i + 2] = (FAT_EMPTY_ENTRY >> 16) % 256;
  }

  fwrite(fat_table_buffer, sizeof fat_table_buffer, 1, fp);
}

void format_data_area(FILE* fp) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    char buffer[BLOCK_SIZE_IN_BYTES] = { 0 };
    fwrite(buffer, sizeof buffer, 1, fp);
  }
}

void format_partition() {
  FILE* fp = fopen(PARTITION_FILENAME, "wb+");
  format_fat_area(fp);
  format_data_area(fp);
  fclose(fp);
}

void format_directory_file(FILE* fp) {
  const DirectoryFile directory_file = {
    .capacity = ROOT_DIRECTORY_MAX_FILES,
    .length = 0,
  };
  unsigned char buffer[DIRECTORY_ENTRY_SIZE_IN_BYTES * ROOT_DIRECTORY_MAX_FILES + 3 * 2] = { 0 };
  serialize_directory_file(&directory_file, buffer);
  fwrite(buffer, sizeof buffer, 1, fp);
}

void format_directory() {
  FILE* fp = fopen(DIRECTORY_FILENAME, "wb+");
  format_directory_file(fp);
  fclose(fp);
}