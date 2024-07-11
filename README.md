# njoritus
njoritus is a telegram bot for weather service.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Build](#build)
- [Docker](#docker)
- [Usage](#usage)
- [Tests](#tests)
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
docker build --build-arg DOCKER_DIR_ARG=<relative/path/to/njoritus>/docker -t <image-name> -f <path/to/njoritus/docker>/njoritus.Dockerfile .
```

### Running the Docker Container

Run the Docker container:
```bash
docker run -it -d --cap-add=SYS_ADMIN --privileged <image-name>
```

## Usage

After building the njoritus, you can run the executables located in `/build/bin/`. To run the njortius, you first need to obtain a token from Telegram. For security purposes, the njoritus utilizes keyutils. You must store the Telegram token in keyutils under the name "mjorn". This can be accomplished with the following command:
```bash
.<path/to/njoritus/build/bin>/thor-shield --enc <token-folder> mjorn
```
After running thor-shield, you can run the njortius:
```bash
.<path/to/njoritus/build/bin>/njoritus
```

## Tests
To run tests, you need ctest. Use the following commands to run the tests:
```bash
cd <path/to/njoritus/build/tests>
ctest
```

## License
This project is licensed under the GPLv3 License - see the LICENSE file for details.
