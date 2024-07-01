#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Import utilities.sh
source ${SCRIPT_DIR}/utilities.sh

if [ $# -eq 0 ]; then
  usage
fi

case $1 in
  build)
    build
    ;;
  clean)
    clean
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
