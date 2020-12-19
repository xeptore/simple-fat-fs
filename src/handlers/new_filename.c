#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "logger.h"
#include "macros.h"
#include "string.h"
#include <stdio.h>


int handle_new_filename(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const char* destination_file_name
) {
  if (directory_is_full(directory)) {
    fatal("Directory does not have any space to store new file.");
    return 2;
  }

  if (filename_exists_in_directory(directory, destination_file_name)) {
    fatal("Filename already exists.");
    return 1;
  }

  FatTableEntry empty_entries[10] = { 0 };
  if (!try_get_ten_empty_entries(fat_table, empty_entries)) {
    fatal("No empty space left in FAT table.");
    return 1;
  }
  update_fat_entires(fat_table, empty_entries);
  DirectoryEntry directory_entry = {
    .first_fat_table_record = empty_entries[0]
  };
  strcpy(directory_entry.filename, destination_file_name);
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);
  persist_fat_table(fat_table);

  return 0;
}
