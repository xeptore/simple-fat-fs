#pragma once
#include <stdbool.h>
#include "logger.h"

typedef int FatTableEntry;

void serialize_fat_entry(const FatTableEntry entry, unsigned char* output);

FatTableEntry deserialize_fat_entry(const unsigned char* serialized_entry);

// Loads FAT table from partition file on disk into `fat_table`.
void load_fat_table(FatTableEntry *fat_table);

// Persists fat table onto partition on disk.
void persist_fat_table(const FatTableEntry *fat_table);

// Appplies `empty_entires` chain to `fat_table`.
void update_fat_entires(
  FatTableEntry *fat_table,
  const FatTableEntry *empty_entries
);

// Tries to find an chain of empty entries in the given `fat_table`
// and fills `empty_entries` with the chain.
// Returns true if succeeded, false otherwise.
bool try_get_ten_empty_entries(
  const FatTableEntry *fat_table,
  FatTableEntry *empty_entries
);
