cmake_minimum_required(VERSION 3.10)

project(CatWidgetExamples LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

find_package(Qt5 COMPONENTS Core Gui Widgets Quick REQUIRED)

set(PROJECT_QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/Resource/Resource.qrc)
qt5_add_resources(PROJECT_QRC_FILES ${PROJECT_QRC_SOURCE_FILES})

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
target_link_libraries(${PROJECT_NAME} PUBLIC ImageTools)
target_link_libraries(${PROJECT_NAME} PUBLIC WidgetTools)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Quick)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Gui)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)

