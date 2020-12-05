#include <math.h>
#include <stdbool.h>
#include <stdio.h>

const int BLOCK_SIZE_IN_BYTES = 1024;

const int FAT_ENTRY_SIZE_IN_BITS = 20;

const unsigned short int ROOT_DIRECTORY_MAX_FILES = 32;

const bool IS_TRUE = true;

const int FAT_ENTRIES = 1048576;                   // 2 ^ 20
const int FAT_END_OF_FILE_ENTRY = FAT_ENTRIES + 1; // 2 ^ 20 + 1
const int FAT_EMPTY_ENTRY = -1;

const unsigned int DIRECTORY_ENTRY_SIZE_IN_BYTES = 14;

struct DirectoryEntry {
  char *filename;
  int first_fat_table_record;
};

struct DirectoryFile {
  size_t capacity;
  size_t length;
  struct DirectoryEntry directory_entry[ROOT_DIRECTORY_MAX_FILES];
};

void serialize_directory_file(struct DirectoryFile directory);

struct DirectoryFile *
deserialize_directory_file(char *serialized_directory_file);

typedef int FatTable;

void format_fat_area(FILE *fp) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    unsigned char buffer[3] = {0};
    fwrite(buffer, sizeof buffer, 1, fp);
  }
}

void format_data_area(FILE *fp) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    unsigned char buffer[BLOCK_SIZE_IN_BYTES] = {0};
    fwrite(buffer, sizeof buffer, 1, fp);
  }
}

/**
 * Format partition on disk. Creates `partition.io` on disk.
 */
void format() {
  FILE *fp = fopen("./partition.io", "wb+");
  format_fat_area(fp);
  format_data_area(fp);
  fclose(fp);
}

/**
 * Loads FAT table from partition on disk into memory.
 */
FatTable *load_fat_table() {
  FILE *fp = fopen("./partition.io", "rb");
  FatTable loaded_fat_table_buffer[FAT_ENTRIES];
  fread(loaded_fat_table_buffer, sizeof loaded_fat_table_buffer, 1, fp);
  fclose(fp);
  return loaded_fat_table_buffer;
}

struct DirectoryFile *load_directory_file() {
  FILE *fp = fopen("./direcotry.dir", "rb");
  char buffer[ROOT_DIRECTORY_MAX_FILES * DIRECTORY_ENTRY_SIZE_IN_BYTES];
  fread(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  return deserialize_directory_file(buffer);
}

/**
 * Persists fat table onto partition on disk.
 */
void persist_fat_table(FatTable *table) {
  FILE *fp = fopen("./partition.io", "wb+");
  fwrite(table, FAT_ENTRIES, 1, fp);
  fclose(fp);
}

void update_fat_entires(FatTable *fat_table, int *empty_entries) {
  for (size_t i = 0; i < 10; i++) {
    fat_table[empty_entries[i]] = empty_entries[i + 1];
  }
  fat_table[empty_entries[9]] = FAT_END_OF_FILE_ENTRY;
}

int exec_save_filename(struct DirectoryFile *directory, FatTable *fat_table);

bool filename_exists_in_directory(struct DirectoryFile *directory,
                                  int *filename) {
  for (size_t i = 0; i < ROOT_DIRECTORY_MAX_FILES; i++) {
    if (directory->directory_entry[i].filename == filename) {
      return true;
    }
  }

  return false;
}

char *get_filename() {
  printf("Enter filename (8-characters long, including extension): ");
  char filename[11];
  scanf("%s", &filename);
  // FIXME: what if user entered filename more than 11 characters?

  return filename;
}

char *get_ten_empty_entries(FatTable *fat_table) {
  unsigned int empty_entries[10];
  size_t empty_entries_index = 0;
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    if (fat_table[i] == FAT_EMPTY_ENTRY) {
      empty_entries[empty_entries_index++] = i;
      if (empty_entries_index == 10) {
        break;
      }
    }
  }
  if (empty_entries_index != 10) {
    return -1;
  }
  return empty_entries;
}

void insert_directory_entry(struct DirectoryFile *directory_file,
                            struct DirectoryEntry *directory_entry) {
  directory_file->directory_entry[directory_file->length++] = *directory_entry;
}

bool directory_is_full(struct DirectoryFile *directory_file) {
  return directory_file->length == directory_file->capacity;
}

int main() {
  // FIXME: check whether partition exists or not.
  // if does not exist, create it first.

  FatTable fat_table[FAT_ENTRIES] = load_fat_table();
  struct DirectoryFile *directory_file = load_directory_file();
  return exec_save_filename(directory_file, fat_table);
}

int exec_save_filename(struct DirectoryFile *directory, FatTable *fat_table) {
  if (directory_is_full(directory)) {
    printf("Directory does not have any space to store new file.\n");
    printf("Exiting...");
    return 2;
  }

  const char *filename = read_filename();
  if (filename_exists_in_directory(directory, filename)) {
    printf("Filename already exists.\n");
    printf("Exiting...");
    return 1;
  }

  const char *empty_entries = get_ten_empty_entries(fat_table);
  // TODO: handle the case of no empty entry...
  update_fat_entires(fat_table, empty_entries);
  const struct DirectoryEntry directory_entry = {
      .filename = filename, .first_fat_table_record = empty_entries[0]};
  insert_directory_entry(directory, &directory_entry);
  persist_directory(directory);
  persist_fat_table(fat_table);
}

void __test__update_fat_entires() {
  const FatTable fat_table[16] = {0};
  const int empty_entries[10] = {0, 2, 4, 6, 7, 8, 9, 10, 13, 14};
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
