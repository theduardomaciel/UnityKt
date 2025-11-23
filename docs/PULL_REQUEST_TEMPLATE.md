# Pull Request: Multi-Platform Native Library Support

## Overview

This PR adds support for Linux and macOS platforms to the TextureDecoderNative library, enabling UnityKt to work on servers and non-Windows environments.

## Motivation

Currently, UnityKt only includes a Windows DLL for texture decoding, which prevents usage on:
- Linux servers (common for API deployments)
- macOS development machines
- Docker containers running Linux
- Cloud platforms (AWS Lambda, Google Cloud Functions, etc.)

## Changes

### 1. Enhanced CMakeLists.txt
- ✅ Cross-platform build configuration
- ✅ Automatic OS and architecture detection
- ✅ Uses `find_package(JNI)` for portability
- ✅ Platform-specific output directories

### 2. Improved Native Library Loader
- ✅ Automatic platform detection (OS + architecture)
- ✅ Smart library naming (lib prefix, correct extensions)
- ✅ Informative error messages
- ✅ Backward compatibility maintained

### 3. Build Scripts
- ✅ `build-linux.sh` - Linux build script
- ✅ `build-windows.bat` - Windows build script
- ✅ `build-darwin.sh` - macOS build script (universal binary)
- ✅ `build-linux-docker.sh/bat` - Cross-compilation via Docker

### 4. Directory Structure
New organization for native libraries:
```
src/main/resources/natives/
├── linux-x86_64/libTextureDecoder.so
├── windows-x86_64/TextureDecoder.dll
├── darwin-x86_64/libTextureDecoder.dylib
└── darwin-aarch64/libTextureDecoder.dylib
```

### 5. CI/CD Pipeline
- ✅ GitHub Actions workflow for automated builds
- ✅ Builds for all platforms on each PR/push
- ✅ Artifacts for easy download

### 6. Documentation
- ✅ `BUILD.md` - Comprehensive build instructions
- ✅ `QUICKSTART.md` - Quick start guide
- ✅ `LINUX_SERVER_GUIDE.md` - Server deployment guide
- ✅ `NATIVE_SETUP.md` - Technical details
- ✅ Updated README with platform support info

## Platform Support

| Platform | Architecture | Status | File |
|----------|--------------|--------|------|
| Windows | x86_64 | ✅ Tested | `TextureDecoder.dll` |
| Linux | x86_64 | ✅ Tested | `libTextureDecoder.so` |
| macOS | x86_64 | ✅ Tested | `libTextureDecoder.dylib` |
| macOS | ARM64 | ✅ Tested | `libTextureDecoder.dylib` |

## Backward Compatibility

- ✅ Existing Windows functionality unchanged
- ✅ Fallback behavior preserved
- ✅ No breaking changes to public API
- ✅ Legacy `loadLibraryFromJar(name, ext)` method deprecated but functional

## Testing

### Tested On

- [x] Windows 11 x64 with JDK 17
- [x] Ubuntu 22.04 x64 with OpenJDK 17
- [x] macOS 14 (Sonoma) on Intel
- [x] macOS 14 (Sonoma) on Apple Silicon

### Test Cases

1. ✅ Load and decode DXT1 textures
2. ✅ Load and decode DXT5 textures
3. ✅ Load and decode BC4/BC5/BC6/BC7 formats
4. ✅ Load and decode ETC1/ETC2 formats
5. ✅ Load and decode ASTC formats
6. ✅ Handle missing native library gracefully
7. ✅ Work in JAR packaging
8. ✅ Work in IDE (development mode)

## How to Test

### Build Native Libraries

```bash
# Linux
cd TextureDecoderNative
./build-linux.sh

# Windows
cd TextureDecoderNative
build-windows.bat

# macOS
cd TextureDecoderNative
./build-darwin.sh

# Or use Docker
./build-linux-docker.sh
```

### Run Tests

```bash
./gradlew test
./gradlew build
java -jar build/libs/UnityKt-*.jar
```

## Migration Guide

For existing users, no changes are required! The library will automatically:

1. Try to load from system library path (as before)
2. Fall back to platform-specific JAR resources
3. Extract and load the correct library for your platform

### For Contributors

To build for a new platform:

1. Run the appropriate build script
2. The library will be placed in `src/main/resources/natives/{platform}/`
3. Include it in your commits

## Future Work

Potential additions:
- [ ] Linux ARM64 support
- [ ] Windows ARM64 support
- [ ] Alpine Linux support (musl libc)
- [ ] Android support
- [ ] iOS support

## Checklist

- [x] Code builds on Linux
- [x] Code builds on Windows
- [x] Code builds on macOS
- [x] Tests pass on all platforms
- [x] Documentation updated
- [x] CI/CD configured
- [x] Backward compatibility verified
- [x] No breaking changes

## Related Issues

Closes #XXX (if applicable)

## Screenshots/Logs

### Successful Linux Build
```
Building TextureDecoder for Linux...
[ 20%] Building CXX object CMakeFiles/TextureDecoder.dir/lib/astc.cpp.o
[ 40%] Building CXX object CMakeFiles/TextureDecoder.dir/lib/bcn.cpp.o
...
[100%] Built target TextureDecoder
Build completed successfully!
Library output: ../src/main/resources/natives/linux-x86_64/libTextureDecoder.so
```

### Successful Runtime Load on Linux
```
Testing native library on Linux...
✅ Native library loaded successfully!
Platform detected: linux-x86_64
Library loaded from: /tmp/UnityKt_Deficuet/TextureDecoder_xxx.so
```

## Notes

- All native libraries are compiled from the same source code
- No functionality differences between platforms
- Libraries are included in the JAR, no separate distribution needed
- Automatic platform detection at runtime

## Acknowledgments

- Original `TextureDecoderNative` from [AssetStudio](https://github.com/Perfare/AssetStudio)
- Platform detection patterns inspired by other JNI libraries (LWJGL, LibGDX)

---

Ready for review! 🚀
