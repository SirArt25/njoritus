#!/bin/bash
set -e

# Define the BUILD_DIR
BUILD_DIR="${SCRIPT_DIR}/../build"

# configure cmake
configure() {
  if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
  fi
  cd "$BUILD_DIR"

  local create_tests=$1

  if [ "$create_tests" = true ]; then
    cmake -DENABLE_TESTS=ON  ..
  else
    cmake -DENABLE_TESTS=OFF  ..
  fi

  cd -
}

pure_build() {
  cd "$BUILD_DIR"

  CORES=$(nproc)

  cmake  --build . -- -j$CORES

  cd -
}

# Function to configure and build the project
build() {
  local create_tests=$1
  # Add build commands here

  configure "$create_tests"
  pure_build
}


clean() {
  if [ -d "$BUILD_DIR" ]; then
    cd "$BUILD_DIR"

    cmake --build . --target clean

    cd -
  else
    echo "Build directory does not exist, nothing to clean."
  fi
}

rmdir-build-dir() {
  if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
  fi
}

clean-all() {
  clean
  rmdir-build-dir
}

pure_lint() {
  cd "$BUILD_DIR"
  cmake --build . --target clang-tidy-thor-shield
  cmake --build . --target clang-tidy-njoritus
  cd -
}


lint() {
  local create_tests=$1
  configure "$create_tests"
  pure_lint
}


build_with_checks(){
  local create_tests=$1
  configure "$create_tests"
  pure_lint
  pure_build
}
