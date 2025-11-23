@echo off
REM Generate JNI header from TextureDecoder.java
REM Requires Gradle build to compile Kotlin dependencies first

echo Building project with Gradle...
cd ..
call gradlew.bat compileJava compileKotlin
if errorlevel 1 (
    echo [ERROR] Gradle build failed
    pause
    exit /b 1
)

echo Generating JNI header...
cd TextureDecoderNative
javac -h ./ -cp "../build/classes/java/main;../build/classes/kotlin/main" ../src/main/java/io/github/deficuet/unitykt/extension/TextureDecoder.java
if errorlevel 1 (
    echo [ERROR] Header generation failed
    pause
    exit /b 1
)

echo [SUCCESS] Header generated: io_github_deficuet_unitykt_extension_TextureDecoder.h
pause