#!/bin/bash
# Generate JNI header from TextureDecoder.java
# Requires Gradle build to compile Kotlin dependencies first

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

echo "Building project with Gradle..."
cd "$PROJECT_ROOT"
./gradlew compileJava compileKotlin

echo "Generating JNI header..."
cd "$SCRIPT_DIR"
javac -h ./ -cp "../build/classes/java/main:../build/classes/kotlin/main" \
  ../src/main/java/io/github/deficuet/unitykt/extension/TextureDecoder.java

echo "[SUCCESS] Header generated: io_github_deficuet_unitykt_extension_TextureDecoder.h"
