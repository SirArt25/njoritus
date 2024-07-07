# find PkgConfig and then LIBSECRET
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSECRET REQUIRED libsecret-1)

include_directories(${LIBSECRET_INCLUDE_DIRS})
add_definitions(${LIBSECRET_CFLAGS_OTHER})

# define include and source files of thor-shield
set(THOR_SHIELD_INCLUDE_LIST ${CMAKE_SOURCE_DIR}/include/thor-shield)
list(APPEND THOR_SHIELD_INCLUDE_LIST ${CMAKE_SOURCE_DIR}/include/utilities)

file(GLOB_RECURSE THOR_SHIELD_SOURCE_FILES
     "${CMAKE_SOURCE_DIR}/src/thor-shield/*.c")
file(GLOB_RECURSE THOR_SHIELD_HEADER_FILES
     "${CMAKE_SOURCE_DIR}/include/thor-shield/*.h")

list(APPEND THOR_SHIELD_SOURCE_FILES
     ${CMAKE_SOURCE_DIR}/src/utilities/utilities.c)

list(REMOVE_ITEM THOR_SHIELD_SOURCE_FILES
     ${CMAKE_SOURCE_DIR}/src/thor-shield/main.c)

add_executable(thor-shield src/thor-shield/main.c ${THOR_SHIELD_SOURCE_FILES})

add_library(thor-shield-lib ${THOR_SHIELD_SOURCE_FILES})

target_include_directories(thor-shield PRIVATE ${THOR_SHIELD_INCLUDE_LIST})
target_include_directories(thor-shield-lib PRIVATE ${THOR_SHIELD_INCLUDE_LIST})
target_link_libraries(thor-shield ${LIBSECRET_LIBRARIES})
target_link_libraries(thor-shield-lib ${LIBSECRET_LIBRARIES})

target_include_directories(thor-shield PRIVATE ${APR_INCLUDE_DIR})
target_include_directories(thor-shield-lib PRIVATE ${APR_INCLUDE_DIR})
target_link_libraries(thor-shield ${APR_LIBRARY})
target_link_libraries(thor-shield-lib ${APR_LIBRARY})

add_dependencies(njoritus thor-shield)
add_dependencies(njoritus thor-shield-lib)
target_link_libraries(njoritus thor-shield-lib)

list(APPEND THOR_SHIELD_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/thor-shield/main.c)
list(APPEND INCLUDES_LIST ${THOR_SHIELD_INCLUDE_LIST})
