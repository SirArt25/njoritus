#!/usr/bin/env bash

set -e

keyctl new_session
keyctl link @u @s


exit 0
