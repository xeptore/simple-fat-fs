#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "logger.h"

void get_filename(char *output) {
  printf(
    "Enter filename (%d-characters long, including extension): ",
    MAX_FILENAME_LENGTH
  );
  scanf("%s", output);
  // FIXME: what if user entered filename more than 11 characters?
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
    .filename = filename,
    .first_fat_table_record = empty_entries[0]
  };
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);
  persist_fat_table(fat_table);

  return 0;
}