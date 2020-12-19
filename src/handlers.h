#include "directory.h"
#include "fat.h"

int handle_new_filename(DirectoryFile* directory, FatTableEntry* fat_table);
int handle_save_file(DirectoryFile* directory, FatTableEntry* fat_table);
int handle_save_new_file(DirectoryFile* directory, FatTableEntry* fat_table);
