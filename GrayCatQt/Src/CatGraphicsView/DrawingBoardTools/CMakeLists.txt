cmake_minimum_required(VERSION 3.10)

project(DrawingBoardTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

add_definitions("-Wall -g")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

aux_source_directory(. DIR_LIB_SRCS)

add_library(DrawingBoardTools SHARED ${DIR_LIB_SRCS})
add_library(DrawingBoardTools_static STATIC ${DIR_LIB_SRCS})

SET_TARGET_PROPERTIES(DrawingBoardTools_static PROPERTIES OUTPUT_NAME "DrawingBoardTools")
SET_TARGET_PROPERTIES(DrawingBoardTools PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(DrawingBoardTools_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(DrawingBoardTools PRIVATE Qt5::Widgets)
target_link_libraries(DrawingBoardTools PRIVATE Qt5::Core)
target_link_libraries(DrawingBoardTools_static PRIVATE Qt5::Widgets)
target_link_libraries(DrawingBoardTools_static PRIVATE Qt5::Core)

target_include_directories(DrawingBoardTools PUBLIC ${PROJECT_SOURCE_DIR})
