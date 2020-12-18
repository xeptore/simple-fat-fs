#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "formatter.h"
#include "handlers.h"
#include "logger.h"
#include <stdbool.h>
#include <stdlib.h>

int main() {
  // FIXME: check whether partition exists or not.
  // if does not exist, create it first.

  // format_partition();
  // format_directory();

  FatTableEntry fat_table[FAT_ENTRIES] = {0};
  load_fat_table(fat_table);

  DirectoryFile directory_file = load_directory_file();

  return handle_new_filename(&directory_file, fat_table);
  return handle_save_file(&directory_file, fat_table);
}
