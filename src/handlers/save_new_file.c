#include "constants.h"
#include "directory.h"
#include "data_area.h"
#include "macros.h"
#include "fat.h"
#include "utilities.h"
#include <string.h>

void get_destination_filename(char* output) {
  printf(
    "Enter destination filename (%d-characters long, including extension): ",
    MAX_FILENAME_LENGTH
  );
  char line[] = INITIALIZE(MAX_FILENAME_LENGTH + 1, '\000');
  scanf("%[^\n]", line);
  strcpy(output, line);
}

void get_source_file_path(char* output) {
  getchar();
  // FIXME: clear input buffer
  printf(
    "Enter source file path (%d-characters long, including extension): ",
    MAXIMUM_SOURCE_FILE_PATH_LENGTH
  );
  char line[] = INITIALIZE(MAXIMUM_SOURCE_FILE_PATH_LENGTH + 1, '\000');
  scanf("%[^\n]", line);
  strcpy(output, line);
}

int handle_save_new_file(DirectoryFile *directory, FatTableEntry *fat_table) {
  if (directory_is_full(directory)) {
    fatal("Directory does not have any space to store new file.");
    return 2;
  }

  char destination_filename[] = INITIALIZE(MAX_FILENAME_LENGTH + 1, '\000');
  get_destination_filename(destination_filename);
  if (filename_exists_in_directory(directory, destination_filename)) {
    char error_message[50 + strlen(destination_filename)];
    sprintf(
      error_message,
      "Destination filename '%s' already exists in directory.",
      destination_filename
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
  strcpy(directory_entry.filename, destination_filename);
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);

  char source_file_path[] = INITIALIZE(MAXIMUM_SOURCE_FILE_PATH_LENGTH + 1, '\000');
  get_source_file_path(source_file_path);
  FILE *source_file = open_source_file(source_file_path);

  FILE *data_file = open_data_file();
  save_source_file(source_file, data_file, empty_entries);

  fclose(source_file);
  fclose(data_file);

  return 0;
}
