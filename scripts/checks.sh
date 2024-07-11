#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Import utilities.sh
source ${SCRIPT_DIR}/utilities.sh


# Display usage information
usage() {
  echo "Usage: $0 {lint}"
  exit 1
}

if [ $# -eq 0 ]; then
  usage
fi

case $1 in
  lint)
    lint
    ;;
  *)
    usage
    ;;
esac
