#!/bin/bash

# Exit on error
set -e
# Set project and build directories
PROJECT_DIR="$(pwd)"
BUILD_DIR="$PROJECT_DIR/bin/build"
EXE_DIR="$PROJECT_DIR/bin"
EXECUTABLE="$EXE_DIR/app"  
CMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

# Optional: set VCPKG_ROOT if not already set
: "${VCPKG_ROOT:="$PROJECT_DIR/vcpkg"}"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Configure CMake
cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" \
  -G "Ninja" \
  -DCMAKE_TOOLCHAIN_FILE="$CMAKE_TOOLCHAIN_FILE" \
  -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build "$BUILD_DIR" --config Release

# Run the executable if it exists
if [[ -x "$EXECUTABLE" ]]; then
  echo "Running: $EXECUTABLE"
  "$EXECUTABLE"
else
  echo "ERROR: Executable not found at $EXECUTABLE"
fi