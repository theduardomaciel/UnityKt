@echo off
REM Build script for Windows

echo Building TextureDecoder for Windows...

REM Create build directory
set BUILD_DIR=build-windows
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Configure CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64

REM Build
cmake --build . --config Release

echo Build completed successfully!
echo Library output: ..\src\main\resources\natives\windows-x86_64\TextureDecoder.dll

cd ..
