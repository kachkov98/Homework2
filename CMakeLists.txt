cmake_minimum_required(VERSION 2.6)
project(homework2)

add_library (list STATIC list.cpp)
add_library (tree STATIC tree.cpp)

add_executable(level1 level1.cpp)
target_link_libraries(level1 list)

add_executable(level2 level2.cpp)
target_link_libraries(level2 tree)

