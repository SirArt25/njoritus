#!/bin/bash
set -e
# Define the build directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
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

# Function to configure and build the project
build() {
  configure

  cd "$BUILD_DIR"

  cmake --build . -- -j12

  cd -
}

# Display usage information
usage() {
  echo "Usage: $0 {build|clean|rebuild|configure}"
  exit 1
}

# Check for command line arguments
if [ $# -eq 0 ]; then
  usage
fi

# Handle the command line arguments
case $1 in
  build)
    build
    ;;
  clean)
    clean
    ;;
  configure)
    configure
    ;;
  rebuild)
    clean
    build
    ;;
  *)
    usage
    ;;
esac
