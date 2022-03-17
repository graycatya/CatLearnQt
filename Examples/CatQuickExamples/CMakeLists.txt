cmake_minimum_required(VERSION 3.10)

project(CatQuickExamples LANGUAGES CXX)


MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DAPP_NAME="CatQuickExamples")
add_definitions(-DAPP_VERSION="v1.2.0")
add_definitions(-DLOG_PATH="Logs/")
add_definitions(-DQGUIAPPLICATIONEXE_CLASS)
#add_definitions(-DGrayCatQtQuickImportPath="qrc:///")
add_definitions(-DWEBRESOURCEPATH="file:///$$PWD/WebResource")
#DEFINES += WEBRESOURCEPATH=\\\"file:///$$PWD/WebResource\\\"


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../module/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick")

include(GrayCatQt)
include(GrayCatQtQuick)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/CatLog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/CatEncp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore/Src/SingleApplication)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick/Src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayFramelesshelper/)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QuickControls2 Qml WebEngine WebView WebSockets Quick3D REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 Qml WebEngine WebView WebSockets Quick3D REQUIRED)
find_package(OpenSSL REQUIRED)


find_graycatqtquick_pack("${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick")
file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SRC_QRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Resource.qrc"
                        "${CMAKE_CURRENT_SOURCE_DIR}/QmlSrc/QmlSrc.qrc"
                        "${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick/imports/GrayCatQtQuick/GrayCatQtQuick.qrc")
qt5_add_resources(PROJECT_QRC_FILES ${SRC_QRC_LIST})
#qt5_add_resources(PROJECT_QRC_FILES ${GrayCatQtQuickRes})
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQt GrayCatQt.out)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/WebResource DESTINATION ${PROJECT_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtCore GrayCatQtCore.out)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayCatQtQuick GrayCatQtQuick.out)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../GrayFramelesshelper GrayFramelesshelper.out)
add_subdirectory(QmlCatLog)
add_subdirectory(QrenCode)
add_subdirectory(Src/TableFunction)
add_subdirectory(Src/WebChannelFunction)

set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Lang")

set(TS_FILES
    "${TS_DIR}/language_en.ts"
    "${TS_DIR}/language_zh_CN.ts"
)

#build_linguisttools(${TS_FILES})
#message(${GrayCatQtQuickPath})
filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)

if(WIN32)
    list(APPEND CURPATH_DIR_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Resource/app_win32.rc)
endif(WIN32)

add_executable(${PROJECT_NAME}
  ${CURPATH_DIR_LIB_SRCS}
  ${SRC_HEAD_LIST}
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
          Qt${QT_VERSION_MAJOR}::WebEngine
          Qt${QT_VERSION_MAJOR}::WebView
          Qt${QT_VERSION_MAJOR}::WebSockets
          Qt${QT_VERSION_MAJOR}::Quick3D)

target_link_libraries(${PROJECT_NAME} PRIVATE GrayCatQtCore)
target_link_libraries(${PROJECT_NAME} PUBLIC GrayCatQtQuick)
target_link_libraries(${PROJECT_NAME} PRIVATE GrayFramelesshelper)
target_link_libraries(${PROJECT_NAME} PRIVATE QmlCatLog)
target_link_libraries(${PROJECT_NAME} PRIVATE QrenCode)
target_link_libraries(${PROJECT_NAME} PRIVATE TableFunction)
target_link_libraries(${PROJECT_NAME} PRIVATE WebChannelFunction)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE dwmapi user32 shell32 advapi32)
endif()

