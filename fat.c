#include "fat.h"
#include "constants.h"
#include <stdio.h>

void deserialize_fat_table(char *serialized, FatTableEntry *fat_table) {
  // TODO: deserialize and map it to `fat_table`.
}

void serialize_fat_table(const FatTableEntry *fat_table, char *output) {
  // TODO: serialize and map it to `output`.
}

void load_fat_table(FatTableEntry *fat_table) {
  FILE *fp = fopen(PARTITION_FILENAME, "rb");
  char buffer[FAT_ENTRIES] = {0};
  fread(fat_table, sizeof buffer, 1, fp);
  fclose(fp);
  deserialize_fat_table(buffer, fat_table);
}

void persist_fat_table(const FatTableEntry *fat_table) {
  FILE *fp = fopen(PARTITION_FILENAME, "wb+");
  char buffer[FAT_ENTRIES] = {0};
  serialize_fat_table(fat_table, buffer);
  fwrite(buffer, sizeof buffer, 1, fp);
  fclose(fp);
}

void update_fat_entires(
  FatTableEntry *fat_table,
  const int *empty_entries
) {
  for (size_t i = 0; i < 10; i++) {
    fat_table[empty_entries[i]] = empty_entries[i + 1];
  }
  fat_table[empty_entries[9]] = FAT_END_OF_FILE_ENTRY;
}

bool try_get_ten_empty_entries(
  const FatTableEntry *fat_table,
  FatTableEntry *empty_entries
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
