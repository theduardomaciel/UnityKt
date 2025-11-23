#!/bin/bash
# Build script for macOS

set -e

echo "Building TextureDecoder for macOS..."

# Create build directory
BUILD_DIR="build-darwin"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure CMake
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON

# Build
cmake --build . --config Release

echo "Build completed successfully!"
echo "Library output: ../src/main/resources/natives/darwin-aarch64/libTextureDecoder.dylib"
