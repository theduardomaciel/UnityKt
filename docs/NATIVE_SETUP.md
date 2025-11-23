# Cross-Platform Native Library Setup - Summary

## What Was Done

This project has been updated to support native texture decoding on multiple platforms (Linux, Windows, and macOS).

### Changes Made

1. **CMakeLists.txt** - Enhanced for cross-platform compilation
   - Automatic OS and architecture detection
   - Uses `find_package(JNI)` instead of hard-coded JDK paths
   - Outputs libraries to platform-specific directories

2. **NativeUtils.kt** - Improved native library loader
   - Automatic platform detection (OS + architecture)
   - Loads the correct library from `resources/natives/{platform}/`
   - Provides informative error messages

3. **TextureDecoder.java** - Updated library loading
   - Better error handling with detailed messages
   - Falls back to JAR-embedded libraries automatically

4. **Directory Structure** - New organization
   ```
   src/main/resources/natives/
   ├── linux-x86_64/
   ├── windows-x86_64/
   ├── darwin-x86_64/
   └── darwin-aarch64/
   ```

5. **Build Scripts** - Platform-specific build automation
   - `build-linux.sh` - Linux build
   - `build-windows.bat` - Windows build
   - `build-darwin.sh` - macOS build (universal binary)
   - `build-linux-docker.sh/bat` - Cross-compile for Linux using Docker

6. **Documentation**
   - `BUILD.md` - Comprehensive build instructions
   - `TextureDecoderNative/README.md` - Native library documentation
   - Updated main `README.md` with platform support info

7. **CI/CD**
   - `.github/workflows/build-natives.yml` - GitHub Actions workflow
   - Automatically builds for all platforms on push/PR

## How to Build for Linux

### Option 1: On a Linux Machine

```bash
cd TextureDecoderNative
chmod +x build-linux.sh
./build-linux.sh
```

The library will be output to: `src/main/resources/natives/linux-x86_64/libTextureDecoder.so`

### Option 2: Using Docker (from Windows/macOS)

```bash
cd TextureDecoderNative
chmod +x build-linux-docker.sh
./build-linux-docker.sh
```

Or on Windows:
```cmd
cd TextureDecoderNative
build-linux-docker.bat
```

### Option 3: Using GitHub Actions

Push your changes to GitHub, and the CI/CD pipeline will automatically build for all platforms. Download the artifacts from the Actions tab.

## How It Works

1. **At Build Time**: CMake compiles the C++ code into platform-specific native libraries
2. **At Package Time**: Gradle includes all native libraries in the JAR under `resources/natives/`
3. **At Runtime**: 
   - `TextureDecoder` static initializer tries to load the library
   - If not found in system path, `NativeUtils` detects the platform
   - Extracts the correct library from JAR to temp directory
   - Loads the library using `System.load()`

## Verifying the Setup

After building, check that libraries exist:

```bash
# Linux
ls -lh src/main/resources/natives/linux-x86_64/

# Expected: libTextureDecoder.so
```

Then test by running your Kotlin application:

```bash
./gradlew run
```

The application should load without `UnsatisfiedLinkError`.

## Next Steps

### For Local Development

1. Build the native library for your platform
2. Run/test your Kotlin application
3. The library will be automatically loaded

### For Deployment

1. Build native libraries for all target platforms
2. Include them all in your JAR
3. Distribute the single JAR - it will work on all platforms

### For Contributing Upstream

1. Test on your platform
2. Commit all changes including the new native libraries
3. Create a pull request with:
   - Description of changes
   - Platform support matrix
   - Build instructions
   - Test results

## Troubleshooting

### Error: CMake cannot find JNI

Set `JAVA_HOME`:
```bash
export JAVA_HOME=/path/to/jdk  # Linux/macOS
set JAVA_HOME=C:\path\to\jdk   # Windows
```

### Error: UnsatisfiedLinkError at runtime

Check that:
1. The native library exists in `src/main/resources/natives/{your-platform}/`
2. The library has the correct name (see `NativeUtils.getLibraryFileName()`)
3. Your JAR includes the resources directory
4. You have the correct JDK architecture (x86_64, not ARM, unless you built for ARM)

### Error: Build fails on Linux with "jni.h not found"

Install JDK development package:
```bash
sudo apt-get install default-jdk
```

## Platform-Specific Notes

### Linux
- Requires GCC/Clang and standard build tools
- May need to install `build-essential` and `cmake`
- Library extension: `.so`
- Prefix: `lib` (e.g., `libTextureDecoder.so`)

### Windows  
- Requires Visual Studio with C++ tools
- Library extension: `.dll`
- No prefix (e.g., `TextureDecoder.dll`)

### macOS
- Requires Xcode Command Line Tools
- Supports universal binaries (x86_64 + ARM64)
- Library extension: `.dylib`
- Prefix: `lib` (e.g., `libTextureDecoder.dylib`)

## File Checklist

- [x] `CMakeLists.txt` - Cross-platform build configuration
- [x] `build-linux.sh` - Linux build script
- [x] `build-windows.bat` - Windows build script
- [x] `build-darwin.sh` - macOS build script
- [x] `build-linux-docker.sh/bat` - Docker-based Linux build
- [x] `NativeUtils.kt` - Enhanced platform detection and loading
- [x] `TextureDecoder.java` - Updated library loading
- [x] `BUILD.md` - Build documentation
- [x] `TextureDecoderNative/README.md` - Native library docs
- [x] `.github/workflows/build-natives.yml` - CI/CD pipeline
- [x] Directory structure for all platforms

## References

- [JNI Specification](https://docs.oracle.com/javase/8/docs/technotes/guides/jni/)
- [CMake Documentation](https://cmake.org/documentation/)
- [AssetStudio/Texture2DDecoderNative](https://github.com/Perfare/AssetStudio/tree/master/Texture2DDecoderNative)
- [BUILD.md](BUILD.md) - Build instructions
- [QUICKSTART.md](QUICKSTART.md) - Quick start guide
