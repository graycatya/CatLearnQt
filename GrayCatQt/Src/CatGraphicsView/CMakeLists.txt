cmake_minimum_required(VERSION 3.10)

project(CatGraphicsView LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_android_gui()

include_directories("./TeachingTools/")
include_directories("./DrawingBoardTools/")

add_subdirectory(TeachingTools)
add_subdirectory(DrawingBoardTools)

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS}
                                   ${SRC_HEAD_LIST})

add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS}
                                  ${SRC_HEAD_LIST})

#target_include_directories(${PROJECT_NAME} PUBLIC "./TeachingTools/")
#target_include_directories(${PROJECT_NAME} PUBLIC "./DrawingBoardTools/")

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} PUBLIC TeachingTools)
target_link_libraries(${PROJECT_NAME} PUBLIC DrawingBoardTools)
target_link_android_gui(${PROJECT_NAME})

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Core)
target_link_libraries(${STATIC_NAME} PRIVATE Qt5::OpenGL)
target_link_libraries(${STATIC_NAME} PUBLIC TeachingTools)
target_link_libraries(${STATIC_NAME} PUBLIC DrawingBoardTools)

target_include_directories(CatGraphicsView PUBLIC ${PROJECT_SOURCE_DIR})
