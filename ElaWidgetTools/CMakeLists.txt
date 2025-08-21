cmake_minimum_required(VERSION 3.20)

project(ElaWidgetTools VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DELAWIDGETTOOLS_LIBRARY)

FILE(GLOB ORIGIN *.h *.cpp)
FILE(GLOB PRIVATE private/*.h private/*.cpp)
FILE(GLOB DEVELOPER DeveloperComponents/*.h DeveloperComponents/*.cpp)

source_group(include FILES ${INCLUDE})
source_group(private FILES ${PRIVATE})
source_group(DeveloperComponents FILES ${DEVELOPER})

set(PROJECT_SOURCES
    ${ORIGIN}
    ${PRIVATE}
    ${DEVELOPER}
    ${CMAKE_CURRENT_SOURCE_DIR}/ElaWidgetTools.qrc
)

if (ELAWIDGETTOOLS_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
    add_definitions(-DELAWIDGETTOOLS_STATIC_LIBRARY)
else ()
    set(LIB_TYPE "SHARED")
endif ()

set(QT_I18N_SOURCE_LANGUAGE cn)
set(QT_I18N_TRANSLATED_LANGUAGES ko en)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(${PROJECT_NAME} ${LIB_TYPE}
        ${PROJECT_SOURCES}
    )
else ()
    add_library(${PROJECT_NAME} ${LIB_TYPE}
        ${PROJECT_SOURCES}
    )
endif ()

qt_add_lupdate( TS_FILES ElaWidgetTools_ko.ts ElaWidgetTools_en.ts
                SOURCES ${PROJECT_SOURCES}
                SOURCE_TARGETS ${PROJECT_NAME}
                OPTIONS -source-language cn
                )

qt_add_lrelease( TS_FILES ElaWidgetTools_ko.ts ElaWidgetTools_en.ts
                 QM_OUTPUT_DIRECTORY translations
                 QM_FILES_OUTPUT_VARIABLE QM_FILES )

# Add generated .qm files as resources to the library
set(QT_RESOURCE_FILES)
foreach(QM_FILE ${QM_FILES})
    # Extract the filename from the .qm file path
    get_filename_component(qm_filename ${QM_FILE} NAME)

    # Set resource alias for each .qm file
    set_source_files_properties(${QM_FILE} PROPERTIES QT_RESOURCE_ALIAS translations/${qm_filename})

    list(APPEND QT_RESOURCE_FILES ${QM_FILE})
endforeach()

qt_add_resources(${PROJECT_NAME}
                 PREFIX "/translations"
                 FILES
                 ${QT_RESOURCE_FILES}
                 )

FILE(GLOB EXPORT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DeveloperComponents>
    $<INSTALL_INTERFACE:${PROJECT_NAME}/include>
)

if (MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif ()
if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        D3D11
        DXGI
    )
else ()
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
    )
endif ()


install(
    TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_resources_1
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${PROJECT_NAME}/lib
    LIBRARY DESTINATION ${PROJECT_NAME}/lib
    RUNTIME DESTINATION ${PROJECT_NAME}/bin
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_resources_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/ElaWidgetToolsExample
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/ElaWidgetToolsExample
)
if (MSVC AND NOT LIB_TYPE STREQUAL "STATIC")
    install(
        FILES $<TARGET_PDB_FILE:${PROJECT_NAME}>
        DESTINATION ${CMAKE_INSTALL_PREFIX}/ElaWidgetToolsExample OPTIONAL)
endif ()

install(FILES ${EXPORT_HEADERS} DESTINATION ${PROJECT_NAME}/include)

set(INCLUDE_DIRS include)
set(LIBRARIES ${PROJECT_NAME})
set(LIB_DIR lib)

install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${PROJECT_NAME}/lib/cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION 2.0.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake
    PATH_VARS INCLUDE_DIRS LIBRARIES LIB_DIR
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
)

install(
    FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake DESTINATION ${PROJECT_NAME}/lib/cmake
)
install(FILES ${QM_FILES} DESTINATION "translations")