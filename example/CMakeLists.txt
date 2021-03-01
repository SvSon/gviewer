cmake_minimum_required(VERSION 3.5)

project(example LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost COMPONENTS graph REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif ()

add_executable(example main.cpp)

target_link_libraries(example PRIVATE Qt5::Widgets gviewer)
