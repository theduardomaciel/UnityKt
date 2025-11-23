# Using UnityKt in a Linux Server Environment

## Overview

UnityKt can now be used on Linux servers for processing Unity asset bundles. This guide shows how to set up and use it in a server environment.

## Setup

### 1. Build the Linux Native Library

On a Linux machine (or using Docker):

```bash
cd TextureDecoderNative
./build-linux.sh
```

This creates `libTextureDecoder.so` in `src/main/resources/natives/linux-x86_64/`.

### 2. Build Your Application

```bash
./gradlew build
```

This creates a JAR with all native libraries embedded.

### 3. Deploy to Server

Copy the JAR to your server:

```bash
scp build/libs/your-app.jar user@server:/path/to/app/
```

### 4. Run on Server

```bash
java -jar your-app.jar
```

The native library will be automatically extracted and loaded.

## Example: Kotlin API Server

### Using Ktor

```kotlin
import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import io.ktor.http.*
import io.ktor.http.content.*
import io.github.deficuet.unitykt.UnityAssetManager
import java.io.File

fun main() {
    embeddedServer(Netty, port = 8080) {
        routing {
            post("/decode-bundle") {
                val multipart = call.receiveMultipart()
                var bundle: ByteArray? = null
                var fileName = "unknown"
                
                multipart.forEachPart { part ->
                    when (part) {
                        is PartData.FileItem -> {
                            fileName = part.originalFileName ?: "bundle"
                            bundle = part.streamProvider().readBytes()
                        }
                        else -> {}
                    }
                    part.dispose()
                }
                
                if (bundle == null) {
                    call.respond(HttpStatusCode.BadRequest, "No file uploaded")
                    return@post
                }
                
                try {
                    // Process the Unity bundle
                    val manager = UnityAssetManager.new()
                    manager.use {
                        val context = it.loadByteArray(bundle!!, fileName)
                        
                        // Extract textures or other assets
                        val results = processAssets(context)
                        
                        call.respond(HttpStatusCode.OK, results)
                    }
                } catch (e: Exception) {
                    call.respond(
                        HttpStatusCode.InternalServerError,
                        "Error processing bundle: ${e.message}"
                    )
                }
            }
            
            get("/health") {
                call.respondText("OK", ContentType.Text.Plain)
            }
        }
    }.start(wait = true)
}

fun processAssets(context: ImportContext): Map<String, Any> {
    val results = mutableMapOf<String, Any>()
    
    // Example: extract texture information
    val textures = context.objects.filterIsInstance<Texture2D>()
    results["texture_count"] = textures.size
    results["textures"] = textures.map { texture ->
        mapOf(
            "name" to texture.mName,
            "width" to texture.mWidth,
            "height" to texture.mHeight,
            "format" to texture.mTextureFormat.toString()
        )
    }
    
    return results
}
```

### Using Spring Boot

```kotlin
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication
import org.springframework.web.bind.annotation.*
import org.springframework.web.multipart.MultipartFile
import org.springframework.http.ResponseEntity
import io.github.deficuet.unitykt.UnityAssetManager

@SpringBootApplication
class UnityBundleProcessorApplication

fun main(args: Array<String>) {
    runApplication<UnityBundleProcessorApplication>(*args)
}

@RestController
@RequestMapping("/api/bundles")
class BundleController {
    
    @PostMapping("/decode")
    fun decodeBundle(@RequestParam("file") file: MultipartFile): ResponseEntity<Map<String, Any>> {
        if (file.isEmpty) {
            return ResponseEntity.badRequest().body(mapOf("error" to "No file provided"))
        }
        
        return try {
            val manager = UnityAssetManager.new()
            manager.use {
                val context = it.loadByteArray(
                    file.bytes,
                    file.originalFilename ?: "bundle"
                )
                
                val results = processBundle(context)
                ResponseEntity.ok(results)
            }
        } catch (e: Exception) {
            ResponseEntity.internalServerError().body(
                mapOf("error" to "Failed to process bundle: ${e.message}")
            )
        }
    }
    
    @GetMapping("/health")
    fun health(): ResponseEntity<String> {
        return ResponseEntity.ok("Service is running")
    }
    
    private fun processBundle(context: ImportContext): Map<String, Any> {
        // Process bundle and extract information
        return mapOf(
            "objects" to context.objects.size,
            "file_name" to context.file.name,
            // Add more processing as needed
        )
    }
}
```

## Docker Deployment

### Dockerfile

