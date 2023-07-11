#!/bin/bash

# Usage: ./build.sh

gcc -g main.c tdouble.c -o 06-type-decl-separate-files $(pkg-config --cflags --libs gobject-2.0)
