package io.github.deficuet.unitykt.test

import io.github.deficuet.unitykt.extension.TextureDecoder
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.DisplayName
import org.junit.jupiter.api.BeforeAll

/**
 * Test suite for native library loading and texture decoding functionality
 * across different platforms (Windows, Linux, macOS)
 */
class NativeLibraryTest {

    companion object {
        @JvmStatic
        @BeforeAll
        fun setup() {
            println("Testing on platform: ${System.getProperty("os.name")} ${System.getProperty("os.arch")}")
        }
    }

    @Test
    @DisplayName("Native library should load successfully")
    fun testNativeLibraryLoads() {
        assertDoesNotThrow {
            // Try to access a native method
            // This will trigger the static initializer and library loading
            val input = ByteArray(16) { 0 }
            val output = ByteArray(64) { 0 } // 4x4 pixels = 16 pixels * 4 bytes (RGBA)
            
            // This should not throw UnsatisfiedLinkError
            TextureDecoder.decodeDXT1(input, 4, 4, output)
            
            println("✅ Native library loaded successfully!")
        }
    }

    @Test
    @DisplayName("Should detect correct platform")
    fun testPlatformDetection() {
        val osName = System.getProperty("os.name").lowercase()
        val osArch = System.getProperty("os.arch").lowercase()
        
        val expectedPlatform = when {
            osName.contains("win") -> "windows"
            osName.contains("mac") || osName.contains("darwin") -> "darwin"
            osName.contains("nux") || osName.contains("nix") -> "linux"
            else -> "unknown"
        }
        
        assertNotEquals("unknown", expectedPlatform, "Platform should be recognized")
        println("Platform detected: $expectedPlatform-$osArch")
    }

