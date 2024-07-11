# njoritus
njoritus is a telegram bot for weather service.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Build](#build)
- [Docker](#docker)
- [Usage](#usage)
- [License](#license)

## Prerequisites

The following software and tools are required to run and build njoritus:

- **Rust** (latest)
- **Python 3**
- **wget**
- **build-essential**
- **libssl-dev**
- **libapr1**
- **libapr1-dev**
- **curl**
- **ca-certificates**
- **gnupg**, **gnupg1**, **gnupg2**
- **lsb-release**
- **software-properties-common**
- **clang-tidy**
- **cmake** (version 3.22.1)
- **libcurl4-openssl-dev**
- **libjson-c-dev**
- **git**
- **pkg-config**
- **pass**
- **keyutils**, **libkeyutils-dev**
- **libcunit1**, **libcunit1-doc**, **libcunit1-dev**

## Build


### Cloning the Repository
Start by cloning the repository to your local machine:

```bash
   git clone git@github.com:SirArt25/njoritus.git
   cd njoritus
   ```
### Building the njoritus
Instead of using CMake directly, you can utilize the provided script to build or rebuild the njoritus:

- To build the njoritus:
  ```bash
  bash scripts/build.sh build
  ```

- To rebuild the njoritus:
  ```bash
  bash scripts/build.sh rebuild
  ```

- To build the njoritus with checks:
  ```bash
  bash scripts/build.sh build_with_checks
  ```

- To rebuild the njoritus with tests:
  ```bash
  bash scripts/build.sh rebuild_with_test
  ```

- To build the njoritus with checks and tests:
  ```bash
  bash scripts/build.sh build_with_checks_and_tests
  ```

### Cleaning the njoritus

- To clean the njoritus and remove all generated files:
    ```bash
    bash scripts/clean.sh clean
    ```

- To clean all external projects and libs along with the generated files:
    ```bash
    bash scripts/clean.sh clean-all
    ```

## Docker

### Building the Docker Image

Build the Docker image:
```bash
docker build --build-arg DOCKER_DIR_ARG=<relative/path/to/project/docker> -t <image-name> -f <relative/path/to/project/docker/njoritus.Dockerfile> .
```

### Running the Docker Container

Run the Docker container:
```bash
docker run -it -d --cap-add=SYS_ADMIN --privileged <image-name>
```
