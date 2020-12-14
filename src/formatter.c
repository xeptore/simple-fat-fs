#include <stdio.h>
#include "constants.h"
#include "formatter.h"

void format_fat_area(FILE *fp) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    unsigned char buffer[3] = {0};
    fwrite(buffer, sizeof buffer, 1, fp);
  }
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