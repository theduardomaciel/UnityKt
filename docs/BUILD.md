# Building TextureDecoder Native Libraries

This document provides instructions for building the TextureDecoder native library for different platforms.

## Prerequisites

### All Platforms
- CMake 3.8 or higher
- C++ compiler with C++14 support
- JDK 11 or higher (with JNI headers)

### Platform-Specific Requirements

#### Linux
- GCC or Clang
- Development tools: `sudo apt-get install build-essential cmake`
- JDK development package: `sudo apt-get install default-jdk`

#### Windows
- Visual Studio 2022 (or 2019/2017) with C++ development tools
- CMake (can be installed via Visual Studio Installer)
- JDK 17 or higher

#### macOS
- Xcode Command Line Tools: `xcode-select --install`
- CMake: `brew install cmake`
- JDK: `brew install openjdk@17`

## Building

### Quick Build Scripts

Navigate to the `TextureDecoderNative` directory and run the appropriate build script:

#### Linux
```bash
cd TextureDecoderNative
chmod +x build-linux.sh
./build-linux.sh
```

This will create `libTextureDecoder.so` in `src/main/resources/natives/linux-x86_64/`

#### Windows
```cmd
cd TextureDecoderNative
build-windows.bat
```

This will create `TextureDecoder.dll` in `src/main/resources/natives/windows-x86_64/`

#### macOS
```bash
cd TextureDecoderNative
chmod +x build-darwin.sh
./build-darwin.sh
```

This will create `libTextureDecoder.dylib` in `src/main/resources/natives/darwin-aarch64/` (or `darwin-x86_64/` depending on your architecture)

### Manual Build

If you prefer to build manually or need custom configuration:

```bash
cd TextureDecoderNative

# Create build directory
mkdir build
cd build

# Configure CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . --config Release
```

The output will be placed in the appropriate `src/main/resources/natives/{platform}/` directory.

## Cross-Compilation

### Building for Multiple Architectures on macOS

To create a universal binary for both Intel and Apple Silicon:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
cmake --build . --config Release
```

### Cross-Compiling for Linux from Another Platform

Use a Docker container with a Linux environment:

```bash
docker run --rm -v $(pwd):/workspace -w /workspace/TextureDecoderNative \
    ubuntu:22.04 \
    bash -c "apt-get update && apt-get install -y build-essential cmake default-jdk && ./build-linux.sh"
```

## Library Structure

After building, your resource structure should look like this:

```
src/main/resources/natives/
├── linux-x86_64/
│   └── libTextureDecoder.so
├── windows-x86_64/
│   └── TextureDecoder.dll
├── darwin-x86_64/
│   └── libTextureDecoder.dylib
└── darwin-aarch64/
    └── libTextureDecoder.dylib
```

## Platform Detection

The `NativeUtils.kt` class automatically detects the platform and loads the appropriate library:

- **Linux**: Looks for `libTextureDecoder.so` in `natives/linux-x86_64/`
- **Windows**: Looks for `TextureDecoder.dll` in `natives/windows-x86_64/`
- **macOS Intel**: Looks for `libTextureDecoder.dylib` in `natives/darwin-x86_64/`
- **macOS ARM**: Looks for `libTextureDecoder.dylib` in `natives/darwin-aarch64/`

## Troubleshooting

### CMake can't find JNI

Set the `JAVA_HOME` environment variable:

```bash
# Linux/macOS
export JAVA_HOME=/path/to/jdk

# Windows
set JAVA_HOME=C:\Program Files\Java\jdk-17
```

### Build fails on Linux with "jni.h not found"

Install JDK development package:
```bash
sudo apt-get install default-jdk
```

### Library loads but functions are not found

Make sure the JNI header file (`io_github_deficuet_unitykt_extension_TextureDecoder.h`) is up to date. Regenerate it if needed:

```bash
cd TextureDecoderNative
javac -h ./ ../src/main/java/io/github/deficuet/unitykt/extension/TextureDecoder.java
```

### UnsatisfiedLinkError: no TextureDecoder in java.library.path

This error means the library couldn't be loaded from the JAR resources. Verify:

1. The library was built for your platform
2. The library file is present in `src/main/resources/natives/{your-platform}/`
3. The library file has the correct name (with proper prefix/suffix)
4. The JAR/classpath includes the resources directory