cmake_minimum_required(VERSION 3.10)

project(QCatGrayWidgetExamples LANGUAGES CXX)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QMAKE_EXECUTABLE ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DAPP_NAME="QCatGrayWidgetExamples")
add_definitions(-DAPP_VERSION="v1.3.0")
add_definitions(-DQAPPLICATIONEXE_CLASS)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets Quick QuickWidgets Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Quick QuickWidgets Svg REQUIRED)


set(PROJECT_QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/Resource/Resource.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(PROJECT_QRC_FILES ${PROJECT_QRC_SOURCE_FILES})
else(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt5_add_resources(PROJECT_QRC_FILES ${PROJECT_QRC_SOURCE_FILES})
endif(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resource/lang")

set(TS_FILES
    "${TS_DIR}/language_en.ts"
    "${TS_DIR}/language_zh_CN.ts"
)

build_linguisttools(${TS_FILES})

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

add_subdirectory(CatConfig)
add_subdirectory(QuickWidgetTools)
add_subdirectory(WidgetTools)

if(WIN32)
    list(APPEND SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Resource/app_win32.rc)
endif(WIN32)

add_executable(${PROJECT_NAME}  ${SRC_LIST}
                                ${PROJECT_QRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE QCatGrayUniversal_a)
target_link_libraries(${PROJECT_NAME} PRIVATE CatConfig)
#target_link_libraries(${PROJECT_NAME} PUBLIC ImageTools)
target_link_libraries(${PROJECT_NAME} PRIVATE WidgetTools)
target_link_libraries(${PROJECT_NAME} PRIVATE QuickWidgetTools)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Svg)

