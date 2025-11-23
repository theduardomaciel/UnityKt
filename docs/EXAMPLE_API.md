# Example: Kotlin API Server with UnityKt

This is a practical example of how to use UnityKt in a Kotlin API server running on Linux.

## Example 1: Simple Ktor API

```kotlin
// File: src/main/kotlin/com/yourcompany/Application.kt

import io.ktor.server.application.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import io.ktor.server.request.*
import io.ktor.http.*
import io.ktor.http.content.*
import io.github.deficuet.unitykt.UnityAssetManager
import io.github.deficuet.unitykt.classes.Texture2D
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import java.io.File

fun main() {
    embeddedServer(Netty, port = 8080, host = "0.0.0.0") {
        configureRouting()
    }.start(wait = true)
}

fun Application.configureRouting() {
    routing {
        get("/") {
            call.respondText("Unity Bundle Processor API - Running on ${System.getProperty("os.name")}")
        }

        get("/health") {
            call.respondText("OK", status = HttpStatusCode.OK)
        }

        post("/api/bundle/info") {
            try {
                val multipart = call.receiveMultipart()
                var bundleData: ByteArray? = null
                var fileName = "bundle"

                multipart.forEachPart { part ->
                    when (part) {
                        is PartData.FileItem -> {
                            fileName = part.originalFileName ?: "bundle"
                            bundleData = part.streamProvider().readBytes()
                        }
                        else -> {}
                    }
                    part.dispose()
                }

                if (bundleData == null) {
                    call.respond(HttpStatusCode.BadRequest, mapOf("error" to "No file provided"))
                    return@post
                }

                // Process the bundle
                val result = withContext(Dispatchers.IO) {
                    processBundleInfo(bundleData!!, fileName)
                }

                call.respond(HttpStatusCode.OK, result)

            } catch (e: Exception) {
                e.printStackTrace()
                call.respond(
                    HttpStatusCode.InternalServerError,
                    mapOf("error" to "Failed to process bundle: ${e.message}")
                )
            }
        }

        post("/api/bundle/extract-textures") {
            try {
                val multipart = call.receiveMultipart()
                var bundleData: ByteArray? = null
                var fileName = "bundle"

                multipart.forEachPart { part ->
                    when (part) {
                        is PartData.FileItem -> {
                            fileName = part.originalFileName ?: "bundle"
                            bundleData = part.streamProvider().readBytes()
                        }
                        else -> {}
                    }
                    part.dispose()
                }

                if (bundleData == null) {
                    call.respond(HttpStatusCode.BadRequest, mapOf("error" to "No file provided"))
                    return@post
                }

                // Extract textures
                val result = withContext(Dispatchers.IO) {
                    extractTextures(bundleData!!, fileName)
                }

                call.respond(HttpStatusCode.OK, result)

            } catch (e: Exception) {
                e.printStackTrace()
                call.respond(
                    HttpStatusCode.InternalServerError,
                    mapOf("error" to "Failed to extract textures: ${e.message}")
                )
            }
        }
    }
}

fun processBundleInfo(bundleData: ByteArray, fileName: String): Map<String, Any> {
    val manager = UnityAssetManager.new(debugOutput = { println("[UnityKt] $it") })
    
    return manager.use {
        val context = it.loadByteArray(bundleData, fileName)
        
        val objectCounts = context.objects.groupingBy { obj ->
            obj::class.simpleName ?: "Unknown"
        }.eachCount()
        
        mapOf(
            "fileName" to fileName,
            "fileSize" to bundleData.size,
            "totalObjects" to context.objects.size,
            "objectsByType" to objectCounts,
            "platform" to System.getProperty("os.name")
        )
    }
}

fun extractTextures(bundleData: ByteArray, fileName: String): Map<String, Any> {
    val manager = UnityAssetManager.new()
    
    return manager.use {
        val context = it.loadByteArray(bundleData, fileName)
        
        val textures = context.objects.filterIsInstance<Texture2D>()
        
        val textureInfoList = textures.map { texture ->
            mapOf(
                "name" to texture.mName,
                "width" to texture.mWidth,
                "height" to texture.mHeight,
                "format" to texture.mTextureFormat.toString(),
                "mipmapCount" to texture.mMipCount
            )
        }
        
        mapOf(
            "fileName" to fileName,
            "textureCount" to textures.size,
            "textures" to textureInfoList
        )
    }
}
```

## Example 2: Spring Boot REST API

