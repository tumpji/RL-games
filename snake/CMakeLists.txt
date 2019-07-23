cmake_minimum_required(VERSION 2.6)

project(Snake)

set(Snake_VERSION_MAJOR 1)
set(Snake_VERSION_MINOR 0)


find_package(Boost COMPONENTS python3 REQUIRED)
message("Boost include path: " ${Boost_INCLUDE_DIRS})
message("Boost library path: " ${Boost_LIBRARIES})

find_package(PythonLibs REQUIRED)
message("Python-dev include path: " ${PYTHON_INCLUDE_DIRS})
message("Python-dev library path: " ${PYTHON_LIBRARIES})


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -g3 -ggdb")




add_executable(snake_interactive test.cpp ../board/board.cpp)

foreach(size 5 10 15 20 25)
    add_library("snake_${size}" ../board/board.cpp shared.cpp)

    target_compile_definitions("snake_${size}" PRIVATE DEF_BOARD_SIZE_X=${size} DEF_BOARD_SIZE_Y=${size}) 
    target_include_directories("snake_${size}" PRIVATE ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    target_link_libraries("snake_${size}" PRIVATE ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
endforeach(size)

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/../board/)


