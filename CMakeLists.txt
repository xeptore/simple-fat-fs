cmake_minimum_required(VERSION 3.19)

SET(CMAKE_C_COMPILER /usr/bin/clang-11)

project(simple-fat)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app main.c constants.h directory.c fat.c formatter.c logger.c)

