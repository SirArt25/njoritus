#!/usr/bin/env bash

set -e

echo "Installing clang-tidy-14.0.6..."


TMP_DIR=$(mktemp -d -t clang-tidy-14-XXXXXXXXXX)

echo "${TMP_DIR}"
cd "${TMP_DIR}"


# Add LLVM repository and install clang-tidy 14
wget -O - "https://apt.llvm.org/llvm-snapshot.gpg.key" | apt-key add -
add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main"
apt-get update
apt-get install -y clang-tidy-14

# Set clang-tidy 14 as the default
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-14 100


rm -rf "${TMP_DIR}"
