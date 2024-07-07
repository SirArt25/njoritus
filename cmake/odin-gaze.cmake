set(ODIN_GAZE_PATH "${CMAKE_SOURCE_DIR}/odin-gaze")

add_custom_target(
  odin-gaze-build ALL
  COMMAND cargo build --release
  WORKING_DIRECTORY ${ODIN_GAZE_PATH}
  COMMENT "Building Rust project")

set(ODIN_GAZE_RELEASE_PATH "${ODIN_GAZE_PATH}/target/release")

# Link the Rust library to your CMake project
set(ODIN_GAZE_LIB "${ODIN_GAZE_RELEASE_PATH}/libodingaze.so")

list(APPEND ADDITIONAL_CLEAN_FILES "${ODIN_GAZE_PATH}/target")
list(APPEND ADDITIONAL_CLEAN_FILES "${ODIN_GAZE_PATH}/Cargo.lock")
add_dependencies(njoritus odin-gaze-build)
target_link_libraries(njoritus ${ODIN_GAZE_LIB})
