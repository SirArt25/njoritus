if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # require at least gcc 8.1.0
  if(CMAKE_C_COMPILER_VERSION VERSION_LESS 8.1.0)
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
else()
  message(
    WARNING "You are using an unsupported compiler! Compilation has only been"
            " tested with GCC.")
endif()
