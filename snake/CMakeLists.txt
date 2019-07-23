cmake_minimum_required(VERSION 2.6)

project(Snake)

set(Snake_VERSION_MAJOR 1)
set(Snake_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -g3 -ggdb")




add_executable(snake_interactive test.cpp ../board/board.cpp)
add_library(snake_10_10.so ../board/board.cpp shared.cpp)


include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/../board/)


