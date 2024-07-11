find_program(CLANG_TIDY "clang-tidy")

if(NOT CLANG_TIDY)
  message(FATAL_ERROR "clang-tidy not found!")
endif()
