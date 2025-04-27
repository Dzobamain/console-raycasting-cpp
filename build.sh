#!/bin/bash

OUT="cr"

SRC=$(find . -name "*.c")

if gcc $SRC -o $OUT; then
    echo "Build complete. Executable is: $OUT"
else
    echo "❌ Build failed."
fi