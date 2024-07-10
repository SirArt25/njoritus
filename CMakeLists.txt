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
add_executable(njoritus ${NJORITUS_SOURCE_FILES})

target_link_libraries(njoritus ${APR_LIBRARY})

# Inlcude telebot external project
include(${CMAKE_CONFIG_DIR}/telebot.cmake)

# Inlcude thor-shield
include(${CMAKE_CONFIG_DIR}/thor-shield.cmake)

# Specify include directories
foreach(dir IN LISTS INCLUDES_LIST)
  target_include_directories(njoritus PRIVATE ${dir})
endforeach()

# Include linting.cmake for creating linting targets
include(${CMAKE_CONFIG_DIR}/linting.cmake)

# Include odin-gaze
include(${CMAKE_CONFIG_DIR}/odin-gaze.cmake)

# Include tests include(${CMAKE_CONFIG_DIR}/cunit.cmake)
option(ENABLE_TESTS "Enable tests" ON)

if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
# Add aditional clean files
list(JOIN ADDITIONAL_CLEAN_FILES ";" ADDITIONAL_CLEAN_FILES_STRING)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
                                    "${ADDITIONAL_CLEAN_FILES_STRING}")
