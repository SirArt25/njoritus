find_path(CUNIT_INCLUDE_DIR NAMES CUnit/Basic.h)
find_library(CUNIT_LIBRARY NAMES cunit)

if(CUNIT_INCLUDE_DIR AND CUNIT_LIBRARY)
  set(CUNIT_FOUND TRUE)
else()
  set(CUNIT_FOUND FALSE)
endif()

if(NOT CUNIT_FOUND)
  message(FATAL_ERROR "CUnit not found!")
endif()

set(CUNIT_LIBRARIES ${CUNIT_LIBRARY})
set(CUNIT_INCLUDE_DIRS ${CUNIT_INCLUDE_DIR})
mark_as_advanced(CUNIT_INCLUDE_DIR CUNIT_LIBRARY)
set(TEST_SOURCE_DIR "${CMAKE_SOURCE_DIR}/tests")

add_executable(
  njoritus-test
  ${TEST_SOURCE_DIR}/njoritus-test.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/core.c
  ${CMAKE_SOURCE_DIR}/src/utilities/utilities.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/query_classifier.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/regex.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/semantic_checkers/cordinate_checker.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/query_classifier_config.c
  ${CMAKE_SOURCE_DIR}/src/njoritus/regex_wrapper.c)

add_executable(odin-gaze-test ${TEST_SOURCE_DIR}/odin-gaze-test.c)

add_executable(thor-shield-test ${TEST_SOURCE_DIR}/thor-shield-test.c)

target_link_libraries(njoritus-test ${CUNIT_LIBRARIES})
target_link_libraries(odin-gaze-test ${CUNIT_LIBRARIES})
target_link_libraries(thor-shield-test ${CUNIT_LIBRARIES})

target_link_libraries(njoritus-test ${APR_LIBRARY})

target_include_directories(
  njoritus-test
  PRIVATE ${CUNIT_INCLUDE_DIRS}
  PRIVATE ${APR_INCLUDE_DIR}
  PRIVATE ${INCLUDES_LIST})

target_include_directories(
  odin-gaze-test
  PRIVATE ${CUNIT_INCLUDE_DIRS}
  PRIVATE ${INCLUDES_LIST})

target_include_directories(
  thor-shield-test
  PRIVATE ${CUNIT_INCLUDE_DIRS}
  PRIVATE ${INCLUDES_LIST}
  PRIVATE ${THOR_SHIELD_INCLUDE_LIST})

add_dependencies(odin-gaze-test odin-gaze-build)
target_link_libraries(odin-gaze-test ${ODIN_GAZE_LIB})

add_dependencies(thor-shield-test thor-shield-lib)
target_link_libraries(thor-shield-test thor-shield-lib)

add_test(NAME njoritus-test COMMAND njoritus-test)
add_test(NAME odin-gaze-test COMMAND odin-gaze-test)
add_test(NAME thor-shield-test COMMAND thor-shield-test)
