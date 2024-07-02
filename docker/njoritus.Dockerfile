FROM ubuntu:24.04
SHELL ["/bin/bash", "-c"]
RUN echo 'APT::Install-Suggests "0";' >> /etc/apt/apt.conf.d/00-docker
RUN echo 'APT::Install-Recommends "0";' >> /etc/apt/apt.conf.d/00-docker


ARG DOCKER_DIR_ARG
ENV DOCKER_DIR=${DOCKER_DIR_ARG}

RUN DEBIAN_FRONTEND=noninteractive \
  apt update \
  && apt install -y python3 \
    wget \
    build-essential \
    libssl-dev \
    libapr1 \
    libapr1-dev \
    curl \
    ca-certificates \
    python3-pip \
    python3-dev  \
    gnupg \
    gnupg2 \
    gnupg1 \
    lsb-release \
    software-properties-common \
  && rm -rf /var/lib/apt/lists/*


# Add LLVM repository and install clang-tidy 14
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main" && \
    apt-get update && \
    apt-get install -y clang-tidy-14

# Set clang-tidy 14 as the default
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-14 100

# Verify installation
RUN clang-tidy --version

WORKDIR /workspace

# Copy cmake_install.sh and install cmake
COPY ${DOCKER_DIR}/scripts/cmake_install.sh /workspace/env_scripts/cmake_install.sh
RUN chmod +x /workspace/env_scripts/cmake_install.sh
RUN CMAKE_VERSION=3.22.1 /workspace/env_scripts/cmake_install.sh
