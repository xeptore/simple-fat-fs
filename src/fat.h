#pragma once
#include <stdbool.h>
#include "logger.h"
#include "types.h"

void serialize_fat_entry(const FatTableEntry entry, unsigned char* output);

FatTableEntry deserialize_fat_entry(const unsigned char* serialized_entry);

// Loads FAT table from partition file on disk into `fat_table`.
void load_fat_table(FatTableEntry* fat_table);

// Persists fat table onto partition on disk.
void persist_fat_table(const FatTableEntry* fat_table);

// Applies `empty_entires` chain to `fat_table`.
void update_fat_entires(
  FatTableEntry* fat_table,
  const FatTableEntry* empty_entries
);

// Tries to find an chain of empty entries in the given `fat_table`
// and fills `empty_entries` with the chain.
// Returns true if succeeded, false otherwise.
bool try_get_ten_empty_entries(
  const FatTableEntry* fat_table,
  FatTableEntry* empty_entries
);

// A container for file FAT entries array
// to make returning the array copy-able.
typedef struct {
  FatTableEntry entries[10];
} FileFatEntries;

// Giving first entry in chain, it finds file FAT entries chain and returns them.
FileFatEntries read_file_fat_entries_chain(
  const FatTableEntry first_entry,
  const FatTableEntry* fat_table,
  const char* filename
);
