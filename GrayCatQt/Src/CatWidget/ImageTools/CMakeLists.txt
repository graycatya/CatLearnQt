cmake_minimum_required(VERSION 3.10)

project(ImageTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

add_definitions("-Wall -g")
#add_definitions(-std=c++17)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_unix_package(X11Extras)

find_android_gui()
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

set(QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/ImageTools/ImageTools.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

add_src_lib(${QRC_FILES})

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
target_link_android_gui(${PROJECT_NAME})
if(UNIX AND (NOT ANDROID) AND (NOT MACROS))
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::X11Extras)
endif(UNIX AND (NOT ANDROID) AND (NOT MACROS))

target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${STATIC_NAME} PRIVATE Qt5::Core)
if(UNIX AND (NOT ANDROID) AND (NOT MACROS))
    target_link_libraries(${STATIC_NAME} PRIVATE Qt5::X11Extras)
endif(UNIX AND (NOT ANDROID) AND (NOT MACROS))

link_unix_lib(X11)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
