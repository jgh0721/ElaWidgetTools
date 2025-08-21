cmake_minimum_required( VERSION 3.20 )

project(ElaWidgetToolsDesigner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets UiPlugin Designer)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets UiPlugin Designer)

add_definitions(-DQT_PLUGIN)
add_definitions(-DQDESIGNER_EXPORT_WIDGETS)
add_definitions(-DELAWIDGETTOOLS_LIBRARY)

set(SOURCE_MAIN
    ${CMAKE_CURRENT_SOURCE_DIR}/ElaWidgetToolsDesigner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ElaWidgetToolsDesigner.hpp
    )

qt6_add_plugin( ElaWidgetToolsDesigner SHARED
                CLASS_NAME ElaWidgetToolsDesignerPlugin
                MANUAL_FINALIZATION
                ${SOURCE_MAIN} )

set(RESORUCE_MAIN
    ${CMAKE_CURRENT_SOURCE_DIR}/../ElaWidgetToolsExample/Resource/Image/control/TreeView.png
    )

qt_add_resources(${PROJECT_NAME} "ElaWidgetToolsDesigner"
                 RESOURCES PREFIX "/"
                 BASE "${CMAKE_CURRENT_SOURCE_DIR}/../ElaWidgetToolsExample"
                 FILES
                 ${RESORUCE_MAIN}
                 )

qt_add_resources( ${PROJECT_NAME} "ElaWidgetToolsDesigner"
                  RESOURCES PREFIX "/"
                  BASE "${CMAKE_CURRENT_SOURCE_DIR}/../ElaWidgetTools/Font"
                  FILES
                  ${CMAKE_CURRENT_SOURCE_DIR}/../ElaWidgetTools/Font/ElaAwesome.ttf
                  )

message(STATUS ${RESORUCE_MAIN})

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

if( WIN32 )
    target_link_libraries(${PROJECT_NAME} PRIVATE
                          Qt${QT_VERSION_MAJOR}::Core
                          Qt${QT_VERSION_MAJOR}::Gui
                          Qt${QT_VERSION_MAJOR}::Widgets
                          Qt${QT_VERSION_MAJOR}::UiPlugin
                          Qt${QT_VERSION_MAJOR}::Designer
                          ElaWidgetTools
                          )
else()
endif()

if (WIN32)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
            )
    if (MSVC)
        install(
                FILES $<TARGET_PDB_FILE:${PROJECT_NAME}>
                DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME} OPTIONAL)
    endif ()
endif ()

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif ()

