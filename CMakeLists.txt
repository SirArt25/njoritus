cmake_minimum_required(VERSION 3.15)

project(MyProject LANGUAGES C)

# Set the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CONFIG_DIR ${CMAKE_SOURCE_DIR}/cmake)

# Include Compiler version checker
include(${CMAKE_CONFIG_DIR}/check_c_compiler_version.cmake)

# Include Cmake Config 
include(${CMAKE_CONFIG_DIR}/config.cmake)

# Include APR finding
include(${CMAKE_CONFIG_DIR}/apr.cmake)


# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the C executable
add_executable(njoritus src/main.c)

# Specify include directories
target_include_directories(njoritus PRIVATE ${CMAKE_SOURCE_DIR}/include)