    @Test
    @DisplayName("DXT1 decoder should work")
    fun testDXT1Decoder() {
        // Create a simple DXT1 block (16 bytes for a 4x4 texture)
        val dxt1Data = ByteArray(16) {
            when (it) {
                // Color 0 (RGB565) - Red
                0 -> 0x00.toByte()
                1 -> 0xF8.toByte()
                // Color 1 (RGB565) - Blue
                2 -> 0x1F.toByte()
                3 -> 0x00.toByte()
                // Indices (2 bits per pixel, 16 pixels)
                else -> 0x00.toByte()
            }
        }
        
        val output = ByteArray(64) // 4x4 pixels * 4 bytes (RGBA)
        
        val result = TextureDecoder.decodeDXT1(dxt1Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        assertNotNull(output, "Output should not be null")
        assertTrue(output.any { it != 0.toByte() }, "Output should contain decoded data")
        
        println("✅ DXT1 decoder working")
    }

    @Test
    @DisplayName("DXT5 decoder should work")
    fun testDXT5Decoder() {
        // DXT5 block (32 bytes for a 4x4 texture)
        val dxt5Data = ByteArray(32) {
            when {
                it < 8 -> 0xFF.toByte() // Alpha block
                it < 16 -> when (it - 8) {
                    0 -> 0x00.toByte()
                    1 -> 0xF8.toByte()
                    2 -> 0x1F.toByte()
                    3 -> 0x00.toByte()
                    else -> 0x00.toByte()
                }
                else -> 0x00.toByte()
            }
        }
        
        val output = ByteArray(64) // 4x4 pixels * 4 bytes (RGBA)
        
        val result = TextureDecoder.decodeDXT5(dxt5Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        assertTrue(output.any { it != 0.toByte() }, "Output should contain decoded data")
        
        println("✅ DXT5 decoder working")
    }

    @Test
    @DisplayName("ETC1 decoder should work")
    fun testETC1Decoder() {
        val etc1Data = ByteArray(8) { 0 } // 8 bytes for 4x4 ETC1 block
        val output = ByteArray(64)
        
        val result = TextureDecoder.decodeETC1(etc1Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ ETC1 decoder working")
    }

    @Test
    @DisplayName("ETC2 decoder should work")
    fun testETC2Decoder() {
        val etc2Data = ByteArray(8) { 0 } // 8 bytes for 4x4 ETC2 block
        val output = ByteArray(64)
        
        val result = TextureDecoder.decodeETC2(etc2Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ ETC2 decoder working")
    }

    @Test
    @DisplayName("BC4 decoder should work")
    fun testBC4Decoder() {
        val bc4Data = ByteArray(8) { 0 } // 8 bytes for 4x4 BC4 block
        val output = ByteArray(64)
        
        val result = TextureDecoder.decodeBC4(bc4Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ BC4 decoder working")
    }

    @Test
    @DisplayName("BC5 decoder should work")
    fun testBC5Decoder() {
        val bc5Data = ByteArray(16) { 0 } // 16 bytes for 4x4 BC5 block
        val output = ByteArray(64)
        
        val result = TextureDecoder.decodeBC5(bc5Data, 4, 4, output)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ BC5 decoder working")
    }

    @Test
    @DisplayName("ASTC 4x4 decoder should work")
    fun testASTCDecoder() {
        val astcData = ByteArray(16) { 0 } // 16 bytes for 4x4 ASTC block
        val output = ByteArray(64)
        
        val result = TextureDecoder.decodeASTC(astcData, 4, 4, output, 4)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ ASTC decoder working")
    }

    @Test
    @DisplayName("PVRTC decoder should work")
    fun testPVRTCDecoder() {
        val pvrtcData = ByteArray(32) { 0 } // Data for 8x8 PVRTC 4bpp
        val output = ByteArray(256) // 8x8 pixels * 4 bytes
        
        val result = TextureDecoder.decodePVRTC(pvrtcData, 8, 8, output, false)
        
        assertEquals(1, result, "Decoder should return success (1)")
        println("✅ PVRTC decoder working")
    }

    @Test
    @DisplayName("All texture formats should be decodable")
    fun testAllFormats() {
        val formats = listOf(
            "DXT1" to { TextureDecoder.decodeDXT1(ByteArray(16), 4, 4, ByteArray(64)) },
            "DXT5" to { TextureDecoder.decodeDXT5(ByteArray(32), 4, 4, ByteArray(64)) },
            "BC4" to { TextureDecoder.decodeBC4(ByteArray(8), 4, 4, ByteArray(64)) },
            "BC5" to { TextureDecoder.decodeBC5(ByteArray(16), 4, 4, ByteArray(64)) },
            "BC6" to { TextureDecoder.decodeBC6(ByteArray(16), 4, 4, ByteArray(64)) },
            "BC7" to { TextureDecoder.decodeBC7(ByteArray(16), 4, 4, ByteArray(64)) },
            "ETC1" to { TextureDecoder.decodeETC1(ByteArray(8), 4, 4, ByteArray(64)) },
            "ETC2" to { TextureDecoder.decodeETC2(ByteArray(8), 4, 4, ByteArray(64)) },
            "ETC2A1" to { TextureDecoder.decodeETC2A1(ByteArray(8), 4, 4, ByteArray(64)) },
            "ETC2A8" to { TextureDecoder.decodeETC2A8(ByteArray(16), 4, 4, ByteArray(64)) },
            "ASTC" to { TextureDecoder.decodeASTC(ByteArray(16), 4, 4, ByteArray(64), 4) },
            "PVRTC" to { TextureDecoder.decodePVRTC(ByteArray(32), 8, 8, ByteArray(256), false) },
        )
        
        val results = mutableListOf<Pair<String, Boolean>>()
        
        formats.forEach { (name, decoder) ->
            val success = try {
                val result = decoder()
                result == 1
            } catch (e: Exception) {
                println("❌ $name failed: ${e.message}")
                false
            }
            results.add(name to success)
        }
        
        println("\nFormat Support Summary:")
        results.forEach { (name, success) ->
            println("  ${if (success) "✅" else "❌"} $name")
        }
        
        val allSuccessful = results.all { it.second }
        assertTrue(allSuccessful, "All texture formats should decode successfully")
    }

    @Test
    @DisplayName("Library should handle errors gracefully")
    fun testErrorHandling() {
        // Test with invalid data sizes
        assertDoesNotThrow {
            val tooSmallInput = ByteArray(1)
            val output = ByteArray(64)
            
            // Should not crash, might return error code
            val result = TextureDecoder.decodeDXT1(tooSmallInput, 4, 4, output)
            
            println("Error handling result: $result")
        }
    }

    @Test
    @DisplayName("Library should work with different texture sizes")
    fun testDifferentSizes() {
        val sizes = listOf(4 to 4, 8 to 8, 16 to 16, 32 to 32)
        
        sizes.forEach { (width, height) ->
            val blockSize = (width / 4) * (height / 4) * 16 // DXT1 block size
            val input = ByteArray(blockSize)
            val output = ByteArray(width * height * 4)
            
            assertDoesNotThrow {
                val result = TextureDecoder.decodeDXT1(input, width, height, output)
                assertEquals(1, result, "Should succeed for ${width}x${height}")
            }
            
            println("✅ Decoded ${width}x${height} texture")
        }
    }
}
