#!/usr/bin/env bash

set -e

echo "Installing CMake..."
mkdir -p /opt/cmake

architecture=$(dpkg --print-architecture)
echo $architecture
case "${architecture}" in
    linux/arm/v5|linux/arm/v6|linux/arm/v7|linux/arm64|arm/v5|arm/v6|arm/v7|arm64)
        ARCH=aarch64 ;;
    linux/amd64|linux/i386|amd64|i386)
        ARCH=x86_64 ;;
    *)
        echo "Unsupported architecture ${architecture}."
        exit 1
        ;;
esac

echo ${CMAKE_VERSION}
CMAKE_BINARY_NAME="cmake-${CMAKE_VERSION}-linux-${ARCH}.sh"
CMAKE_CHECKSUM_NAME="cmake-${CMAKE_VERSION}-SHA-256.txt"
TMP_DIR=$(mktemp -d -t cmake-XXXXXXXXXX)

echo "${TMP_DIR}"
cd "${TMP_DIR}"

curl -sSL "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/${CMAKE_BINARY_NAME}" -O
curl -sSL "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/${CMAKE_CHECKSUM_NAME}" -O

#sha256sum -c --ignore-missing "${CMAKE_CHECKSUM_NAME}"
sh "${CMAKE_BINARY_NAME}" --prefix=/opt/cmake --skip-license

ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
ln -s /opt/cmake/bin/ctest /usr/local/bin/ctest


rm -rf "${TMP_DIR}"
