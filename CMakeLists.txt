cmake_minimum_required(VERSION 3.19)

# sets compiler
SET(CMAKE_C_COMPILER /usr/bin/clang-11)

# debugging build configuration
set (CMAKE_BUILD_TYPE Debug)

project(simple-fat)
add_executable (simple-fat main.c constants.h)

include_directories (handlers)
include_directories(${PROJECT_SOURCE_DIR})

# adds libraries
add_library (directory directory.h directory.c)
target_link_libraries (simple-fat directory)

add_library (handlers handlers.h handlers/save_new_file.c)
target_link_libraries (simple-fat handlers)

add_library (fat fat.h fat.c)
target_link_libraries (simple-fat fat)

add_library (formatter formatter.h formatter.c)
target_link_libraries (simple-fat formatter)

add_library (logger logger.h logger.c)
target_link_libraries (simple-fat logger)
