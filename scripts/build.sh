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

# Function to configure and build the project
build() {
  # Create the build directory if it doesn't exist
  if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
  fi

  # Navigate to the build directory
  cd "$BUILD_DIR"

  # Run CMake to configure the project
  cmake ..

  # Build the project using the generated Makefile
  cmake --build . -- -j12

  # Return to the root directory
  cd ..
}

# Display usage information
usage() {
  echo "Usage: $0 {build|clean|rebuild}"
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
  rebuild)
    clean
    build
    ;;
  *)
    usage
    ;;
esac
