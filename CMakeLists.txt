cmake_minimum_required(VERSION 3.19)

# sets compiler
SET (CMAKE_C_COMPILER /usr/bin/clang-11)

# debugging build configuration
set (CMAKE_BUILD_TYPE Debug)

project (simple-fat)
add_executable (simple-fat main.c src/constants.h src/macros.h)

include_directories (src)

add_executable (_test_fat src/fat_test.c)
target_link_libraries (_test_fat fat -lcunit)

# adds libraries as the units of compilation
add_library (directory src/directory.h src/directory.c)
target_link_libraries (simple-fat directory)

add_library (handlers src/handlers.h src/handlers/new_filename.c)
target_link_libraries (simple-fat handlers)

add_library (fat src/fat.h src/fat.c)
target_link_libraries (simple-fat fat)

add_library (formatter src/formatter.h src/formatter.c)
target_link_libraries (simple-fat formatter)

add_library (logger src/logger.h src/logger.c)
target_link_libraries (simple-fat logger)
