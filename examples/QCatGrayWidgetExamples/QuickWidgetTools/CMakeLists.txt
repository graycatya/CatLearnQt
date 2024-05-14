cmake_minimum_required(VERSION 3.10)

project(QuickWidgetTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets Quick QuickWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Quick QuickWidgets REQUIRED)

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                                Qt${QT_VERSION_MAJOR}::Gui
                                                Qt${QT_VERSION_MAJOR}::Widgets
                                                Qt${QT_VERSION_MAJOR}::Quick
                                                Qt${QT_VERSION_MAJOR}::QuickWidgets
                                                QCatGrayQrenCode_a
                                                QCatGrayQuickQrenCodeQml_a
                                                QCatGrayUniversal_a)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
