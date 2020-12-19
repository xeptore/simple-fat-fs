#include "fat.h"
#include "directory.h"
#include "data_area.h"
#include "macros.h"
#include <string.h>

const unsigned short int MAXIMUM_DESTINATION_FILE_PATH_LENGTH = 100U;

void get_destination_file_path(char* output) {
  getchar();
  printf(
    "Enter destination file path (%d-characters long, including extension): ",
    MAXIMUM_DESTINATION_FILE_PATH_LENGTH
  );
  char line[] = INITIALIZE(MAXIMUM_DESTINATION_FILE_PATH_LENGTH + 1, '\000');
  scanf("%[^\n]", line);
  strcpy(output, line);
}

void get_source_filename(char* output) {
  printf(
    "Enter source file name (%d-characters long, including extension): ",
    MAX_FILENAME_LENGTH
  );
  char line[] = INITIALIZE(MAX_FILENAME_LENGTH + 1, '\000');
  scanf("%[^\n]", line);
  strcpy(output, line);
}

FILE* open_destination_file(const char* destination_file_path) {
  FILE* file = fopen(destination_file_path, "w+b");
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

int handle_restore_file(DirectoryFile* directory, FatTableEntry* fat_table) {
  char source_filename[] = INITIALIZE(MAX_FILENAME_LENGTH + 1, '\000');
  get_source_filename(source_filename);
  if (!filename_exists_in_directory(directory, source_filename)) {
    const char error_message_template[] = "Source file name '%s' does not exist in directory.";
    char error_message[strlen(error_message_template) - 2 + strlen(source_filename)];
    sprintf(
      error_message,
      error_message_template,
      source_filename
    );
    fatal(error_message);
    return 1;
  }

  const FatTableEntry first_file_entry = get_file_fat_first_entry(directory, source_filename);
  const FileFatEntries file_fat_entries = read_file_fat_entries_chain(first_file_entry, fat_table, source_filename);

  char destination_file_path[] = INITIALIZE(MAXIMUM_DESTINATION_FILE_PATH_LENGTH + 1, '\000');
  get_destination_file_path(destination_file_path);
  FILE* destination_file = open_destination_file(destination_file_path);

  FILE* data_file = open_data_file();
  restore_file(data_file, file_fat_entries.entries, destination_file);

  fclose(data_file);
  fclose(destination_file);

  return 0;
}