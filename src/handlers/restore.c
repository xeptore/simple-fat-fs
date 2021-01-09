#include "fat.h"
#include "directory.h"
#include "data_area.h"
#include "macros.h"
#include "handlers.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

FILE* open_destination_file(const char* destination_file_path) {
  FILE* file = fopen(destination_file_path, "w+b");
  if (file == NULL) {
    sprintf(
      stderr,
      "Error opening file '%s': %s\n",
      destination_file_path,
      strerror(errno)
    );
    exit(errno);
  }

  return file;
}

void restore_file(
  FILE* data_file,
  const FatTableEntry* fat_entries,
  FILE* destination_file
) {
  for (size_t i = 0; i < 10; i++) {
    unsigned char block_buffer[] = INITIALIZE(BLOCK_SIZE_IN_BYTES, '\000');
    read_block_n(data_file, fat_entries[i], block_buffer);
    write_block_n(destination_file, i, block_buffer);
  }
}

int handle_restore(
  DirectoryFile* directory,
  FatTableEntry* fat_table,
  const RestoreArgs* args
) {
  if (!filename_exists_in_directory(directory, args->source_file_name)) {
    const char error_message_template[] = "Source file name '%s' does not exist in directory.";
    char error_message[strlen(error_message_template) - 2 + strlen(args->source_file_name)];
    sprintf(
      error_message,
      error_message_template,
      args->source_file_name
    );
    fatal(error_message);
    return 1;
  }

  const FatTableEntry first_file_entry = get_file_fat_first_entry(
    directory,
    args->source_file_name
  );
  const FileFatEntries file_fat_entries = read_file_fat_entries_chain(
    first_file_entry,
    fat_table,
    args->source_file_name
  );

  FILE* destination_file = open_destination_file(args->destination_file_path);

  FILE* data_file = open_data_file();
  restore_file(data_file, file_fat_entries.entries, destination_file);

  fclose(data_file);
  fclose(destination_file);

  return 0;
}