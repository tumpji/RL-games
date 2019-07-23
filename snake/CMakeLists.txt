cmake_minimum_required(VERSION 3.0)

project(Snake)

set(Snake_VERSION_MAJOR 1)
set(Snake_VERSION_MINOR 0)


find_package(Boost COMPONENTS REQUIRED python36) 
message("Boost include path: " ${Boost_INCLUDE_DIRS})
message("Boost library path: " ${Boost_LIBRARIES})

find_package(PythonLibs 3 REQUIRED)
message("Python-dev include path: " ${PYTHON_INCLUDE_DIRS})
message("Python-dev library path: " ${PYTHON_LIBRARIES})



set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -O0 -g3 -ggdb -Wno-undef")




add_executable(snake_interactive test.cpp ../board/board.cpp)

foreach(size 5)
    set(CURNAME "snake_${size}_${size}")
    python_add_module(${CURNAME} shared.cpp)

    target_compile_definitions(${CURNAME} PUBLIC DEF_BOARD_SIZE_X=${size} DEF_BOARD_SIZE_Y=${size} NAME=snake_${size}_${size}) 
    target_include_directories(${CURNAME} PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    target_link_libraries(${CURNAME} PUBLIC ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
endforeach(size)

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/../board/)




