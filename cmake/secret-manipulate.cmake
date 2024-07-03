find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBSECRET REQUIRED libsecret-1)

include_directories(${LIBSECRET_INCLUDE_DIRS})

target_link_libraries(njoritus ${LIBSECRET_LIBRARIES})
add_definitions(${LIBSECRET_CFLAGS_OTHER})
