include(ExternalProject)
# Define telebot
ExternalProject_Add(
  telebot
  GIT_REPOSITORY https://github.com/smartnode/telebot.git
  PREFIX ${EXTERNAL_PROJECTS_DIR}/telebot
  INSTALL_COMMAND "")

ExternalProject_Get_Property(telebot source_dir binary_dir)
set(TELEBOT_INCLUDE_DIR ${source_dir}/include)
set(TELEBOT_LIB_DIR ${binary_dir})

include_directories(${TELEBOT_INCLUDE_DIR})
list(APPEND INCLUDES_LIST ${TELEBOT_INCLUDE_DIR})

# Create dependecy of njoritus from telebot
add_dependencies(njoritus telebot)
target_link_libraries(njoritus ${TELEBOT_LIB_DIR}/libtelebot.so)
