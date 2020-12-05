#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "formatter.h"
#include "logger.h"
#include <stdbool.h>
#include <stdlib.h>

int exec_save_filename(DirectoryFile *directory, FatTableEntry *fat_table);

void get_filename(char *output) {
  printf("Enter filename (%d-characters long, including extension): ",
         MAX_FILENAME_LENGTH);
  scanf("%s", output);
  // FIXME: what if user entered filename more than 11 characters?
}

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
  // DirectoryFile directory_file = load_directory_file();
  // return exec_save_filename(&directory_file, fat_table);
}

int exec_save_filename(DirectoryFile *directory, FatTableEntry *fat_table) {
  if (directory_is_full(directory)) {
    fatal("Directory does not have any space to store new file.");
    return 2;
  }

  char filename[MAX_FILENAME_LENGTH] = {0};
  get_filename(filename);
  if (filename_exists_in_directory(directory, filename)) {
    fatal("Filename already exists.");
    return 1;
  }

  FatTableEntry empty_entries[10] = {0};
  if (!try_get_ten_empty_entries(fat_table, empty_entries)) {
    fatal("No empty space left in FAT table.");
    return 1;
  }
  update_fat_entires(fat_table, empty_entries);
  const DirectoryEntry directory_entry = {
      .filename = filename, .first_fat_table_record = empty_entries[0]};
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);
  persist_fat_table(fat_table);

  return 0;
}
