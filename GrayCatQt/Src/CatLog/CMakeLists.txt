
cmake_minimum_required(VERSION 3.10)

project(CatLog_Sington)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

add_definitions("-Wall -g")
add_definitions(-std=c++17)
link_libraries(pthread)

aux_source_directory(. DIR_LIB_SRCS)

target_include_directories(PUBLIC ${DIR_LIB_SRCS})

add_library(CatLog_Sington SHARED ${DIR_LIB_SRCS})
add_library(CatLog_Sington_static STATIC ${DIR_LIB_SRCS})

SET_TARGET_PROPERTIES(CatLog_Sington_static PROPERTIES OUTPUT_NAME "CatLog_Sington")
SET_TARGET_PROPERTIES(CatLog_Sington PROPERTIES VERSION 1.0.1 SOVERSION 1)
SET_TARGET_PROPERTIES(CatLog_Sington_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)