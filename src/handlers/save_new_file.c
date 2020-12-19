#include "constants.h"
#include "directory.h"
#include "data_area.h"
#include "macros.h"
#include "fat.h"
#include "utilities.h"
#include "handlers.h"
#include <string.h>

int handle_save_new_file(
  DirectoryFile *directory,
  FatTableEntry *fat_table,
  StoreArgs* args
) {
  if (directory_is_full(directory)) {
    fatal("Directory does not have any space to store new file.");
    return 2;
  }

  if (filename_exists_in_directory(directory, args->destination_file_name)) {
    char error_message[50 + strlen(args->destination_file_name)];
    sprintf(
      error_message,
      "Destination filename '%s' already exists in directory.",
      args->destination_file_name
    );
    fatal(error_message);
    return 1;
  }

  FatTableEntry empty_entries[10] = {0};
  if (!try_get_ten_empty_entries(fat_table, empty_entries)) {
    fatal("No empty space left in FAT table.");
    return 1;
  }
  update_fat_entires(fat_table, empty_entries);
  persist_fat_table(fat_table);

  DirectoryEntry directory_entry = {.first_fat_table_record = empty_entries[0]};
  strcpy(directory_entry.filename, args->destination_file_name);
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);

  FILE *source_file = open_source_file(args->source_file_path);

  FILE *data_file = open_data_file();
  save_source_file(source_file, data_file, empty_entries);

  fclose(source_file);
  fclose(data_file);

  return 0;
}
