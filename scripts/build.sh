#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Import utilities.sh
source ${SCRIPT_DIR}/utilities.sh

usage() {
  echo "Usage: $0 {build|rebuild|configure|build_with_checks}"
  exit 1
}

if [ $# -eq 0 ]; then
  usage
fi

case $1 in
  build)
    build
    ;;
  build_with_checks)
    build_with_checks
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
