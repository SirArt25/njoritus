function(lint_files target_name file_list)
  # Creates linting commands for each file in the list
  foreach(src IN LISTS ${file_list})
    add_custom_command(
      TARGET ${target_name}
      COMMAND ${CMAKE_COMMAND} -E echo "${target_name} linting ${src}"
      COMMAND "${CLANG_TIDY}" -p ${CMAKE_BINARY_DIR} ${src} 2> ${DEV_NULL})
  endforeach()
endfunction()

function(create_linting_target target_name source_list_files_name
         header_list_files_name)
  add_custom_target(${target_name} COMMENT "Running ${target_name}...")
  lint_files(${target_name} ${header_list_files_name})
  lint_files(${target_name} ${source_list_files_name})
endfunction()

# create clang-tidy targets
create_linting_target(clang-tidy-njoritus NJORITUS_SOURCE_FILES
                      NJORITUS_HEADER_FILES)
create_linting_target(clang-tidy-thor-shield THOR_SHIELD_SOURCE_FILES
                      THOR_SHIELD_HEADER_FILES)

# for making linting ok
add_dependencies(clang-tidy-njoritus telebot)
