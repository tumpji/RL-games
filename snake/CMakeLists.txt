cmake_minimum_required(VERSION 2.6)

project(Snake)

set(Snake_VERSION_MAJOR 1)
set(Snake_VERSION_MINOR 0)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -g3 -ggdb")




add_executable(snake_interactive test.cpp ../board/board.cpp)

foreach(size 5 10 15 20 25)
    add_library("snake_${size}" ../board/board.cpp shared.cpp)
    target_compile_definitions("snake_${size}" PRIVATE DEF_BOARD_SIZE_X=${size} DEF_BOARD_SIZE_Y=${size}) 
    #target_compile_options("snake_${size}" PRIVATE "-DDEF_BOARD_SIZE_X" "${size}" "-DDEF_BOARD_SIZE_Y" "${size}")
endforeach(size)

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/../board/)


