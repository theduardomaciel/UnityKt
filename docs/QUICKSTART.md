# Quick Start: Building for Linux

## TL;DR - What You Need to Do

### 1. Build the Linux Native Library

You have 3 options:

#### Option A: On a Linux Machine (Easiest if you have Linux)

```bash
cd TextureDecoderNative
chmod +x build-linux.sh
./build-linux.sh
```

#### Option B: Using Docker on Windows (Recommended for Windows users)

```bash
cd TextureDecoderNative
build-linux-docker.bat
```

#### Option C: Use GitHub Actions (No local build needed)

1. Push your changes to GitHub
2. Go to Actions tab
3. Download the `linux-x86_64` artifact
4. Extract `libTextureDecoder.so` to `src/main/resources/natives/linux-x86_64/`

### 2. Verify the Library Exists

```bash
# Should show the .so file
ls -la src/main/resources/natives/linux-x86_64/
```

### 3. Build Your Kotlin Application

```bash
./gradlew build
```

### 4. Deploy to Linux Server

```bash
# Copy JAR to server
scp build/libs/UnityKt-*.jar user@your-server:/path/to/app/

# Run on server
ssh user@your-server
cd /path/to/app
java -jar UnityKt-*.jar
```

## What Changed?

- ✅ Native library loader now detects Linux automatically
- ✅ CMakeLists.txt configured for cross-platform builds
- ✅ Directory structure organized by platform
- ✅ Scripts ready for building on each platform

## Testing the Build

### On Linux Server

Create a simple test:

```kotlin
import io.github.deficuet.unitykt.UnityAssetManager
import io.github.deficuet.unitykt.extension.TextureDecoder

fun main() {
    println("Testing native library on Linux...")
    
    try {
        // Try to use a native function
        val input = ByteArray(16)
        val output = ByteArray(16)
        TextureDecoder.decodeDXT1(input, 4, 4, output)
        
        println("✅ Native library loaded successfully!")
    } catch (e: UnsatisfiedLinkError) {
        println("❌ Failed to load native library:")
        e.printStackTrace()
    }
}
```

Run it:

```bash
./gradlew run
```

## Troubleshooting

### "UnsatisfiedLinkError: Native library not found"

Check that `libTextureDecoder.so` exists in your JAR:

```bash
jar tf build/libs/UnityKt-*.jar | grep "natives/linux"
```

Should show:
```
natives/linux-x86_64/
natives/linux-x86_64/libTextureDecoder.so
```

### "Cannot find JNI" during build

Install JDK:

```bash
sudo apt-get update
sudo apt-get install default-jdk
```

### Docker build fails

Make sure Docker is running:

```bash
docker --version
docker ps
```

## Next Steps

1. ✅ Build the Linux library (using one of the methods above)
2. ✅ Test locally with `./gradlew run`
3. ✅ Build JAR with `./gradlew build`
4. ✅ Deploy to your Linux server
5. ✅ Your Kotlin API will automatically use the Linux native library!

## Need Help?

- Check [BUILD.md](BUILD.md) for detailed build instructions
- Check [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md) for server deployment
- Check [NATIVE_SETUP.md](NATIVE_SETUP.md) for technical details

## Summary

The main thing you need is to get `libTextureDecoder.so` compiled for Linux. The easiest way is using Docker if you're on Windows. Once you have that file, everything else is automatic!
