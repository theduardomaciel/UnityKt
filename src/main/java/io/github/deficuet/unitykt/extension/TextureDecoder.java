package io.github.deficuet.unitykt.extension;

import io.github.deficuet.unitykt.internal.NativeUtils;

public final class TextureDecoder {
    private TextureDecoder() {  }

    static {
        try {
            System.loadLibrary("TextureDecoder");
        } catch (UnsatisfiedLinkError e) {
            NativeUtils.Companion.loadLibraryFromJar("TextureDecoder", "dll");
        }
    }

    public static native int decodeDXT1(byte[] data, int w, int h, byte[] out);
    public static native int decodeDXT5(byte[] data, int w, int h, byte[] out);
    public static native int decodeBC4(byte[] data, int w, int h, byte[] out);
    public static native int decodeBC5(byte[] data, int w, int h, byte[] out);
    public static native int decodeBC6(byte[] data, int w, int h, byte[] out);
    public static native int decodeBC7(byte[] data, int w, int h, byte[] out);
    public static native int decodePVRTC(byte[] data, int w, int h, byte[] out, boolean is2bpp);
    public static native int decodeETC1(byte[] data, int w, int h, byte[] out);
    public static native int decodeETC2(byte[] data, int w, int h, byte[] out);
    public static native int decodeETC2A1(byte[] data, int w, int h, byte[] out);
    public static native int decodeETC2A8(byte[] data, int w, int h, byte[] out);
    public static native int decodeATCRGB4(byte[] data, int w, int h, byte[] out);
    public static native int decodeATCRGBA8(byte[] data, int w, int h, byte[] out);
    public static native int decodeASTC(byte[] data, int w, int h, byte[] out, int blockSize);
    public static native int decodeEACR(byte[] data, int w, int h, byte[] out);
    public static native int decodeEACRSigned(byte[] data, int w, int h, byte[] out);
    public static native int decodeEACRG(byte[] data, int w, int h, byte[] out);
    public static native int decodeEACRGSigned(byte[] data, int w, int h, byte[] out);
    public static native int decodeCrunchedDXT1(byte[] data, int w, int h, byte[] out, boolean useUnityCrunch);
    public static native int decodeCrunchedDXT5(byte[] data, int w, int h, byte[] out, boolean useUnityCrunch);
    public static native int decodeCrunchedETC1(byte[] data, int w, int h, byte[] out, boolean useUnityCrunch);
    public static native int decodeCrunchedETC2A8(byte[] data, int w, int h, byte[] out, boolean useUnityCrunch);
}
