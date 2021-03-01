cmake_minimum_required(VERSION 3.5)

project(gviewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost COMPONENTS graph REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif ()

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
file(GLOB_RECURSE UI ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

qt5_add_resources(QRC_SOURCES ${RESOURCES})

message(QRC: ${QRC_SOURCES})
add_library(gviewer
    STATIC
    ${SOURCES}
    ${MOC_Files}
    ${HEADERS}
    ${QRC_SOURCES}
    ${UI})

target_link_libraries(gviewer PRIVATE Qt5::Widgets)

target_compile_definitions(gviewer PRIVATE GVIEWER_LIBRARY)

