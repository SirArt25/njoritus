find_program(CLANG_TIDY "clang-tidy")

if(NOT CLANG_TIDY)
  message(FATAL_ERROR "clang-tidy not found!")
endif()

add_custom_target(
  clang-tidy-njoritus
  COMMAND "${CLANG_TIDY}" -p ${CMAKE_BINARY_DIR} ${SOURCE_FILES} --
          -I${CMAKE_SOURCE_DIR}/include -I${APR_INCLUDE_DIR}
  COMMENT "Running clang-tidy...")
