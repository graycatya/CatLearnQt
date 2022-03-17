cmake_minimum_required(VERSION 3.10)

project(GrayCatQtCore LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)
#add_definitions(-DWEBASSEMBLY)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME)
message(STATUS ${STATIC_NAME})

find_package(Qt5 COMPONENTS Core REQUIRED)

find_android_gui()
if((NOT WEBASSEMBLY))
    add_subdirectory(Src/CatEncp)
endif((NOT WEBASSEMBLY))

add_subdirectory(Src/CatLog)

if((NOT WEBASSEMBLY) OR (NOT IOS))
    add_subdirectory(Src/CatSerial)
endif((NOT WEBASSEMBLY) OR (NOT IOS))

add_subdirectory(Src/CatUniversal)

if((NOT WEBASSEMBLY))
    add_subdirectory(Src/CatNetWork)
    add_subdirectory(Src/SingleApplication)
endif((NOT WEBASSEMBLY))

add_library(${STATIC_NAME} STATIC)

add_library(${PROJECT_NAME} SHARED)

SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
if((NOT WEBASSEMBLY))
target_link_libraries(${PROJECT_NAME} PUBLIC CatEncp)
endif((NOT WEBASSEMBLY))
target_link_libraries(${PROJECT_NAME} PUBLIC CatLog_Sington)
if((NOT WEBASSEMBLY) OR (NOT IOS))
    target_link_libraries(${PROJECT_NAME} PUBLIC CatSerial)
endif((NOT WEBASSEMBLY) OR (NOT IOS))
target_link_libraries(${PROJECT_NAME} PUBLIC CatUniversal)
if((NOT WEBASSEMBLY))
    target_link_libraries(${PROJECT_NAME} PUBLIC CatNetWork)
    target_link_libraries(${PROJECT_NAME} PUBLIC SingleApplication)
endif((NOT WEBASSEMBLY))
target_link_android_gui(${PROJECT_NAME})

target_link_libraries(${STATIC_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${STATIC_NAME} PUBLIC CatLog_Sington)
if((NOT WEBASSEMBLY) OR (NOT IOS))
    target_link_libraries(${STATIC_NAME} PUBLIC CatSerial)
endif((NOT WEBASSEMBLY) OR (NOT IOS))
target_link_libraries(${STATIC_NAME} PUBLIC CatUniversal)
if((NOT WEBASSEMBLY))
    target_link_libraries(${STATIC_NAME} PUBLIC CatNetWork)
    target_link_libraries(${STATIC_NAME} PUBLIC SingleApplication)
endif((NOT WEBASSEMBLY))

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
