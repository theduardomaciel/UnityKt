# TextureDecoderNative

Native C++ library for decoding various texture formats used in Unity.

## Building

See [BUILD.md](../docs/BUILD.md) for detailed build instructions.

### Quick Start

#### Linux
```bash
./build-linux.sh
```

#### Windows
```cmd
build-windows.bat
```

#### macOS
```bash
./build-darwin.sh
```

## Supported Texture Formats

- DXT1/DXT5 (BC1/BC3)
- BC4/BC5/BC6/BC7
- PVRTC (2bpp/4bpp)
- ETC1/ETC2 variants
- ATC (RGB4/RGBA8)
- ASTC
- EAC (R/RG, signed/unsigned)
- Crunched formats (DXT1/DXT5/ETC1/ETC2A8)

## Architecture

The library uses JNI (Java Native Interface) to provide high-performance texture decoding from Java/Kotlin code.

### File Structure

- `CMakeLists.txt` - CMake build configuration (cross-platform)
- `build-*.sh/bat` - Platform-specific build scripts
- `io_github_deficuet_unitykt_extension_TextureDecoder.h` - JNI header (generated)
- `io_github_deficuet_unitykt_extension_TextureDecoder.cc` - JNI implementation
- `lib/` - Core decoding implementations
  - `astc.cpp/h` - ASTC decoder
  - `atc.cpp/h` - ATC decoder
  - `bcn.cpp/h` - BCN (DirectX) decoders
  - `etc.cpp/h` - ETC decoders
  - `pvrtc.cpp/h` - PVRTC decoder
  - `crunch.cpp/h` - Crunch decompression
  - `unitycrunch.cpp/h` - Unity-specific Crunch variant
  - `color.h` - Color manipulation utilities
  - `endianness.h` - Endianness handling
  - `fp16.h` - Half-precision float support
  - Additional subdirectories with third-party decoder implementations

## Regenerating JNI Headers

If you modify the `TextureDecoder.java` file and add new native methods:

```bash
./header.bat  # Windows
# or
javac -h ./ ../src/main/java/io/github/deficuet/unitykt/extension/TextureDecoder.java
```

This will regenerate the `io_github_deficuet_unitykt_extension_TextureDecoder.h` file.

## Output

Compiled libraries are placed in:
- `../src/main/resources/natives/linux-x86_64/libTextureDecoder.so`
- `../src/main/resources/natives/windows-x86_64/TextureDecoder.dll`
- `../src/main/resources/natives/darwin-{arch}/libTextureDecoder.dylib`

These are automatically loaded by the Java/Kotlin code based on the runtime platform.
