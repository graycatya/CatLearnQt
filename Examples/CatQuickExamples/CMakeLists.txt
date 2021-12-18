cmake_minimum_required(VERSION 3.14)

project(CatQuickExamples LANGUAGES CXX)


MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DAPP_NAME="CatQuickExamples")
add_definitions(-DAPP_VERSION="v1.2.0")
add_definitions(-DLOG_PATH="Logs/")
add_definitions(-DQGUIAPPLICATION_CLASS)
add_definitions(-DGrayCatQtQuickImportPath="qrc:///")
add_definitions(-DWEBRESOURCEPATH="file:///$$PWD/WebResource")
#DEFINES += WEBRESOURCEPATH=\\\"file:///$$PWD/WebResource\\\"


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../module/cmake")

include(GrayCatQt)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/CatLog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/SingleApplication)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)


file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SRC_QRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Resource.qrc" 
                        "${CMAKE_CURRENT_SOURCE_DIR}/QmlSrc/QmlSrc.qrc")

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt GrayCatQt.out)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore GrayCatQtCore.out)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick GrayCatQtQuick.out)
add_subdirectory(QmlCatLog)
add_subdirectory(QrenCode)

set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Lang")

set(TS_FILES
    "${TS_DIR}/language_en.ts"
    "${TS_DIR}/language_zh_CN.ts"
)

#build_linguisttools(${TS_FILES})

filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${CURPATH_DIR_LIB_SRCS}
        ${SRC_HEAD_LIST}
        ${SRC_QRC_LIST}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${CURPATH_DIR_LIB_SRCS}
            ${SRC_HEAD_LIST}
            ${SRC_QRC_LIST}
        )
    else()
        add_executable(${PROJECT_NAME}
          ${CURPATH_DIR_LIB_SRCS}
          ${SRC_HEAD_LIST}
          ${SRC_QRC_LIST}
        )
    endif()
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

target_link_libraries(${PROJECT_NAME} PRIVATE GrayCatQtCore)
target_link_libraries(${PROJECT_NAME} PRIVATE GrayCatQtQuick)
target_link_libraries(${PROJECT_NAME} PRIVATE QmlCatLog)
target_link_libraries(${PROJECT_NAME} PRIVATE QrenCode)

