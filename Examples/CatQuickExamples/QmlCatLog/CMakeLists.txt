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

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
else()
    link_libraries(pthread)
endif()

include_directories("${PROJECT_SOURCE_DIR}/../../../GrayCatQtCore/Src/CatLog")
add_subdirectory(${PROJECT_SOURCE_DIR}/../../../GrayCatQtCore/Src/CatLog CatLog.out)
set (EXTRA_LIBS2 ${EXTRA_LIBS2} CatLog_Sington)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

aux_source_directory(. DIR_LIB_SRCS)

add_library(${PROJECT_NAME} ${DIR_LIB_SRCS} "QmlCatLog.h")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS2})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0.0 SOVERSION 1)

add_library("${PROJECT_NAME}_shared" SHARED ${DIR_LIB_SRCS} "QmlCatLog.h")
target_compile_definitions("${PROJECT_NAME}_shared" PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries("${PROJECT_NAME}_shared" PRIVATE Qt5::Core Qt5::Quick)
target_link_libraries("${PROJECT_NAME}_shared" PUBLIC ${EXTRA_LIBS2})
SET_TARGET_PROPERTIES("${PROJECT_NAME}_shared" PROPERTIES VERSION 1.0.0.0 SOVERSION 1)



