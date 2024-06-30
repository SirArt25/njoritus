# First, check the possible locations 
# of the APR library and find it."

set(APR_HEADER_SUPPOSED_PATHS
    /usr/local/include/apr-1
    /usr/local/include/apr-1.0
    /usr/include/apr-1
    /usr/include/apr-1.0
    /usr/local/apr/include/apr-1
)


find_path(APR_INCLUDE_DIR apr.h
        PATHS ${APR_HEADER_SUPPOSED_PATHS}
)

set(APR_NAMES
    apr-1
)

set(APR_SUPPOSED_PATHS
    /usr/lib
    /usr/local/lib
    /usr/local/apr/lib
)

find_library(APR_LIBRARY
        NAMES ${APR_NAMES}
        PATHS ${APR_SUPPOSED_PATHS}
)

if (APR_LIBRARY AND APR_INCLUDE_DIR)
    set(APR_LIBRARIES ${APR_LIBRARY})
    set(APR_FOUND TRUE)
else ()
    set(APR_FOUND FALSE)
endif ()


if (NOT APR_FOUND)
    MESSAGE(FATAL_ERROR "Could not find APR library")
endif()


if (APR_FIND_VERBOSE)
    MESSAGE(STATUS "Found APR headers: ${APR_INCLUDE_DIR}")
    MESSAGE(STATUS "Found APR library: ${APR_LIBRARIES}")
endif ()


# Deprecated declarations.
SET (NATIVE_APR_INCLUDE_PATH ${APR_INCLUDE_DIR} )
GET_FILENAME_COMPONENT (NATIVE_APR_LIB_PATH ${APR_LIBRARY} PATH)

MARK_AS_ADVANCED(
        APR_LIBRARY
        APR_INCLUDE_DIR
)