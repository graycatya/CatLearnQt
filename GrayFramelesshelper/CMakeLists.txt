cmake_minimum_required(VERSION 3.10)

project(GrayFramelesshelper LANGUAGES CXX)

set(SOURCES
    framelesshelper_global.h
    framelesshelper.h
    framelesshelper.cpp
    utilities.h
    utilities.cpp
    framelesswindowsmanager.h
    framelesswindowsmanager.cpp
)

if(TARGET Qt${QT_VERSION_MAJOR}::Quick)
    list(APPEND SOURCES
        framelessquickhelper.h
        framelessquickhelper.cpp
    )
endif()

if(WIN32)
    list(APPEND SOURCES
        framelesshelper_windows.h
        utilities_win32.cpp
        framelesshelper_win32.h
        framelesshelper_win32.cpp
    )
else()
    if(APPLE)
        list(APPEND SOURCES
            utilities_macos.mm
            nswindow_proxy.h
            nswindow_proxy.mm
            window_buttons_proxy.h
            window_buttons_proxy.mm
            scoped_nsobject.h
        )
    else()
        find_package(QT NAMES Qt6 Qt5 COMPONENTS X11Extras REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS X11Extras REQUIRED)
        list(APPEND SOURCES utilities_linux.cpp)
    endif()
endif()

add_library(${PROJECT_NAME} ${SOURCES})
add_library(CatGrayYa::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        FRAMELESSHELPER_STATIC
    )
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_TO_ASCII
    QT_NO_KEYWORDS
    QT_DEPRECATED_WARNINGS
    QT_DISABLE_DEPRECATED_BEFORE=0x060100
    FRAMELESSHELPER_BUILD_LIBRARY
)

if(TEST_UNIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        FRAMELESSHELPER_TEST_UNIX
    )
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE dwmapi user32 shell32 advapi32)
else()
    if(APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE
            "-framework Cocoa -framework Carbon"
        )
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE
            Qt${QT_VERSION_MAJOR}::X11Extras
            X11
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::GuiPrivate
)

if(TARGET Qt${QT_VERSION_MAJOR}::Quick)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Quick
    )
endif()

if(TARGET Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::WidgetsPrivate
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
)
