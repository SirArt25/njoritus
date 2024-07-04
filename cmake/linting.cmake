function(create_linting_target target_name SOURCE_LIST_FILES)
  add_custom_target(${target_name} COMMENT "Running ${target_name}...")

  foreach(src IN LISTS SOURCE_LIST_FILES)
    add_custom_command(
      TARGET ${target_name}
      COMMAND ${CMAKE_COMMAND} -E echo "${target_name} linting ${src}"
      COMMAND "${CLANG_TIDY}" -p ${CMAKE_BINARY_DIR} ${src} 2> ${DEV_NULL})
  endforeach()
endfunction()

create_linting_target(clang-tidy-njoritus ${SOURCE_FILES})
create_linting_target(clang-tidy-thor-shield ${THOR_SHIELD_SOURCE_FILES})
# for making linting ok
add_dependencies(clang-tidy-njoritus telebot)
