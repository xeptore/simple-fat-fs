#pragma once
#include <stdbool.h>

#define BLOCK_SIZE_IN_BYTES 1024
#define MAX_FILENAME_LENGTH 20
#define FAT_ENTRY_SIZE_IN_BITS 20
#define FAT_ENTRIES 1048576           // 2 ^ 20
#define FAT_END_OF_FILE_ENTRY 1048577 // FAT_ENTRIES + 1
#define FAT_EMPTY_ENTRY -1
// 20 bytes for filename
// 1 byte for filename null terminator
// 3 bytes for fat entry index
#define DIRECTORY_ENTRY_SIZE_IN_BYTES 24
#define ROOT_DIRECTORY_MAX_FILES 32
#define PARTITION_FILENAME "./partition.io"
#define DIRECTORY_FILENAME "./directory.dir"
