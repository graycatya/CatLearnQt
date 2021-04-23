cmake_minimum_required(VERSION 3.10)

project(TeachingTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

add_definitions("-Wall -g")
#add_definitions(-std=c++17)

find_package(Qt5 COMPONENTS Core Gui Widgets Svg REQUIRED)

set(QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/TeachingTool/TeachingTool.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

aux_source_directory(. DIR_LIB_SRCS)

add_library(TeachingTools SHARED ${DIR_LIB_SRCS} ${QRC_FILES})
add_library(TeachingTools_static STATIC ${DIR_LIB_SRCS} ${QRC_FILES})

SET_TARGET_PROPERTIES(TeachingTools_static PROPERTIES OUTPUT_NAME "TeachingTools")
SET_TARGET_PROPERTIES(TeachingTools PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(TeachingTools_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(TeachingTools PRIVATE Qt5::Widgets)
target_link_libraries(TeachingTools PRIVATE Qt5::Core)
target_link_libraries(TeachingTools PRIVATE Qt5::Svg)
target_link_libraries(TeachingTools_static PRIVATE Qt5::Widgets)
target_link_libraries(TeachingTools_static PRIVATE Qt5::Core)
target_link_libraries(TeachingTools_static PRIVATE Qt5::Svg)

target_include_directories(TeachingTools PUBLIC ${PROJECT_SOURCE_DIR})
