#!/bin/bash
set -e

# Define the BUILD_DIR
BUILD_DIR="${SCRIPT_DIR}/../build"

# Function to clean the build directory
clean() {
  if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing build directory."
    rm -rf "$BUILD_DIR"
  else
    echo "Build directory does not exist, nothing to clean."
  fi
}

# configure cmake
configure() {
  if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
  fi

  cd "$BUILD_DIR"

  cmake ..

  cd -
}

pure_build() {
  cd "$BUILD_DIR"

  cmake --build . -- -j12

  cd -
}

# Function to configure and build the project
build() {
  configure
  pure_build
}


pure_lint() {
  cd "$BUILD_DIR"
  cmake --build . --target clang-tidy-njoritus
  cd -
}


lint() {
  configure
  pure_lint
}


build_with_checks(){
  configure
  pure_lint
  pure_build
}
