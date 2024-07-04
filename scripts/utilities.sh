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

  cmake ..

  cd -
}

pure_build() {
  cd "$BUILD_DIR"

  CORES=$(nproc)

  cmake --build . -- -j$CORES

  cd -
}

# Function to configure and build the project
build() {
  configure
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
  configure
  pure_lint
}


build_with_checks(){
  configure
  pure_lint
  pure_build
}
