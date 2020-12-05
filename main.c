#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "formatter.h"
#include "handlers.h"
#include "logger.h"
#include <stdbool.h>
#include <stdlib.h>

#ifdef APP_ENV_TEST

void __test__update_fat_entires() {
  FatTableEntry fat_table[16] = {0};
  int empty_entries[10] = {0, 2, 4, 6, 7, 8, 9, 10, 13, 14};
  update_fat_entires(fat_table, empty_entries);
  if (!(fat_table[0] == 2 && fat_table[2] == 4 && fat_table[4] == 6 &&
        fat_table[6] == 7 && fat_table[7] == 8 && fat_table[8] == 9 &&
        fat_table[9] == 10 && fat_table[10] == 13 && fat_table[13] == 14 &&
        fat_table[14] == FAT_END_OF_FILE_ENTRY)) {
    printf("Test failed.");
    return;
  }
  printf("Works fine!");
}

#endif

int main() {
  // FIXME: check whether partition exists or not.
  // if does not exist, create it first.

  // format_partition();
  // format_directory();

  FatTableEntry fat_table[FAT_ENTRIES] = {0};
  load_fat_table(fat_table);

  DirectoryFile directory_file = load_directory_file();
  return exec_save_filename(&directory_file, fat_table);
}
