cmake_minimum_required(VERSION 3.10)

project(CatQcustomplot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#ADD_DEFINITIONS(-D QCUSTOMPLOT_USE_OPENGL)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})


find_package(Qt5 COMPONENTS Core Widgets PrintSupport REQUIRED)
find_android_gui()
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})


filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CatQcustomplotCharts CAT_QCUSTOMPLOTCHARTS_SRCS)

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB CATQCUSTOMPLOT_SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/CatQcustomplotCharts/*.h")

add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS} 
                                    ${CAT_QCUSTOMPLOTCHARTS_SRCS}
                                    ${SRC_HEAD_LIST}
                                    ${CATQCUSTOMPLOT_SRC_HEAD_LIST})

add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS} 
                                    ${CAT_QCUSTOMPLOTCHARTS_SRCS}
                                    ${SRC_HEAD_LIST}
                                    ${CATQCUSTOMPLOT_SRC_HEAD_LIST})

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::PrintSupport)
target_link_android_gui(${PROJECT_NAME})

target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Core)
target_link_libraries(${STATIC_NAME} PRIVATE Qt5::PrintSupport)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
