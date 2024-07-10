#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Import utilities.sh
source ${SCRIPT_DIR}/utilities.sh

usage() {
  echo "Usage: $0 {build|rebuild|configure|build_with_checks|"
  echo "             configure_with_test|build_with_test|"
  echo "             rebuild_with_test|"
  echo "             build_with_checks_and_tests|}"
  exit 1
}

if [ $# -eq 0 ]; then
  usage
fi

case $1 in
  build)
    build false
    ;;
  build_with_checks)
    build_with_checks false
    ;;
  build_with_test)
    build true
    ;;
  build_with_checks_and_tests)
    build_with_checks true
    ;;
  configure)
    configure false
    ;;
  configure_with_test)
    configure true
    ;;
  rebuild)
    clean
    build false
    ;;
  rebuild_with_test)
    clean
    build true
    ;;
  *)
    usage
    ;;
esac
