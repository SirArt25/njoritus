#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Import utilities.sh
source ${SCRIPT_DIR}/utilities.sh

usage() {
  echo "Usage: $0 {clean|clean-all}"
  exit 1
}

if [ $# -eq 0 ]; then
  usage
fi

case $1 in
  clean)
    clean
    ;;
  clean-all)
    clean-all
    ;;
  *)
    usage
    ;;
esac
