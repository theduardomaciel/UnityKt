# Set the minimum version of CMake that can be used
cmake_minimum_required (VERSION 3.8)

# Set the project name
project("TextureDecoder")

# Set the C++ standard to C++ 14
set(CMAKE_CXX_STANDARD 14)

# Add definitions from the project file
# 'Release|x64'
# <PreprocessorDefinitions>_T2D_DLL;NDEBUG;TEXTURE2DDECODERNATIVE_EXPORTS;_WINDOWS;_USRDLL;%(PreprocessorDefinitions)</PreprocessorDefinitions>
add_compile_definitions(_T2D_DLL)
add_compile_definitions(NDEBUG)
add_compile_definitions(TEXTURE2DDECODERNATIVE_EXPORTS)

# Add the given directories to those the compiler uses to search for include files
include_directories("C:/Program Files/Java/jdk-17.0.12+7/include")
include_directories("C:/Program Files/Java/jdk-17.0.12+7/include/win32")
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
