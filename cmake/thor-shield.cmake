# find PkgConfig and then KEYUTILS
find_package(PkgConfig REQUIRED)
find_path(KEYUTILS_INCLUDE_DIR keyutils.h)
find_library(KEYUTILS_LIBRARIES keyutils)

if(KEYUTILS_INCLUDE_DIR AND KEYUTILS_LIBRARIES)
  set(KEYUTILS_FOUND TRUE)
  message(STATUS "Found keyutils: ${KEYUTILS_LIBRARIES}")
else()
  set(KEYUTILS_FOUND FALSE)
  message(FATAL_ERROR "Could not find keyutils")
endif()

include_directories(${KEYUTILS_INCLUDE_DIR})
link_directories(${KEYUTILS_LIBRARIES})

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
target_link_libraries(thor-shield ${KEYUTILS_LIBRARIES})
target_link_libraries(thor-shield-lib ${KEYUTILS_LIBRARIES})

target_include_directories(thor-shield PRIVATE ${APR_INCLUDE_DIR})
target_include_directories(thor-shield-lib PRIVATE ${APR_INCLUDE_DIR})
target_link_libraries(thor-shield ${APR_LIBRARY})
target_link_libraries(thor-shield-lib ${APR_LIBRARY})

add_dependencies(njoritus thor-shield)
add_dependencies(njoritus thor-shield-lib)
target_link_libraries(njoritus thor-shield-lib)

list(APPEND THOR_SHIELD_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/thor-shield/main.c)
list(APPEND INCLUDES_LIST ${THOR_SHIELD_INCLUDE_LIST})
