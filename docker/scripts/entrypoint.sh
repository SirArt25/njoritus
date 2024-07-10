#!/bin/bash

keyctl new_session  > /dev/null
keyctl link @u @s  > /dev/null


exit 0
