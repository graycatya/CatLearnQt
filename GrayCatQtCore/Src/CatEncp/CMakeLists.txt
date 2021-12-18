cmake_minimum_required(VERSION 3.10)

project(CatEncp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

add_definitions("-Wall -g")
add_definitions(-std=c++11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME)
message(STATUS ${STATIC_NAME})

link_unix_lib(pthread)

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

#add_subdirectory(${PROJECT_SOURCE_DIR}/../../../GrayCatQtCore/Src/CatLog CatLog.out)
#set (EXTRA_LIBS2 ${EXTRA_LIBS2} CatLog_Sington)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS}
                                  ${SRC_HEAD_LIST})

add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS}
                                   ${SRC_HEAD_LIST})