```dockerfile
FROM eclipse-temurin:17-jdk-jammy

# Install required dependencies for native library (if needed)
RUN apt-get update && \
    apt-get install -y libc6 && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy JAR file
COPY build/libs/your-app.jar app.jar

# Expose port
EXPOSE 8080

# Run application
ENTRYPOINT ["java", "-jar", "app.jar"]
```

### Build and Run

```bash
# Build Docker image
docker build -t unity-bundle-processor .

# Run container
docker run -p 8080:8080 unity-bundle-processor

# Or with docker-compose
```

### docker-compose.yml

```yaml
version: '3.8'

services:
  app:
    build: .
    ports:
      - "8080:8080"
    environment:
      - JAVA_OPTS=-Xmx2g
    volumes:
      - ./bundles:/app/bundles
    restart: unless-stopped
```

## Performance Considerations

### Memory Management

Unity bundles can be large. Configure JVM memory:

```bash
java -Xmx4g -Xms1g -jar your-app.jar
```

### Cleanup

Always use `manager.use { }` or call `manager.close()` to release resources:

```kotlin
val manager = UnityAssetManager.new()
try {
    // Process bundles
} finally {
    manager.close()
}

// Or better:
UnityAssetManager.new().use { manager ->
    // Process bundles
}
```

### Concurrent Processing

For handling multiple requests:

```kotlin
import kotlinx.coroutines.*
import java.util.concurrent.Executors

val processingDispatcher = Executors.newFixedThreadPool(4).asCoroutineDispatcher()

suspend fun processBundle(bundle: ByteArray, fileName: String): Map<String, Any> = 
    withContext(processingDispatcher) {
        UnityAssetManager.new().use { manager ->
            val context = manager.loadByteArray(bundle, fileName)
            // Process...
            mapOf("status" to "success")
        }
    }
```

## Troubleshooting

### Native Library Not Found

If you see `UnsatisfiedLinkError`:

1. Verify the library is in the JAR:
   ```bash
   jar tf your-app.jar | grep natives
   ```

2. Check the platform is correct:
   ```bash
   java -XshowSettings:properties -version 2>&1 | grep "os.name\|os.arch"
   ```

3. Ensure proper file permissions:
   ```bash
   chmod +x /tmp/UnityKt_Deficuet/*.so
   ```

### Out of Memory

Increase JVM heap size:

```bash
java -Xmx4g -jar your-app.jar
```

Or in Docker:

```dockerfile
ENV JAVA_OPTS="-Xmx4g"
ENTRYPOINT ["sh", "-c", "java $JAVA_OPTS -jar app.jar"]
```

### Permission Errors

The library needs write access to temp directory:

```bash
# Ensure temp directory is writable
chmod 777 /tmp
```

Or set custom temp directory:

```bash
java -Djava.io.tmpdir=/path/to/writable/dir -jar your-app.jar
```

## Systemd Service (Linux)

### /etc/systemd/system/unity-processor.service

```ini
[Unit]
Description=Unity Bundle Processor Service
After=network.target

[Service]
Type=simple
User=appuser
WorkingDirectory=/opt/unity-processor
ExecStart=/usr/bin/java -Xmx2g -jar /opt/unity-processor/app.jar
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
```

### Enable and Start

```bash
sudo systemctl daemon-reload
sudo systemctl enable unity-processor
sudo systemctl start unity-processor
sudo systemctl status unity-processor
```

## Monitoring

### Logging

Configure logging to track native library loading:

```kotlin
import org.slf4j.LoggerFactory

val logger = LoggerFactory.getLogger("UnityProcessor")

try {
    val manager = UnityAssetManager.new(debugOutput = { msg ->
        logger.debug(msg)
    })
    // ...
} catch (e: UnsatisfiedLinkError) {
    logger.error("Failed to load native library", e)
}
```

### Health Checks

Implement health endpoints that verify native library is loaded:

```kotlin
@GetMapping("/health/native")
fun nativeLibraryHealth(): ResponseEntity<Map<String, Any>> {
    return try {
        // Try to use a native function
        TextureDecoder.decodeDXT1(ByteArray(16), 4, 4, ByteArray(16))
        ResponseEntity.ok(mapOf(
            "status" to "ok",
            "native_library" to "loaded"
        ))
    } catch (e: Exception) {
        ResponseEntity.internalServerError().body(mapOf(
            "status" to "error",
            "native_library" to "failed",
            "error" to e.message
        ))
    }
}
```

## Summary

UnityKt now works seamlessly on Linux servers. The native texture decoding library is automatically detected and loaded based on your platform, making deployment simple and straightforward.
