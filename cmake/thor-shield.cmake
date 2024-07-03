find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBSECRET REQUIRED libsecret-1)

include_directories(${LIBSECRET_INCLUDE_DIRS})

set(THOR_SHIELD_INLUDE_LIST ${INCLUDES_LIST}/thor-shield)

add_executable(thor-shield src/thor-shield/main.c src/thor-shield/enc.c
                           src/thor-shield/dec.c src/thor-shield/mjolnir.c)
target_include_directories(thor-shield PUBLIC ${THOR_SHIELD_INLUDE_LIST})

target_link_libraries(thor-shield ${LIBSECRET_LIBRARIES})
add_definitions(${LIBSECRET_CFLAGS_OTHER})
