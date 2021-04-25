
cmake_minimum_required(VERSION 3.10)

project(CatLog_Sington)



message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

add_definitions("-Wall -g")
add_definitions(-std=c++17)

IF (WIN32)
	MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
    link_libraries(pthread)
	MESSAGE(STATUS "Now is UNIX-like OS's. Including aPPLE os x  and CygWin")
ENDIF ()



aux_source_directory(. DIR_LIB_SRCS)

add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})
add_library(${STATIC_NAME} STATIC ${DIR_LIB_SRCS})

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.1 SOVERSION 1)
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC ${DIR_LIB_SRCS})

Install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)