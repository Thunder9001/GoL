cmake_minimum_required(VERSION 2.8)

project(GameOfLife)


set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(unity/include)

add_executable(GameOfLife main.c logic.c logic.h)
add_executable(GoLUnitTests unity_tests.c logic.c unity/src/unity.c unit_tests.c)
target_link_libraries(GameOfLife ${SDL2_LIBRARIES})