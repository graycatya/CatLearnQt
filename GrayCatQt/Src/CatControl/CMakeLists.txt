cmake_minimum_required(VERSION 3.10)

project(CatControl LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

set(QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/Resource/CatControl.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

aux_source_directory(. DIR_LIB_SRCS)

#qt5_add_resources(${DIR_LIB_SRCS} ${PROJECT_SOURCE_DIR}/Resource/CatControl.qrc)

add_library(CatControl SHARED ${DIR_LIB_SRCS} ${QRC_FILES})
add_library(CatControl_static STATIC ${DIR_LIB_SRCS} ${QRC_FILES})

SET_TARGET_PROPERTIES(CatControl_static PROPERTIES OUTPUT_NAME "CatControl")
SET_TARGET_PROPERTIES(CatControl PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(CatControl_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(CatControl PRIVATE Qt5::Widgets)
target_link_libraries(CatControl PRIVATE Qt5::Core)
target_link_libraries(CatControl_static PRIVATE Qt5::Widgets)
target_link_libraries(CatControl_static PRIVATE Qt5::Core)

target_include_directories(CatControl PUBLIC ${PROJECT_SOURCE_DIR})
