#include "fat.h"
#include "constants.h"
#include "logger.h"
#include <stdio.h>

FatTableEntry deserialize_fat_entry(const unsigned char* serialized_entry) {
  return ((serialized_entry[0] << 0)) +
         ((serialized_entry[1] << 8)) +
         ((serialized_entry[2] << 16));
}

void deserialize_fat_table(unsigned char *serialized, FatTableEntry *fat_table) {
  for (size_t i = 0; i < FAT_ENTRIES; i++)  {
    fat_table[i] = deserialize_fat_entry(&serialized[i * 3]);
  }
}

void serialize_fat_entry(const FatTableEntry entry, unsigned char* output) {
  output[0] = (entry >> 0) % 256;
  output[1] = (entry >> 8) % 256;
  output[2] = (entry >> 16) % 256;
}

void serialize_fat_table(const FatTableEntry *fat_table, unsigned char *output) {
  for (size_t i = 0; i < FAT_ENTRIES; i++)  {
    serialize_fat_entry(fat_table[i], &output[3 * i]);
  }
}

void load_fat_table(FatTableEntry *fat_table) {
  FILE *fp = fopen(PARTITION_FILENAME, "rb");
  char buffer[FAT_ENTRIES] = {0};
  fread(buffer, sizeof buffer, 1, fp);
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
