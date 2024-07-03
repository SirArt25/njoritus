set(EXTERNAL_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/external_projects)
# EXTERNAL_PROJECTS_SUB_DIRS
file(
  GLOB ALL_ENTRIES
  RELATIVE ${EXTERNAL_PROJECTS_DIR}
  ${EXTERNAL_PROJECTS_DIR}/*/)

set(EXTERNAL_PROJECTS_SUB_DIRS "")

foreach(entry IN LISTS ALL_ENTRIES)
  if(IS_DIRECTORY "${EXTERNAL_PROJECTS_DIR}/${entry}")
    list(APPEND EXTERNAL_PROJECTS_SUB_DIRS "${entry}")
  endif()
endforeach()

message(STATUS "EXTERNAL_PROJECTS_SUB_DIRS = ${EXTERNAL_PROJECTS_SUB_DIRS}")
# Creating a script to remove all subdirectories
file(
  WRITE
  ${CMAKE_BINARY_DIR}/utility_cmakes/remove_external_projects_sub_dirs.cmake
  "set(EXTERNAL_PROJECTS_SUB_DIRS ${EXTERNAL_PROJECTS_SUB_DIRS})
set(EXTERNAL_PROJECTS_DIR ${EXTERNAL_PROJECTS_DIR})
foreach(subdir IN LISTS EXTERNAL_PROJECTS_SUB_DIRS)
    file(REMOVE_RECURSE \${EXTERNAL_PROJECTS_DIR}/\${subdir})
endforeach()
")

add_custom_target(
  remove_external_projects
  COMMAND
    ${CMAKE_COMMAND} -P
    ${CMAKE_BINARY_DIR}/utility_cmakes/remove_external_projects_sub_dirs.cmake
  COMMENT "Removing all subdirectories in ${EXTERNAL_PROJECTS_DIR}")

add_custom_target(
  clean_all
  COMMAND ${CMAKE_COMMAND} --build . --target clean
  COMMENT "Cleaning all targets")

add_dependencies(clean_all remove_external_projects)
