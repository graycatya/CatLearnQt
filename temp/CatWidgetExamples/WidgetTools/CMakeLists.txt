cmake_minimum_required(VERSION 3.10)

project(WidgetTools LANGUAGES CXX)

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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../GrayCatQt/Src/CatLog)
#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
#find_android_gui()

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SRC_UI_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

add_subdirectory(QcustomplotCharts)
add_subdirectory(SideWidgetTools)
add_subdirectory(InputTools)
add_subdirectory(CatTableViewTools)

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(${PROJECT_NAME} ${CURPATH_DIR_LIB_SRCS}
                            ${SRC_HEAD_LIST}
                            ${SRC_UI_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC QcustomplotCharts)
target_link_libraries(${PROJECT_NAME} PUBLIC SideWidgetTools)
target_link_libraries(${PROJECT_NAME} PUBLIC CatTableViewTools)
