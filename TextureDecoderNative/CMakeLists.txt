# Set the minimum version of CMake that can be used
cmake_minimum_required (VERSION 3.8)

# Set the project name
project("TextureDecoder")

# Set the C++ standard to C++ 14
set(CMAKE_CXX_STANDARD 14)

# Add definitions from the project file
add_compile_definitions(_T2D_DLL)
add_compile_definitions(NDEBUG)
add_compile_definitions(TEXTURE2DDECODERNATIVE_EXPORTS)

# Detect operating system
if(WIN32)
    set(OS_NAME "windows")
    set(LIB_EXTENSION "dll")
elseif(APPLE)
    set(OS_NAME "darwin")
    set(LIB_EXTENSION "dylib")
elseif(UNIX)
    set(OS_NAME "linux")
    set(LIB_EXTENSION "so")
endif()

# Detect architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(ARCH "x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
    set(ARCH "aarch64")
else()
    set(ARCH ${CMAKE_SYSTEM_PROCESSOR})
endif()

message(STATUS "Building for ${OS_NAME}-${ARCH}")

# Find JDK
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Add the given directories to those the compiler uses to search for include files
include_directories(./lib/crunch)
include_directories(./lib/fp16)
include_directories(./lib/unitycrunch)

# Generate the shared library from the library sources
add_library(TextureDecoder SHARED
        lib/crunch/crn_decomp.h
        lib/crunch/crnlib.h
        lib/fp16/bitcasts.h
        lib/fp16/fp16.h
        lib/unitycrunch/crn_decomp.h
        lib/unitycrunch/crn_defs.h
        lib/unitycrunch/crnlib.h
        lib/astc.cpp
        lib/astc.h
        lib/atc.cpp
        lib/atc.h
        lib/bcn.cpp
        lib/bcn.h
        lib/bool32_t.h
        lib/color.h
        lib/crunch.cpp
        lib/crunch.h
        lib/dllexport.h
        lib/dllmain.cpp
        lib/endianness.h
        lib/etc.cpp
        lib/etc.h
        lib/fp16.h
        lib/pvrtc.cpp
        lib/pvrtc.h
        lib/resource.h
        lib/unitycrunch.cpp
        lib/unitycrunch.h
        io_github_deficuet_unitykt_extension_TextureDecoder.h
        io_github_deficuet_unitykt_extension_TextureDecoder.cc)

# Set output directory based on OS and architecture
set_target_properties(TextureDecoder PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../src/main/resources/natives/${OS_NAME}-${ARCH}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../src/main/resources/natives/${OS_NAME}-${ARCH}"
)

# Link JNI
target_link_libraries(TextureDecoder ${JNI_LIBRARIES})

# Platform-specific settings
if(UNIX AND NOT APPLE)
    # Linux specific settings
    set_target_properties(TextureDecoder PROPERTIES
        PREFIX "lib"
        SUFFIX ".so"
    )
    target_compile_options(TextureDecoder PRIVATE -fPIC)
elseif(APPLE)
    # macOS specific settings
    set_target_properties(TextureDecoder PROPERTIES
        PREFIX "lib"
        SUFFIX ".dylib"
    )
    target_compile_options(TextureDecoder PRIVATE -fPIC)
elseif(WIN32)
    # Windows specific settings - no prefix needed
    set_target_properties(TextureDecoder PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
endif()
