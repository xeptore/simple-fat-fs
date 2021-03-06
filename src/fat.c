#include "fat.h"
#include "constants.h"
#include "macros.h"
#include "logger.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

FatTableEntry deserialize_fat_entry(const unsigned char* serialized_entry) {
  return
    (serialized_entry[0] << 0) +
    (serialized_entry[1] << 8) +
    (serialized_entry[2] << 16);
}

void deserialize_fat_table(unsigned char* serialized, FatTableEntry* fat_table) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    fat_table[i] = deserialize_fat_entry(&serialized[i * 3]);
  }
}

void serialize_fat_entry(const FatTableEntry entry, unsigned char* output) {
  output[0] = (entry >> 0) % 256;
  output[1] = (entry >> 8) % 256;
  output[2] = (entry >> 16) % 256;
}

void serialize_fat_table(const FatTableEntry* fat_table, unsigned char* output) {
  for (size_t i = 0; i < FAT_ENTRIES; i++) {
    serialize_fat_entry(fat_table[i], &output[3 * i]);
  }
}

void load_fat_table(FatTableEntry* fat_table) {
  FILE* fp = fopen(PARTITION_FILENAME, "rb");
  if (fp == NULL) {
    fprintf(
      stderr,
      "Error opening partition file. Try partitioning again.\n"
    );
    exit(errno);
  }
  unsigned char buffer[] = INITIALIZE(FAT_ENTRIES * 3, '\000');
  fread(buffer, sizeof buffer, 1, fp);
  fclose(fp);
  deserialize_fat_table(buffer, fat_table);
}

void persist_fat_table(const FatTableEntry* fat_table) {
  FILE* fp = fopen(PARTITION_FILENAME, "r+b");
  if (fp == NULL) {
    fprintf(
      stderr,
      "Error opening partition file. Try partitioning again.\n"
    );
    exit(errno);
  }
  unsigned char buffer[] = INITIALIZE(FAT_ENTRIES * 3, '\000');
  serialize_fat_table(fat_table, buffer);
  fseek(fp, 0, SEEK_SET);
  fwrite(buffer, sizeof buffer, 1, fp);
  fclose(fp);
}

void update_fat_entires(
  FatTableEntry* fat_table,
  const FatTableEntry* empty_entries
) {
  for (size_t i = 0; i < 10; i++) {
    fat_table[empty_entries[i]] = empty_entries[i + 1];
  }
  fat_table[empty_entries[9]] = FAT_END_OF_FILE_ENTRY;
}

bool try_get_ten_empty_entries(
  const FatTableEntry* fat_table,
  FatTableEntry* empty_entries
) {
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
    return false;
  }
  return true;
}

FileFatEntries read_file_fat_entries_chain(
  const FatTableEntry first_entry,
  const FatTableEntry* fat_table,
  const char* filename
) {
  FileFatEntries file_fat_entries;
  file_fat_entries.entries[0] = first_entry;

  for (size_t i = 1; i < 10; i++) {
    file_fat_entries.entries[i] = fat_table[file_fat_entries.entries[i - 1]];
  }

  return file_fat_entries;
}
