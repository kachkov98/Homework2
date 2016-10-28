cmake_minimum_required(VERSION 2.6)
project(homework2)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -O2")

add_library(list STATIC list.cpp)
add_library(tree STATIC tree.cpp)
add_library(timer STATIC timer.cpp)
link_libraries(list)
link_libraries(tree list)

add_executable(level1 level1.cpp)
target_link_libraries(level1 list timer)

add_executable(level2 level2.cpp)
target_link_libraries(level2 tree timer)
