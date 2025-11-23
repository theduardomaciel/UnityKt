package io.github.deficuet.unitykt.internal

import java.io.File
import java.io.IOException
import java.nio.file.FileSystems
import java.nio.file.Files
import java.nio.file.StandardCopyOption

internal class NativeUtils private constructor() {
    companion object {
        private val nativeTempFolder by lazy {
            val temp = File(
                "${System.getProperty("java.io.tmpdir")}UnityKt_Deficuet"
            )
            if (!temp.exists()) {
                if (!temp.mkdir())
                    throw IllegalStateException("Can't create temp directory ${temp.canonicalPath}")
            }
            temp
        }

        private val isPosix: Boolean get() {
            return try {
                FileSystems.getDefault().supportedFileAttributeViews().contains("posix")
            } catch (e: Exception) {
                false
            }
        }

        /**
         * Detects the current OS and architecture and returns the platform identifier
         * Format: {os}-{arch} (e.g., "linux-x86_64", "windows-x86_64", "darwin-aarch64")
         */
        private fun getPlatform(): String {
            val osName = System.getProperty("os.name").lowercase()
            val osArch = System.getProperty("os.arch").lowercase()
            
            val os = when {
                osName.contains("win") -> "windows"
                osName.contains("mac") || osName.contains("darwin") -> "darwin"
                osName.contains("nux") || osName.contains("nix") -> "linux"
                else -> throw UnsupportedOperationException("Unsupported OS: $osName")
            }
            
            val arch = when {
                osArch.contains("amd64") || osArch.contains("x86_64") -> "x86_64"
                osArch.contains("aarch64") || osArch.contains("arm64") -> "aarch64"
                osArch.contains("arm") -> "arm"
                else -> osArch
            }
            
            return "$os-$arch"
        }

        /**
         * Gets the library file name with proper prefix and extension for the current platform
         */
        private fun getLibraryFileName(name: String): String {
            val osName = System.getProperty("os.name").lowercase()
            
            return when {
                osName.contains("win") -> "$name.dll"
                osName.contains("mac") || osName.contains("darwin") -> "lib$name.dylib"
                osName.contains("nux") || osName.contains("nix") -> "lib$name.so"
                else -> throw UnsupportedOperationException("Unsupported OS: $osName")
            }
        }

        /**
         * Loads a native library from the JAR resources
         * Looks for the library in /natives/{platform}/ directory
         */
        fun loadLibraryFromJar(name: String) {
            val platform = getPlatform()
            val libraryFileName = getLibraryFileName(name)
            val resourcePath = "/natives/$platform/$libraryFileName"
            
            val inputStream = NativeUtils::class.java.getResourceAsStream(resourcePath)
                ?: throw UnsatisfiedLinkError(
                    "Native library not found: $resourcePath\n" +
                    "Platform: $platform\n" +
                    "Please ensure the library is compiled for your platform."
                )
            
            val f = File.createTempFile("${name}_", getExtension(libraryFileName), nativeTempFolder)
            inputStream.use {
                try {
                    Files.copy(it, f.toPath(), StandardCopyOption.REPLACE_EXISTING)
                } catch (e: IOException) {
                    f.delete()
                    throw UnsatisfiedLinkError("Failed to extract native library: ${e.message}")
                }
            }
            
            try {
                System.load(f.absolutePath)
            } finally {
                try {
                    if (isPosix) {
                        f.delete()
                    } else {
                        f.deleteOnExit()
                    }
                } catch (_: Throwable) {  }
            }
        }

        /**
         * Legacy method for backward compatibility
         */
        @Deprecated("Use loadLibraryFromJar(name: String) instead", ReplaceWith("loadLibraryFromJar(name)"))
        fun loadLibraryFromJar(name: String, ext: String) {
            loadLibraryFromJar(name)
        }

        private fun getExtension(fileName: String): String {
            val dotIndex = fileName.lastIndexOf('.')
            return if (dotIndex > 0) fileName.substring(dotIndex) else ""
        }
    }
}