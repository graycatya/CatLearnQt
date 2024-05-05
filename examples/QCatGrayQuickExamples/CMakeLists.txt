cmake_minimum_required(VERSION 3.10)

project(QCatGrayQuickExamples LANGUAGES CXX)


MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DAPP_NAME="QCatGrayQuickExamples")
add_definitions(-DAPP_VERSION="v1.3.0")
add_definitions(-DWEBRESOURCEPATH="file:///${CMAKE_CURRENT_SOURCE_DIR}/WebResource")



find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QuickControls2 Qml WebEngineQuick WebView WebSockets Quick3D WebEngine REQUIRED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 Qml WebEngineQuick WebView WebSockets Quick3D REQUIRED)
else(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 Qml WebEngine WebView WebSockets Quick3D REQUIRED)
endif(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
file(GLOB SRC_LIST  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
              "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SRC_QRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Resource.qrc"
  "${CMAKE_CURRENT_SOURCE_DIR}/QmlSrc/Qt${QT_VERSION_MAJOR}Compat/QmlSrc.qrc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(PROJECT_QRC_FILES ${SRC_QRC_LIST})
else(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt5_add_resources(PROJECT_QRC_FILES ${SRC_QRC_LIST})
endif(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/WebResource DESTINATION ${PROJECT_BINARY_DIR})

add_subdirectory(Src/TableFunction)
add_subdirectory(Src/WebChannelFunction)

set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Lang")

set(TS_FILES
    "${TS_DIR}/language_en.ts"
    "${TS_DIR}/language_zh_CN.ts"
)



if(WIN32)
    list(APPEND CURPATH_DIR_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Resource/app_win32.rc)
endif(WIN32)

add_executable(${PROJECT_NAME}
  ${CURPATH_DIR_LIB_SRCS}
  ${SRC_LIST}
  ${PROJECT_QRC_FILES}
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Quick
          Qt${QT_VERSION_MAJOR}::QuickControls2
          Qt${QT_VERSION_MAJOR}::Qml
          Qt${QT_VERSION_MAJOR}::QuickPrivate
          Qt${QT_VERSION_MAJOR}::QmlPrivate
          Qt${QT_VERSION_MAJOR}::WebView
          Qt${QT_VERSION_MAJOR}::WebSockets
          Qt${QT_VERSION_MAJOR}::Quick3D)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineQuick)
else(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt${QT_VERSION_MAJOR}::WebEngine)
endif(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

target_link_libraries(${PROJECT_NAME} PRIVATE TableFunction_a
                                              WebChannelFunction_a
                                              QCatGrayQuick
                                              QCatGrayQuickQrenCodeQml_a
                                              QCatGrayModel_a
                                              QCatGrayUniversal_a)



