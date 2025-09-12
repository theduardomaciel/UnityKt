#include <cstdint>

#include "io_github_deficuet_unitykt_extension_TextureDecoder.h"
#include "lib/crunch.h"
#include "lib/unitycrunch.h"
#include "lib/bcn.h"
#include "lib/pvrtc.h"
#include "lib/etc.h"
#include "lib/atc.h"
#include "lib/astc.h"

static void get_array_critical(
    JNIEnv *env, jbyteArray &data, jbyteArray &out,
    const uint8_t *&dataPtr, uint32_t *&outPtr
) {
    dataPtr = static_cast<const uint8_t *>(env->GetPrimitiveArrayCritical(data, nullptr));
    outPtr = static_cast<uint32_t *>(env->GetPrimitiveArrayCritical(out, nullptr));
}

static void release_array_critical(
    JNIEnv *env, jbyteArray &data, jbyteArray &out,
    const uint8_t *dataPtr, uint32_t *outPtr, jint releaseOutMode
) {
    if (outPtr != nullptr) {
        env->ReleasePrimitiveArrayCritical(out, (void *)outPtr, releaseOutMode);
    }
    if (dataPtr != nullptr) {
        env->ReleasePrimitiveArrayCritical(data, (void *)dataPtr, JNI_ABORT);
    }
}

static bool check_array(
    JNIEnv *env, jbyteArray &data, jbyteArray &out,
    const uint8_t *dataPtr, uint32_t *outPtr
) {
    if (dataPtr == nullptr || outPtr == nullptr) {
        release_array_critical(env, data, out, dataPtr, outPtr, JNI_ABORT);
        jclass oom = env->FindClass("java/lang/OutOfMemoryError");
        env->ThrowNew(oom, "Failed to get critical array access.");
        return false;
    }
    return true;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeDXT1
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc1(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeDXT5
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc3(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeBC4
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc4(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeBC5
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc5(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeBC6
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc6(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeBC7
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_bc7(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodePVRTC
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jboolean is2bpp) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_pvrtc(dataPtr, w, h, outPtr, is2bpp ? 1 : 0);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeETC1
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_etc1(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeETC2
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_etc2(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeETC2A1
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_etc2a1(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeETC2A8
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_etc2a8(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeATCRGB4
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_atc_rgb4(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeATCRGBA8
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_atc_rgba8(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeASTC
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jint blockSize) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_astc(dataPtr, w, h, blockSize, blockSize, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeEACR
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_eacr(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeEACRSigned
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_eacr_signed(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeEACRG
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_eacrg(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeEACRGSigned
(JNIEnv *env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    decode_eacrg_signed(dataPtr, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

typedef bool (*CrunchUnpackCallable)(const uint8_t* data, uint32_t data_size, uint32_t level_index, void** ret, uint32_t* ret_size);

static bool do_crunch_unpack(
    const uint8_t *dataPtr, jsize dataSize, void **ret, 
    uint32_t *retSizePtr, jboolean useUnityCrunch
) {
    CrunchUnpackCallable callable = useUnityCrunch ? &unity_crunch_unpack_level : &crunch_unpack_level;
    if (!callable(dataPtr, dataSize, 0, ret, retSizePtr)) {
        if (*ret != nullptr) {
            delete[] *ret;
        }
        return false;
    }
    return true;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeCrunchedDXT1
(JNIEnv * env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jboolean useUnityCrunch) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    jsize dataSize = env->GetArrayLength(data);
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    const uint8_t *unpackedData = nullptr; uint32_t unpackedSize = 0;
    if (!do_crunch_unpack(dataPtr, dataSize, (void **)&unpackedData, &unpackedSize, useUnityCrunch)) {
        release_array_critical(env, data, out, dataPtr, outPtr, JNI_ABORT);
        return 0;
    }
    decode_bc1(unpackedData, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeCrunchedDXT5
(JNIEnv * env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jboolean useUnityCrunch) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    jsize dataSize = env->GetArrayLength(data);
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    const uint8_t *unpackedData = nullptr; uint32_t unpackedSize = 0;
    if (!do_crunch_unpack(dataPtr, dataSize, (void **)&unpackedData, &unpackedSize, useUnityCrunch)) {
        release_array_critical(env, data, out, dataPtr, outPtr, JNI_ABORT);
        return 0;
    }
    decode_bc3(unpackedData, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeCrunchedETC1
(JNIEnv * env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jboolean useUnityCrunch) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    jsize dataSize = env->GetArrayLength(data);
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    const uint8_t *unpackedData = nullptr; uint32_t unpackedSize = 0;
    if (!do_crunch_unpack(dataPtr, dataSize, (void **)&unpackedData, &unpackedSize, useUnityCrunch)) {
        release_array_critical(env, data, out, dataPtr, outPtr, JNI_ABORT);
        return 0;
    }
    decode_etc1(unpackedData, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}

JNIEXPORT jint JNICALL Java_io_github_deficuet_unitykt_extension_TextureDecoder_decodeCrunchedETC2A8
(JNIEnv * env, jclass clz, jbyteArray data, jint w, jint h, jbyteArray out, jboolean useUnityCrunch) {
    const uint8_t *dataPtr = nullptr;
    uint32_t *outPtr = nullptr;
    jsize dataSize = env->GetArrayLength(data);
    get_array_critical(env, data, out, dataPtr, outPtr);
    if (!check_array(env, data, out, dataPtr, outPtr)) {
        return 0;
    }
    const uint8_t *unpackedData = nullptr; uint32_t unpackedSize = 0;
    if (!do_crunch_unpack(dataPtr, dataSize, (void **)&unpackedData, &unpackedSize, useUnityCrunch)) {
        release_array_critical(env, data, out, dataPtr, outPtr, JNI_ABORT);
        return 0;
    }
    decode_etc2a8(unpackedData, w, h, outPtr);
    release_array_critical(env, data, out, dataPtr, outPtr, 0);
    return 1;
}
