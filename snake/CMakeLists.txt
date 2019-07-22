cmake_minimum_required(VERSION 2.6)

project(Snake)

set(Snake_VERSION_MAJOR 1)
set(Snake_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -g3 -ggdb")


#add_compile_options("${CMAKE_CXX_FLAGS_DEBUG}")



add_executable(snake_interactive test.cpp ../board/board.cpp)

target_include_directories(snake_interactive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../board/)





