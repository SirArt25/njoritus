include(ExternalProject)

# Define telebot
ExternalProject_Add(
  telebot
  GIT_REPOSITORY https://github.com/smartnode/telebot.git
  PREFIX ${EXTERNAL_PROJECTS_DIR}/telebot
  INSTALL_COMMAND "")

ExternalProject_Get_Property(telebot source_dir binary_dir)

set(ADDITIONAL_CLEAN_FILES "${EXTERNAL_PROJECTS_DIR}/telebot")
set(TELEBOT_INCLUDE_DIR ${source_dir}/include)
set(TELEBOT_LIB_DIR ${binary_dir})

include_directories(${TELEBOT_INCLUDE_DIR})
list(APPEND INCLUDES_LIST ${TELEBOT_INCLUDE_DIR})

# Create dependecy of njoritus from telebot
add_custom_target(
  copy-telebot-libs
  COMMAND ${CMAKE_COMMAND} -E copy ${TELEBOT_LIB_DIR}/libtelebot.so
          ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
  COMMAND ${CMAKE_COMMAND} -E copy ${TELEBOT_LIB_DIR}/libtelebot.so.4.7.0
          ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
add_dependencies(copy-telebot-libs telebot)
add_dependencies(njoritus copy-telebot-libs)
target_link_libraries(njoritus ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libtelebot.so)
