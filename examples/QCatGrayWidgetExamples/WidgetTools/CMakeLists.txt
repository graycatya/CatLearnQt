cmake_minimum_required(VERSION 3.10)

project(WidgetTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

add_subdirectory(QcustomplotCharts)
add_subdirectory(SideWidgetTools)
add_subdirectory(InputTools)
add_subdirectory(CatTableViewTools)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                                QcustomplotCharts
                                                SideWidgetTools
                                                CatTableViewTools
                                                CatConfig
                                                QCatGrayUniversal_a
                                                QCatGrayQrenCode_a
                                                QCatGrayWidgetControls_a)

