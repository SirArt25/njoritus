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
  && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace


copy ${DOCKER_DIR}/scripts/cmake_install.sh /cmake_install.sh
