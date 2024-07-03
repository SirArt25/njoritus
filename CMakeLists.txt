cmake_minimum_required(VERSION 3.22.1)

project(Njoritus LANGUAGES C)

# Set the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# CMAKE_EXPORT_COMPILE_COMMANDS for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CONFIG_DIR ${CMAKE_SOURCE_DIR}/cmake)

# Include Compiler version checker
include(${CMAKE_CONFIG_DIR}/check_c_compiler_version.cmake)

# Include Cmake Config
include(${CMAKE_CONFIG_DIR}/config.cmake)

# Include APR finding If you want verbose set APR_FIND_VERBOSE
set(APR_FIND_VERBOSE True)
include(${CMAKE_CONFIG_DIR}/apr.cmake)

# Include clang-tidy verifier
include(${CMAKE_CONFIG_DIR}/clang_tidy_verifier.cmake)

# Add the C executable
add_executable(njoritus src/main.c)

target_link_libraries(njoritus ${APR_LIBRARY})

# Specify include directories
foreach(dir IN LISTS INCLUDES_LIST)
  target_include_directories(njoritus PRIVATE ${dir})
endforeach()

# Inlcude telebot external project
include(${CMAKE_CONFIG_DIR}/telebot.cmake)

message(STATUS "TELEBOT_INCLUDE_DIR = ${TELEBOT_INCLUDE_DIR}")
add_custom_target(
  clang-tidy-njoritus
  COMMAND
    "${CLANG_TIDY}" -p ${CMAKE_BINARY_DIR} ${SOURCE_FILES} --
    -I${CMAKE_SOURCE_DIR}/include -I${APR_INCLUDE_DIR} -I${TELEBOT_INCLUDE_DIR}
  COMMENT "Running clang-tidy...")
