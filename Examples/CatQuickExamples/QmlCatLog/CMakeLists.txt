cmake_minimum_required(VERSION 3.10)

project(QmlCatLog)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

add_definitions("-Wall -g")
add_definitions(-std=c++11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME)
message(STATUS ${STATIC_NAME})

link_unix_lib(pthread)

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

#add_subdirectory(${PROJECT_SOURCE_DIR}/../../../GrayCatQtCore/Src/CatLog CatLog.out)
#set (EXTRA_LIBS2 ${EXTRA_LIBS2} CatLog_Sington)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS}
                                  ${SRC_HEAD_LIST})

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
target_compile_definitions(${STATIC_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${STATIC_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(${STATIC_NAME} PRIVATE CatLog_Sington)

add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS}
                                   ${SRC_HEAD_LIST})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0.0 SOVERSION 1)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(${PROJECT_NAME} PRIVATE CatLog_Sington)
target_link_android_gui(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})



