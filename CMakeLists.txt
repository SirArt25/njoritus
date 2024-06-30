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

# Find clang-tidy
find_program(CLANG_TIDY "clang-tidy")

# If clang-tidy is found, add it to the CMAKE_CXX_CLANG_TIDY variable
if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()


# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the C executable
add_executable(njoritus src/main.c)
target_link_libraries(njoritus ${APR_LIBRARY})
# Specify include directories
target_include_directories(njoritus 
            PRIVATE ${CMAKE_SOURCE_DIR}/include
            PRIVATE ${APR_INCLUDE_DIR}
)