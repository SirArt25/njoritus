# This file contains the global configuration for CMake

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Optionally, set the output directory for library files if needed
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE NJORITUS_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/njoritus/*.c")
file(GLOB_RECURSE NJORITUS_HEADER_FILES
     "${CMAKE_SOURCE_DIR}/include/njoritus/*.h")
set(INCLUDES_LIST ${CMAKE_SOURCE_DIR}/include)

set(EXTERNAL_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/external_projects)

set(DEV_NULL /dev/null)