```kotlin
// File: src/main/kotlin/com/yourcompany/Application.kt

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication
import org.springframework.context.annotation.Configuration
import org.springframework.web.bind.annotation.*
import org.springframework.web.multipart.MultipartFile
import org.springframework.http.ResponseEntity
import org.springframework.http.HttpStatus
import io.github.deficuet.unitykt.UnityAssetManager
import io.github.deficuet.unitykt.classes.Texture2D
import io.github.deficuet.unitykt.classes.Sprite
import io.github.deficuet.unitykt.classes.Mesh
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext
import java.util.concurrent.ConcurrentHashMap

@SpringBootApplication
class UnityBundleProcessorApplication

fun main(args: Array<String>) {
    runApplication<UnityBundleProcessorApplication>(*args)
}

@RestController
@RequestMapping("/api/v1")
class BundleController {

    private val processCache = ConcurrentHashMap<String, Map<String, Any>>()

    @GetMapping("/health")
    fun health(): ResponseEntity<Map<String, String>> {
        return ResponseEntity.ok(mapOf(
            "status" to "UP",
            "platform" to System.getProperty("os.name"),
            "architecture" to System.getProperty("os.arch")
        ))
    }

    @PostMapping("/bundle/analyze")
    fun analyzeBundle(
        @RequestParam("file") file: MultipartFile
    ): ResponseEntity<Map<String, Any>> = runBlocking {
        
        if (file.isEmpty) {
            return@runBlocking ResponseEntity
                .badRequest()
                .body(mapOf("error" to "No file provided"))
        }

        try {
            val result = withContext(Dispatchers.IO) {
                analyzeUnityBundle(file.bytes, file.originalFilename ?: "unknown")
            }
            
            ResponseEntity.ok(result)
        } catch (e: Exception) {
            ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .body(mapOf(
                    "error" to "Analysis failed",
                    "message" to (e.message ?: "Unknown error")
                ))
        }
    }

    @PostMapping("/bundle/textures")
    fun extractTextures(
        @RequestParam("file") file: MultipartFile
    ): ResponseEntity<Map<String, Any>> = runBlocking {
        
        if (file.isEmpty) {
            return@runBlocking ResponseEntity
                .badRequest()
                .body(mapOf("error" to "No file provided"))
        }

        try {
            val result = withContext(Dispatchers.IO) {
                extractTextureData(file.bytes, file.originalFilename ?: "unknown")
            }
            
            ResponseEntity.ok(result)
        } catch (e: Exception) {
            ResponseEntity
                .status(HttpStatus.INTERNAL_SERVER_ERROR)
                .body(mapOf(
                    "error" to "Extraction failed",
                    "message" to (e.message ?: "Unknown error")
                ))
        }
    }

    private fun analyzeUnityBundle(data: ByteArray, fileName: String): Map<String, Any> {
        val manager = UnityAssetManager.new()
        
        return manager.use {
            val context = it.loadByteArray(data, fileName)
            
            val objectTypes = context.objects.groupingBy { obj ->
                obj::class.simpleName ?: "Unknown"
            }.eachCount()
            
            val textures = context.objects.filterIsInstance<Texture2D>()
            val sprites = context.objects.filterIsInstance<Sprite>()
            val meshes = context.objects.filterIsInstance<Mesh>()
            
            mapOf(
                "analysis" to mapOf(
                    "fileName" to fileName,
                    "fileSize" to data.size,
                    "totalObjects" to context.objects.size,
                    "objectTypes" to objectTypes,
                    "summary" to mapOf(
                        "textures" to textures.size,
                        "sprites" to sprites.size,
                        "meshes" to meshes.size
                    )
                )
            )
        }
    }

    private fun extractTextureData(data: ByteArray, fileName: String): Map<String, Any> {
        val manager = UnityAssetManager.new()
        
        return manager.use {
            val context = it.loadByteArray(data, fileName)
            
            val textures = context.objects.filterIsInstance<Texture2D>()
            
            val textureList = textures.map { texture ->
                mapOf(
                    "name" to texture.mName,
                    "width" to texture.mWidth,
                    "height" to texture.mHeight,
                    "format" to texture.mTextureFormat.toString(),
                    "mipmaps" to texture.mMipCount,
                    "size" to (texture.mWidth * texture.mHeight * 4) // Estimated RGBA size
                )
            }
            
            mapOf(
                "extraction" to mapOf(
                    "fileName" to fileName,
                    "textureCount" to textures.size,
                    "textures" to textureList,
                    "totalEstimatedSize" to textureList.sumOf { 
                        (it["size"] as? Int) ?: 0 
                    }
                )
            )
        }
    }
}
```

