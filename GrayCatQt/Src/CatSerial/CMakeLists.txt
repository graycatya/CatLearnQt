cmake_minimum_required(VERSION 3.10)

project(CatSerial LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

add_definitions("-Wall -g")

find_package(Qt5 COMPONENTS Core SerialPort Widgets REQUIRED)

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#   endif()
#endif()

if(WIN32)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CURPATH_DIR_LIB_SRCS)
else()
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CURPATH_DIR_LIB_SRCS)
    list(REMOVE_ITEM CURPATH_DIR_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/CatWinMonitorSerial.h)
    list(REMOVE_ITEM CURPATH_DIR_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/CatWinMonitorSerial.cpp)
endif(WIN32)


add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS})

if(NOT ANDROID)
    add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS})
endif()

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::SerialPort)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

if(NOT ANDROID)
    SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Core)
    target_link_libraries(${STATIC_NAME} PRIVATE Qt5::SerialPort)
endif()





target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
