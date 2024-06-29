cmake_minimum_required(VERSION 3.15)

project(MyProject LANGUAGES C)

# Set the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")


# Set the output directory for runtime binaries (executables)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Optionally, set the output directory for library files if needed
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the C executable
add_executable(njoritus src/main.c)

# Specify include directories
target_include_directories(njoritus PRIVATE ${CMAKE_SOURCE_DIR}/include)