## Example 3: Gradle Build Configuration

```kotlin
// File: build.gradle.kts

plugins {
    kotlin("jvm") version "1.9.21"
    application
    id("com.github.johnrengelman.shadow") version "8.1.1" // For fat JAR
}

group = "com.yourcompany"
version = "1.0.0"

repositories {
    mavenCentral()
    maven("https://jitpack.io")
}

dependencies {
    // Kotlin
    implementation(kotlin("stdlib"))
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.7.3")

    // Ktor (choose this OR Spring Boot)
    implementation("io.ktor:ktor-server-core:2.3.7")
    implementation("io.ktor:ktor-server-netty:2.3.7")
    
    // OR Spring Boot (choose this OR Ktor)
    // implementation("org.springframework.boot:spring-boot-starter-web:3.2.0")
    
    // Logging
    implementation("ch.qos.logback:logback-classic:1.4.14")

    // Testing
    testImplementation(kotlin("test"))
    testImplementation("org.junit.jupiter:junit-jupiter:5.10.1")
}

application {
    mainClass.set("com.yourcompany.ApplicationKt")
}

tasks.test {
    useJUnitPlatform()
}

// Create fat JAR with all dependencies
tasks.shadowJar {
    archiveBaseName.set("unity-processor")
    archiveClassifier.set("")
    archiveVersion.set(version.toString())
}

kotlin {
    jvmToolchain(17)
}
```

## Example 4: Docker Deployment

```dockerfile
# File: Dockerfile

FROM eclipse-temurin:17-jdk-jammy as builder

WORKDIR /app

# Copy gradle files
COPY gradlew .
COPY gradle gradle
COPY build.gradle.kts .
COPY settings.gradle.kts .

# Copy source
COPY src src
COPY TextureDecoderNative TextureDecoderNative

# Build application
RUN ./gradlew shadowJar --no-daemon

# Runtime stage
FROM eclipse-temurin:17-jre-jammy

WORKDIR /app

# Install runtime dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends libc6 && \
    rm -rf /var/lib/apt/lists/*

# Copy JAR from builder
COPY --from=builder /app/build/libs/unity-processor-*.jar app.jar

# Expose port
EXPOSE 8080

# Set JVM options
ENV JAVA_OPTS="-Xmx2g -Xms512m"

# Run
ENTRYPOINT ["sh", "-c", "java $JAVA_OPTS -jar app.jar"]
```

## Example 5: Testing the API

```bash
# Test health endpoint
curl http://localhost:8080/health

# Upload and analyze a bundle
curl -X POST \
  -F "file=@path/to/your/bundle.unity3d" \
  http://localhost:8080/api/bundle/info

# Extract texture information
curl -X POST \
  -F "file=@path/to/your/bundle.unity3d" \
  http://localhost:8080/api/bundle/extract-textures
```

## Example Response

```json
{
  "fileName": "character_bundle.unity3d",
  "fileSize": 1048576,
  "totalObjects": 42,
  "objectsByType": {
    "Texture2D": 15,
    "Sprite": 8,
    "Mesh": 5,
    "Material": 10,
    "GameObject": 4
  },
  "platform": "Linux"
}
```

## Building and Running

```bash
# Build the application
./gradlew shadowJar

# Run locally
java -jar build/libs/unity-processor-1.0.0.jar

# Or with Docker
docker build -t unity-processor .
docker run -p 8080:8080 unity-processor

# Deploy to server
scp build/libs/unity-processor-1.0.0.jar user@server:/opt/app/
ssh user@server "cd /opt/app && java -jar unity-processor-1.0.0.jar"
```

## Performance Tips

```kotlin
// Use connection pooling for database access
// Implement caching for frequently accessed bundles
// Use coroutines for concurrent processing

import kotlinx.coroutines.*
import java.util.concurrent.Executors

val processingDispatcher = Executors.newFixedThreadPool(
    Runtime.getRuntime().availableProcessors()
).asCoroutineDispatcher()

suspend fun processMultipleBundles(bundles: List<ByteArray>) = coroutineScope {
    bundles.map { bundle ->
        async(processingDispatcher) {
            processBundle(bundle)
        }
    }.awaitAll()
}
```

This example shows a complete working setup for using UnityKt on a Linux server!
