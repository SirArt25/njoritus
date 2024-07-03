FROM --platform=linux/amd64  ubuntu:24.04
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
    gnupg \
    gnupg2 \
    gnupg1 \
    lsb-release \
    software-properties-common \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY ${DOCKER_DIR}/scripts/clang-tidy14_install.sh /workspace/env_scripts/clang-tidy14_install.sh
RUN chmod +x /workspace/env_scripts/clang-tidy14_install.sh
RUN /workspace/env_scripts/clang-tidy14_install.sh

# Verify installation
RUN clang-tidy --version


# Copy cmake_install.sh and install cmake
COPY ${DOCKER_DIR}/scripts/cmake_install.sh /workspace/env_scripts/cmake_install.sh
RUN chmod +x /workspace/env_scripts/cmake_install.sh
RUN CMAKE_VERSION=3.22.1 /workspace/env_scripts/cmake_install.sh


# Add dependency of telebot
RUN DEBIAN_FRONTEND=noninteractive \
  apt update \
  && apt install -y libcurl4-openssl-dev \
    libjson-c-dev \
  && rm -rf /var/lib/apt/lists/*
