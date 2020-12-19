#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "formatter.h"
#include "handlers.h"
#include "logger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* USAGE_MESSAGE = "\
  Usage:\
\n    simple-fat <command> [command-specific-options]+\
\n  Commands:\
\n    partition        = Creates partition.bin and directory.bin files in current working directory. Overwrites if already exists.\
\n\
\n    reserve          = Reserves 10 blocks for <destination-file-name> in FAT table.\
\n      -d, --destination-file-name <destination-file-name>\
\n\
\n    store-reserved   = Stores <source-file-absolute-path> in file system. <destination-file-name> file must already exists, otherwise error occurs.\
\n      -d, --destination-file-name <destination-file-name>\
\n      -s, --source-file-path <source-file-absolute-path>\
\n\
\n    store            = Executes `reserve` and `store-reserved` in one command.\
\n      -d, --destination-file-name <destination-file-name>\
\n      -s, --source-file-path <source-file-absolute-path>\
\n\
\n    restore          = Restores <source-file-name> from file system and copies its data to <destination-file-absolute-path> on host machine's file system.\
\n      -d, --destination-file-path <destination-file-absolute-path>\
\n      -s, --source-file-name <source-file-name>\
";

void print_usage_message_and_exit() {
  fprintf(stderr, "%s\n", USAGE_MESSAGE);
  exit(1);
}

bool validate_command(char* cmd) {
  if (strcmp("partition", cmd) == 0 ||
    strcmp("reserve", cmd) == 0 ||
    strcmp("store-reserved", cmd) == 0 ||
    strcmp("store", cmd) == 0 ||
    strcmp("restore", cmd) == 0) {
    return true;
  }
  return false;
}

bool validate_reserve_command_args(unsigned int argc, char* argv[]) {
  if (argc < 4) {
    return false;
  }
  const char* option = argv[2];
  if (strcmp(option, "-d") != 0 &&
    strcmp(option, "--destination-file-name") != 0) {
    return false;
  }
  const char* value = argv[3];
  if (strlen(value) > MAX_FILENAME_LENGTH) {
    return false;
  }
  return true;
}

bool validate_store_reserve_command_args(unsigned int argc, char* argv[]) {
  if (argc < 6) {
    return false;
  }
  const char* d_option = argv[2];
  if (strcmp(d_option, "-d") != 0 &&
    strcmp(d_option, "--destination-file-name") != 0) {
    return false;
  }
  const char* d_value = argv[3];
  if (strlen(d_value) > MAX_FILENAME_LENGTH) {
    return false;
  }
  const char* s_option = argv[4];
  if (strcmp(s_option, "-s") != 0 &&
    strcmp(s_option, "--source-file-path") != 0) {
    return false;
  }
  const char* s_value = argv[5];
  const unsigned short int MAXIMUM_SOURCE_FILE_PATH_LENGTH = 100U;
  if (strlen(s_value) > MAXIMUM_SOURCE_FILE_PATH_LENGTH) {
    return false;
  }
  return true;
}

bool validate_store_command_args(unsigned int argc, char* argv[]) {
  if (argc < 6) {
    return false;
  }
  const char* d_option = argv[2];
  if (strcmp(d_option, "-d") != 0 &&
    strcmp(d_option, "--destination-file-name") != 0) {
    return false;
  }
  const char* d_value = argv[3];
  if (strlen(d_value) > MAX_FILENAME_LENGTH) {
    return false;
  }
  const char* s_option = argv[4];
  if (strcmp(s_option, "-s") != 0 &&
    strcmp(s_option, "--source-file-path") != 0) {
    return false;
  }
  const char* s_value = argv[5];
  const unsigned short int MAXIMUM_SOURCE_FILE_PATH_LENGTH = 100U;
  if (strlen(s_value) > MAXIMUM_SOURCE_FILE_PATH_LENGTH) {
    return false;
  }
  return true;
}

