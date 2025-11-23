# 📖 Documentation Index - UnityKt Multi-Platform Support

Welcome! This index helps you find the right documentation for your needs.

---

## 🎯 I Want To...

### ...Get Started Quickly
→ **[QUICKSTART.md](QUICKSTART.md)**
- Fastest way to build for Linux
- 3 simple options: Linux machine, Docker, or GitHub Actions
- 5-minute setup guide

### ...Deploy to a Linux Server
→ **[LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md)**
- Complete server deployment guide
- Ktor and Spring Boot examples
- Docker deployment
- Systemd service setup
- Performance tuning

### ...See Code Examples
→ **[EXAMPLE_API.md](EXAMPLE_API.md)**
- Full Ktor REST API example
- Full Spring Boot REST API example
- Gradle configuration
- Docker setup
- API testing examples

### ...Build Native Libraries
→ **[BUILD.md](BUILD.md)**
- Detailed build instructions for all platforms
- Prerequisites for Linux, Windows, macOS
- Cross-compilation guide
- Troubleshooting section
- CI/CD integration

### ...Understand the Technical Details
→ **[NATIVE_SETUP.md](NATIVE_SETUP.md)**
- Complete technical overview
- How the loader works
- Platform detection mechanism
- Directory structure explanation
- File checklist

### ...See What Changed
→ **[SUMMARY.md](SUMMARY.md)**
- Complete summary of all changes
- Files created and modified
- Before/after comparison
- Platform support matrix
- Success criteria checklist

### ...Contribute Upstream
→ **[PULL_REQUEST_TEMPLATE.md](PULL_REQUEST_TEMPLATE.md)**
- Ready-to-use PR description
- Testing checklist
- Migration guide
- Platform support documentation

### ...Work with Native Code
→ **[TextureDecoderNative/README.md](TextureDecoderNative/README.md)**
- Native library overview
- Supported texture formats
- Architecture explanation
- JNI header regeneration

---

## 📁 Quick File Reference

### Documentation Files
| File | Purpose |
|------|---------|
| `QUICKSTART.md` | 5-minute quick start guide |
| `BUILD.md` | Comprehensive build instructions |
| `LINUX_SERVER_GUIDE.md` | Server deployment guide |
| `EXAMPLE_API.md` | Complete code examples |
| `NATIVE_SETUP.md` | Technical deep dive |
| `SUMMARY.md` | Overview of all changes |
| `PULL_REQUEST_TEMPLATE.md` | PR template for upstream |

### Build Scripts
| File | Purpose |
|------|---------|
| `TextureDecoderNative/build-linux.sh` | Build on Linux |
| `TextureDecoderNative/build-windows.bat` | Build on Windows |
| `TextureDecoderNative/build-darwin.sh` | Build on macOS |
| `TextureDecoderNative/build-linux-docker.sh` | Cross-compile with Docker (bash) |
| `TextureDecoderNative/build-linux-docker.bat` | Cross-compile with Docker (Windows) |

### Core Implementation
| File | Purpose |
|------|---------|
| `TextureDecoderNative/CMakeLists.txt` | Cross-platform build config |
| `src/.../NativeUtils.kt` | Platform detection & loading |
| `src/.../TextureDecoder.java` | JNI interface |

### CI/CD
| File | Purpose |
|------|---------|
| `.github/workflows/build-natives.yml` | Automated builds |

---

## 🎓 Learning Path

### Beginner (Just want it to work)
1. Read [QUICKSTART.md](QUICKSTART.md)
2. Choose Option B (Docker) if on Windows
3. Follow the 5 steps
4. Done! ✅

### Intermediate (Want to deploy to server)
1. Read [QUICKSTART.md](QUICKSTART.md) first
2. Then read [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md)
3. Check [EXAMPLE_API.md](EXAMPLE_API.md) for code samples
4. Deploy using Docker or systemd

### Advanced (Want to understand everything)
1. Start with [SUMMARY.md](SUMMARY.md) for overview
2. Read [NATIVE_SETUP.md](NATIVE_SETUP.md) for technical details
3. Review [BUILD.md](BUILD.md) for build process
4. Check [PULL_REQUEST_TEMPLATE.md](PULL_REQUEST_TEMPLATE.md) to contribute

---

## 🔍 Find By Topic

### Building
- **All Platforms**: [BUILD.md](BUILD.md)
- **Linux Specific**: [QUICKSTART.md](QUICKSTART.md) + [BUILD.md](BUILD.md)
- **Docker Build**: [QUICKSTART.md](QUICKSTART.md) → Option B
- **CI/CD**: [BUILD.md](BUILD.md) → CI/CD Integration section

