cmake_minimum_required(VERSION 3.5)

add_subdirectory(gviewer)
add_subdirectory(example)

target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(.)
