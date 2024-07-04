# find PkgConfig and then LIBSECRET
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSECRET REQUIRED libsecret-1)
include_directories(${LIBSECRET_INCLUDE_DIRS})
add_definitions(${LIBSECRET_CFLAGS_OTHER})

# define include and source files of thor-shield
set(THOR_SHIELD_INCLUDE_LIST ${CMAKE_SOURCE_DIR}/include/thor-shield)
file(GLOB THOR_SHIELD_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/thor-shield/*.c")

list(REMOVE_ITEM THOR_SHIELD_SOURCE_FILES src/thor-shield/main.c)

add_executable(thor-shield src/thor-shield/main.c ${THOR_SHIELD_SOURCE_FILES})

add_library(thor-shield-lib ${THOR_SHIELD_SOURCE_FILES})

message(STATUS "THOR_SHIELD_INCLUDE_LIST = ${THOR_SHIELD_INCLUDE_LIST}")
target_include_directories(thor-shield PRIVATE ${THOR_SHIELD_INCLUDE_LIST})
target_include_directories(thor-shield-lib PRIVATE ${THOR_SHIELD_INCLUDE_LIST})
target_link_libraries(thor-shield ${LIBSECRET_LIBRARIES})

add_dependencies(njoritus thor-shield)
add_dependencies(njoritus thor-shield-lib)
target_link_libraries(njoritus thor-shield-lib)

add_custom_target(
  clang-tidy-thor-shield
  COMMAND
    "${CLANG_TIDY}" -p ${CMAKE_BINARY_DIR} ${THOR_SHIELD_SOURCE_FILES} --
    -I${THOR_SHIELD_INLUDE_LIST} -I${APR_INCLUDE_DIR}
    -I${LIBSECRET_INCLUDE_DIRS}
  COMMENT "Running clang-tidy for thor-shield...")

list(APPEND INCLUDES_LIST ${THOR_SHIELD_INCLUDE_LIST})
