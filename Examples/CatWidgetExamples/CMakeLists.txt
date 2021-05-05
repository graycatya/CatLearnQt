cmake_minimum_required(VERSION 3.10)

project(CatWidgetExamples LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DAPP_NAME="CatWidgetExamples")
add_definitions(-DAPP_VERSION="v1.0.0")
add_definitions(-DLOG_PATH="Logs/")

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../module/cmake")

include(GrayCatQt)


load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt/Src/CatLog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt/Src/SingleApplication)

find_package(Qt5 COMPONENTS Core Gui Widgets Quick QuickWidgets Svg REQUIRED)

set(PROJECT_QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/Resource/Resource.qrc)
qt5_add_resources(PROJECT_QRC_FILES ${PROJECT_QRC_SOURCE_FILES})



set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resource/lang")

set(TS_FILES
    "${TS_DIR}/language_en.ts"
    "${TS_DIR}/language_zh_CN.ts"
)

build_linguisttools(${TS_FILES})

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SRC_UI_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt GrayCatQt.out)
add_subdirectory(CatConfig)
add_subdirectory(QuickWidgetTools)
add_subdirectory(WidgetTools)

add_executable(${PROJECT_NAME} ${CURPATH_DIR_LIB_SRCS}
                                ${SRC_HEAD_LIST}
                                ${SRC_UI_LIST}
                                ${PROJECT_QRC_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC GrayCatQt)
target_link_libraries(${PROJECT_NAME} PUBLIC CatConfig)
#target_link_libraries(${PROJECT_NAME} PUBLIC ImageTools)
target_link_libraries(${PROJECT_NAME} PUBLIC WidgetTools)
target_link_libraries(${PROJECT_NAME} PUBLIC QuickWidgetTools)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Quick)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::QuickWidgets)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Svg)

