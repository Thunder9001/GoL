cmake_minimum_required(VERSION 2.8)

project(GameOfLife)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(unity/include)

add_executable(GameOfLife main.c logic.c graphics.c fileHandler.c )
add_executable(GoLUnitTests unit_tests.c logic.c fileHandler.c unity/src/unity.c)
target_link_libraries(GameOfLife ${SDL2_LIBRARIES})