bool validate_restore_command_args(unsigned int argc, char* argv[]) {
  if (argc < 6) {
    return false;
  }
  const char* d_option = argv[2];
  if (strcmp(d_option, "-d") != 0 &&
    strcmp(d_option, "--destination-file-path") != 0) {
    return false;
  }
  const char* d_value = argv[3];
  const unsigned short int MAXIMUM_DESTINATION_FILE_PATH_LENGTH = 100U;
  if (strlen(d_value) > MAXIMUM_DESTINATION_FILE_PATH_LENGTH) {
    return false;
  }
  const char* s_option = argv[4];
  if (strcmp(s_option, "-s") != 0 &&
    strcmp(s_option, "--source-file-name") != 0) {
    return false;
  }
  const char* s_value = argv[5];
  if (strlen(s_value) > MAX_FILENAME_LENGTH) {
    return false;
  }
  return true;
}

typedef enum Command {
  Partition,
  Reserve,
  StoreReserved,
  Store,
  Restore,
} Command;

enum Command parse_command(char* cmd) {
  if (strcmp("partition", cmd) == 0) {
    return Partition;
  }
  if (strcmp("reserve", cmd) == 0) {
    return Reserve;
  }
  if (strcmp("store-reserved", cmd) == 0) {
    return StoreReserved;
  }
  if (strcmp("store", cmd) == 0) {
    return Store;
  }
  if (strcmp("restore", cmd) == 0) {
    return Restore;
  }
  return Partition;
}

char* parse_reserve_arg(char** argv) {
  const unsigned int argument_length = strlen(argv[3]);
  char* destination_file_name = malloc(argument_length);
  strcpy(destination_file_name, argv[3]);
  return destination_file_name;
}

StoreReservedArgs parse_store_reserve_arg(char** argv) {
  StoreReservedArgs args;
  strcpy(args.source_file_path, argv[5]);
  strcpy(args.destination_file_name, argv[3]);
  return args;
}

StoreArgs parse_store_arg(char** argv) {
  StoreArgs args;
  strcpy(args.source_file_path, argv[5]);
  strcpy(args.destination_file_name, argv[3]);
  return args;
}

RestoreArgs parse_restore_arg(char** argv) {
  RestoreArgs args;
  strcpy(args.source_file_name, argv[5]);
  strcpy(args.destination_file_path, argv[3]);
  return args;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    print_usage_message_and_exit();
  }

  if (!validate_command(argv[1])) {
    print_usage_message_and_exit();
  }
  const Command command = parse_command(argv[1]);

  if (command == Partition) {
    format_partition();
    format_directory();
    return 0;
  }

  FatTableEntry fat_table[FAT_ENTRIES] = { 0 };
  load_fat_table(fat_table);

  DirectoryFile directory_file = load_directory_file();

  switch (command) {
  case Reserve: {
    if (!validate_reserve_command_args(argc, argv)) {
      print_usage_message_and_exit();
    }
    char* destination_file_name = parse_reserve_arg(argv);
    const int result = handle_reserve(&directory_file, fat_table, destination_file_name);
    free(destination_file_name);
    return result;
  }
  case StoreReserved: {
    if (!validate_store_reserve_command_args(argc, argv)) {
      print_usage_message_and_exit();
    }
    StoreReservedArgs args = parse_store_reserve_arg(argv);
    return handle_store_reserved(&directory_file, fat_table, &args);
  }
  case Store: {
    if (!validate_store_command_args(argc, argv)) {
      print_usage_message_and_exit();
    }
    StoreArgs args = parse_store_arg(argv);
    return handle_store(&directory_file, fat_table, &args);
  }
  case Restore: {
    if (!validate_restore_command_args(argc, argv)) {
      print_usage_message_and_exit();
    }
    const RestoreArgs args = parse_restore_arg(argv);
    return handle_restore(&directory_file, fat_table, &args);
  }
  default:
    fprintf(stderr, "How did you reach here?!");
    return 1;
  }
}
