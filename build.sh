#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Compiler Warning Flags
FLAGS="-Wall -Wextra -Wconversion -pedantic -Werror"

# Detect Operating System
OS="$(uname -s)"
echo "[INFO]: Detected operating system: $OS"

# Detect available C++ compiler
COMPILER=""
if command -v clang++ &> /dev/null; then
    COMPILER="clang++"
elif command -v g++ &> /dev/null; then
    COMPILER="g++-14"
else
    echo "[ERROR]: No C++ compiler (clang++ or g++) found!"
    exit 1
fi

echo "[INFO]: Using compiler: $COMPILER"

# Create output directory if necessary
mkdir -p bin

# Compile
echo "[INFO]: Building...."
$COMPILER $FLAGS -std=c++23 src/*.cpp -Iincludes -o bin/Tundra

echo "[INFO]: Build success!"
echo "[INFO]: Running...."

# Execute the built binary
./bin/Tundra
