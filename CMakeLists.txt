cmake_minimum_required(VERSION 3.19)

# sets compiler
SET (CMAKE_C_COMPILER /usr/bin/clang-11)

# debugging build configuration
set (CMAKE_BUILD_TYPE Debug)

project (simple-fat)
add_executable (simple-fat main.c src/constants.h src/macros.h)

include_directories (src)

# add fat library test executable
add_executable (_test_fat src/fat_test.c)
target_link_libraries (_test_fat fat -lcunit)

# add directory library test executable
add_executable (_test_directory src/directory_test.c)
target_link_libraries (_test_directory directory fat -lcunit)

# adds libraries as the units of compilation
add_library (data-area src/data_area.h src/data_area.c)
target_link_libraries (simple-fat data-area)

add_library (handlers
  src/handlers.h
  src/handlers/utilities.h
  src/handlers/utilities.c
  src/handlers/reserve.c
  src/handlers/store_reserved.c
  src/handlers/store.c
  src/handlers/restore.c
)
target_link_libraries (simple-fat handlers data-area)

add_library (fat src/fat.h src/fat.c)
target_link_libraries (simple-fat fat)

add_library (directory src/directory.h src/directory.c)
target_link_libraries (directory fat)
target_link_libraries (simple-fat directory)

add_library (formatter src/formatter.h src/formatter.c)
target_link_libraries (formatter directory)
target_link_libraries (simple-fat formatter)

add_library (logger src/logger.h src/logger.c)
target_link_libraries (simple-fat logger)