### Deployment
- **Linux Server**: [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md)
- **Docker**: [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md) → Docker section
- **Systemd**: [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md) → Systemd section

### Code Examples
- **Ktor**: [EXAMPLE_API.md](EXAMPLE_API.md) → Example 1
- **Spring Boot**: [EXAMPLE_API.md](EXAMPLE_API.md) → Example 2
- **Gradle**: [EXAMPLE_API.md](EXAMPLE_API.md) → Example 3
- **Docker**: [EXAMPLE_API.md](EXAMPLE_API.md) → Example 4

### Troubleshooting
- **Build Issues**: [BUILD.md](BUILD.md) → Troubleshooting
- **Runtime Issues**: [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md) → Troubleshooting
- **Quick Reference**: [SUMMARY.md](SUMMARY.md) → Troubleshooting Quick Reference

### Technical Details
- **How It Works**: [NATIVE_SETUP.md](NATIVE_SETUP.md)
- **Platform Detection**: [SUMMARY.md](SUMMARY.md) → What Changed Under the Hood
- **Directory Structure**: [NATIVE_SETUP.md](NATIVE_SETUP.md) → Directory Structure
- **Loading Process**: [SUMMARY.md](SUMMARY.md) → Loading Process diagram

---

## 💡 Common Scenarios

### Scenario 1: "I need to run UnityKt on my Linux server"
→ Go to [QUICKSTART.md](QUICKSTART.md)

### Scenario 2: "I want to build a REST API that processes Unity bundles"
→ Go to [EXAMPLE_API.md](EXAMPLE_API.md)

### Scenario 3: "The build fails with 'jni.h not found'"
→ Go to [BUILD.md](BUILD.md) → Troubleshooting → "Build fails on Linux"

### Scenario 4: "I want to contribute this to the original repository"
→ Go to [PULL_REQUEST_TEMPLATE.md](PULL_REQUEST_TEMPLATE.md)

### Scenario 5: "I need to understand how platform detection works"
→ Go to [NATIVE_SETUP.md](NATIVE_SETUP.md) → How It Works

### Scenario 6: "I want to deploy with Docker"
→ Go to [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md) → Docker Deployment

### Scenario 7: "What files do I need to build?"
→ Go to [SUMMARY.md](SUMMARY.md) → File Checklist

---

## 🚀 Quick Links

- **Main README**: [README.md](README.md)
- **Native Library README**: [TextureDecoderNative/README.md](TextureDecoderNative/README.md)
- **Build Config**: [TextureDecoderNative/CMakeLists.txt](TextureDecoderNative/CMakeLists.txt)
- **Tests**: [src/test/kotlin/.../NativeLibraryTest.kt](src/test/kotlin/io/github/deficuet/unitykt/test/NativeLibraryTest.kt)

---

## 📊 Documentation Stats

- **Total Documentation Files**: 8
- **Total Build Scripts**: 5
- **Code Examples**: 5
- **Supported Platforms**: 4 (Windows x64, Linux x64, macOS x64, macOS ARM64)
- **Lines of Documentation**: ~2000+
- **Total Implementation**: Complete ✅

---

## 🤝 Need Help?

1. Check the appropriate documentation file above
2. Look in the Troubleshooting sections
3. Check [SUMMARY.md](SUMMARY.md) for quick reference
4. Review the code examples in [EXAMPLE_API.md](EXAMPLE_API.md)

---

## ✅ Quick Checklist

**For Immediate Use:**
- [ ] Read [QUICKSTART.md](QUICKSTART.md)
- [ ] Choose build method (Linux, Docker, or CI)
- [ ] Build native library
- [ ] Test with `./gradlew run`
- [ ] Deploy to server

**For Production Deployment:**
- [ ] Read [LINUX_SERVER_GUIDE.md](LINUX_SERVER_GUIDE.md)
- [ ] Review [EXAMPLE_API.md](EXAMPLE_API.md)
- [ ] Set up Docker or systemd
- [ ] Configure monitoring
- [ ] Set up health checks

**For Contributing:**
- [ ] Read [PULL_REQUEST_TEMPLATE.md](PULL_REQUEST_TEMPLATE.md)
- [ ] Build for all platforms
- [ ] Run tests
- [ ] Update documentation if needed
- [ ] Submit PR

---

**This is your complete guide to UnityKt multi-platform support!** 🎉

Start with [QUICKSTART.md](QUICKSTART.md) and you'll be up and running in minutes.
