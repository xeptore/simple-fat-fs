#include "constants.h"
#include "directory.h"
#include "data_area.h"
#include "fat.h"
#include "logger.h"
#include "macros.h"
#include "string.h"
#include "utilities.h"
#include <stdio.h>

void get_filename(char* output) {
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

int handle_save_file(DirectoryFile* directory, FatTableEntry* fat_table) {
  FILE* data_file = open_data_file();

  char filename[] = INITIALIZE(MAX_FILENAME_LENGTH + 1, '\000');
  get_filename(filename);
  if (!filename_exists_in_directory(directory, filename)) {
    char error_message[52 + strlen(filename)];
    sprintf(error_message, "Destination filename '%s' does not exist in directory.", filename);
    fatal(error_message);
    return 1;
  }

  char source_file_path[] = INITIALIZE(MAXIMUM_SOURCE_FILE_PATH_LENGTH + 1, '\000');
  get_source_file_path(source_file_path);
  FILE* source_file = open_source_file(source_file_path);

  const FatTableEntry first_file_entry = get_file_fat_first_entry(directory, filename);
  const FileFatEntries file_fat_entries = read_file_fat_entries_chain(first_file_entry, fat_table, filename);
  save_source_file(source_file, data_file, file_fat_entries.entries);

  fclose(source_file);
  fclose(data_file);

  return 0;
}
