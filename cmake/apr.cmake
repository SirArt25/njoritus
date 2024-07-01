# First, check the possible locations of the APR library and find it."

set(APR_HEADER_SUPPOSED_PATHS
    /usr/local/include/apr-1 /usr/local/include/apr-1.0 /usr/include/apr-1
    /usr/include/apr-1.0 /usr/local/apr/include/apr-1)

find_path(APR_INCLUDE_DIR apr.h PATHS ${APR_HEADER_SUPPOSED_PATHS})

set(APR_NAMES apr-1)

set(APR_SUPPOSED_PATHS /usr/lib /usr/local/lib /usr/local/apr/lib)

find_library(
  APR_LIBRARY
  NAMES ${APR_NAMES}
  PATHS ${APR_SUPPOSED_PATHS})

if(APR_LIBRARY AND APR_INCLUDE_DIR)
  set(APR_LIBRARIES ${APR_LIBRARY})
  set(APR_FOUND TRUE)
else()
  set(APR_FOUND FALSE)
endif()

if(NOT APR_FOUND)
  message(FATAL_ERROR "Could not find APR library")
endif()

if(APR_FIND_VERBOSE)
  message(STATUS "Found APR headers: ${APR_INCLUDE_DIR}")
  message(STATUS "Found APR library: ${APR_LIBRARIES}")
endif()

# Deprecated declarations.
set(NATIVE_APR_INCLUDE_PATH ${APR_INCLUDE_DIR})
get_filename_component(NATIVE_APR_LIB_PATH ${APR_LIBRARY} PATH)

mark_as_advanced(APR_LIBRARY APR_INCLUDE_DIR)

list(APPEND INCLUDES_LIST ${APR_INCLUDE_DIR})
