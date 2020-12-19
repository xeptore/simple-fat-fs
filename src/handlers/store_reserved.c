#include "constants.h"
#include "directory.h"
#include "data_area.h"
#include "fat.h"
#include "logger.h"
#include "macros.h"
#include "string.h"
#include "utilities.h"
#include "handlers.h"
#include <stdio.h>

int handle_store_reserved(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  StoreReservedArgs* args
) {
  FILE* data_file = open_data_file();

  if (!filename_exists_in_directory(directory, args->destination_file_name)) {
    char error_message[52 + strlen(args->destination_file_name)];
    sprintf(
      error_message,
      "Destination filename '%s' does not exist in directory.",
      args->destination_file_name
    );
    fatal(error_message);
    return 1;
  }

  FILE* source_file = open_source_file(args->source_file_path);

  const FatTableEntry first_file_entry = get_file_fat_first_entry(
    directory,
    args->destination_file_name
  );
  const FileFatEntries file_fat_entries = read_file_fat_entries_chain(
    first_file_entry,
    fat_table,
    args->destination_file_name
  );
  save_source_file(source_file, data_file, file_fat_entries.entries);

  fclose(source_file);
  fclose(data_file);

  return 0;
}
