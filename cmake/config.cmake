# This file contains the global configuration for CMake

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Optionally, set the output directory for library files if needed
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.c")
set(INCLUDES_LIST ${CMAKE_SOURCE_DIR}/include)

set(EXTERNAL_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/external_projects)
