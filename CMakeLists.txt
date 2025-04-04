cmake_minimum_required(VERSION 3.20)

project(ElaFramework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

option(ELAPACKETIO_BUILD_STATIC_LIB "Build static library." ON)
option(ELAWIDGETTOOLS_BUILD_STATIC_LIB "Build static library." ON)

IF(DEFINED ENV{QT_PATH})
    SET(QT_SDK_DIR $ENV{QT_PATH})
ELSE()
    SET(QT_SDK_DIR D:/Qt/Qt-6.9.0-VC2022-X64-D-MD-OCI-2025-04-03 CACHE PATH "QT SDK DIR" FORCE)
ENDIF()

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

list(APPEND CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets LinguistTools)

add_subdirectory(ElaWidgetTools)
if (WIN32)
    add_subdirectory(ElaPacketIO)
endif ()
add_subdirectory(ElaWidgetToolsExample)
add_subdirectory(ElaWidgetToolsDesigner)

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElaWidgetTools)
endif ()
