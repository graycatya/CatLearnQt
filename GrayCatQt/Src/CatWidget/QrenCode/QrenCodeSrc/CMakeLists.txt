cmake_minimum_required(VERSION 3.10)

project(QrenCodeSrc)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../module/cmake")

include(GrayCatQt)

load_name_static(STATIC_NAME) 
message(STATUS ${STATIC_NAME})

add_definitions(-DHAVE_CONFIG_H)

file(GLOB SRC_HEAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

#find_android_gui()
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS)


#list(REMOVE_ITEM SRC_HEAD_LIST ${CMAKE_CURRENT_SOURCE_DIR}/qrencode_inner.h)

add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS}
                                  ${SRC_HEAD_LIST})

add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS}
                                   ${SRC_HEAD_LIST})

#SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
SET_TARGET_PROPERTIES(${STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)




#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
