#!/bin/bash

# Usage: ./build.sh file-without-extension

gcc -g "$1".c -o $1 $(pkg-config --cflags --libs gobject-2.0)
