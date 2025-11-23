# ✅ Deployment Checklist - UnityKt on Linux

Use this checklist to ensure a smooth deployment to your Linux server.

---

## Pre-Deployment

### Local Setup
- [ ] Repository cloned/forked
- [ ] All documentation reviewed
- [ ] Development environment set up

### Build Native Library
Choose one method:

#### Option A: On Linux Machine
- [ ] Installed build-essential: `sudo apt-get install build-essential cmake default-jdk`
- [ ] Ran `cd TextureDecoderNative && ./build-linux.sh`
- [ ] Verified output: `ls src/main/resources/natives/linux-x86_64/libTextureDecoder.so`

#### Option B: Using Docker
- [ ] Docker installed and running
- [ ] Ran `cd TextureDecoderNative && build-linux-docker.bat` (or .sh)
- [ ] Verified output: `ls src/main/resources/natives/linux-x86_64/libTextureDecoder.so`

#### Option C: GitHub Actions
- [ ] Pushed code to GitHub
- [ ] Workflow completed successfully
- [ ] Downloaded artifact from Actions tab
- [ ] Extracted to `src/main/resources/natives/linux-x86_64/`

### Build Application
- [ ] Ran `./gradlew clean`
- [ ] Ran `./gradlew build`
- [ ] JAR created: `build/libs/UnityKt-*.jar`
- [ ] Verified JAR contains native libraries:
      ```bash
      jar tf build/libs/UnityKt-*.jar | grep "natives/linux"
      ```
      Should show `natives/linux-x86_64/libTextureDecoder.so`

### Local Testing
- [ ] Ran `./gradlew test`
- [ ] All tests passed
- [ ] Ran `./gradlew run` (if applicable)
- [ ] No `UnsatisfiedLinkError` errors
- [ ] Native library loaded successfully

---

## Server Preparation

### Server Requirements
- [ ] Linux server accessible (Ubuntu 20.04+, Debian 11+, or similar)
- [ ] SSH access configured
- [ ] Java 17+ installed on server:
      ```bash
      java -version
      ```
- [ ] Sufficient disk space (check: `df -h`)
- [ ] Required permissions for deployment directory

### Server Setup
- [ ] Created deployment directory:
      ```bash
      mkdir -p /opt/unitykt
      ```
- [ ] Set proper permissions:
      ```bash
      sudo chown $USER:$USER /opt/unitykt
      ```
- [ ] Created logs directory:
      ```bash
      mkdir -p /opt/unitykt/logs
      ```
- [ ] Ensured temp directory is writable:
      ```bash
      test -w /tmp && echo "OK" || echo "NOT WRITABLE"
      ```

### Firewall Configuration (if applicable)
- [ ] Opened required port (e.g., 8080):
      ```bash
      sudo ufw allow 8080/tcp
      ```
- [ ] Verified firewall status:
      ```bash
      sudo ufw status
      ```

---

## Deployment

### File Transfer
- [ ] Copied JAR to server:
      ```bash
      scp build/libs/UnityKt-*.jar user@server:/opt/unitykt/
      ```
- [ ] Verified file exists on server:
      ```bash
      ssh user@server "ls -lh /opt/unitykt/*.jar"
      ```
- [ ] Copied configuration files (if any)
- [ ] Set executable permissions (if needed)

### Environment Variables (if needed)
- [ ] Created `.env` file or set environment variables
- [ ] Set `JAVA_HOME` if required
- [ ] Set `JAVA_OPTS` for JVM tuning:
      ```bash
      export JAVA_OPTS="-Xmx2g -Xms512m"
      ```

---

## Initial Testing

### Manual Test
- [ ] SSH into server
- [ ] Navigate to deployment directory:
      ```bash
      cd /opt/unitykt
      ```
- [ ] Run application manually:
      ```bash
      java -jar UnityKt-*.jar
      ```
- [ ] Verified output shows:
      - [ ] Platform detected as Linux
      - [ ] Native library loaded successfully
      - [ ] No errors or exceptions
      - [ ] Application started correctly

### Health Check
- [ ] Tested health endpoint (if applicable):
      ```bash
      curl http://localhost:8080/health
      ```
- [ ] Expected response received
- [ ] Checked logs for errors

### Functional Test
- [ ] Uploaded test Unity bundle
- [ ] Verified processing works
- [ ] Checked texture decoding functions
- [ ] Reviewed output/response

---

## Production Setup

### Choose Deployment Method

#### Option A: Systemd Service
- [ ] Created service file: `/etc/systemd/system/unitykt.service`
      ```ini
      [Unit]
      Description=UnityKt Service
      After=network.target

      [Service]
      Type=simple
      User=unitykt-user
      WorkingDirectory=/opt/unitykt
      ExecStart=/usr/bin/java -Xmx2g -jar /opt/unitykt/UnityKt-*.jar
      Restart=on-failure
      RestartSec=10

      [Install]
      WantedBy=multi-user.target
      ```
- [ ] Reloaded systemd:
      ```bash
      sudo systemctl daemon-reload
      ```
- [ ] Enabled service:
      ```bash
      sudo systemctl enable unitykt
      ```
- [ ] Started service:
      ```bash
      sudo systemctl start unitykt
      ```
- [ ] Checked status:
      ```bash
      sudo systemctl status unitykt
      ```
- [ ] Verified logs:
      ```bash
      sudo journalctl -u unitykt -f
      ```

#### Option B: Docker Container
- [ ] Created Dockerfile
- [ ] Built Docker image:
      ```bash
      docker build -t unitykt .
      ```
- [ ] Tested locally:
      ```bash
      docker run -p 8080:8080 unitykt
      ```
- [ ] Tagged for registry (if using):
      ```bash
      docker tag unitykt registry.example.com/unitykt:latest
      ```
- [ ] Pushed to registry:
      ```bash
      docker push registry.example.com/unitykt:latest
      ```
- [ ] Deployed on server:
      ```bash
      docker pull registry.example.com/unitykt:latest
      docker run -d -p 8080:8080 --name unitykt \
        --restart unless-stopped \
        registry.example.com/unitykt:latest
      ```
- [ ] Verified container running:
      ```bash
      docker ps | grep unitykt
      ```

#### Option C: Docker Compose
- [ ] Created `docker-compose.yml`
- [ ] Started services:
      ```bash
      docker-compose up -d
      ```
- [ ] Checked status:
      ```bash
      docker-compose ps
      ```
- [ ] Verified logs:
      ```bash
      docker-compose logs -f
      ```

---

## Post-Deployment Verification

### Functionality Tests
- [ ] Application responds to requests
- [ ] All endpoints working
- [ ] File uploads functioning
- [ ] Bundle processing successful
- [ ] Texture decoding working
- [ ] Error handling correct

### Performance Tests
- [ ] Response times acceptable
- [ ] Memory usage within limits
- [ ] CPU usage reasonable
- [ ] No memory leaks detected

### Load Tests (if applicable)
- [ ] Tested with concurrent requests
- [ ] Verified stability under load
- [ ] Confirmed resource usage scales appropriately

---

## Monitoring Setup

### Logging
- [ ] Configured log rotation:
      ```bash
      sudo nano /etc/logrotate.d/unitykt
      ```
- [ ] Logs being written correctly
- [ ] Log levels appropriate
- [ ] Sensitive data not logged

### Monitoring
- [ ] Set up health check monitoring
- [ ] Configured alerts for failures
- [ ] CPU/Memory monitoring enabled
- [ ] Disk space monitoring active

### Metrics (if applicable)
- [ ] Application metrics exposed
- [ ] Metrics collection configured
- [ ] Dashboards created

---

## Security

### Application Security
- [ ] Using HTTPS (if applicable)
- [ ] Authentication configured (if needed)
- [ ] Rate limiting enabled (if needed)
- [ ] Input validation working
- [ ] File upload limits set

### Server Security
- [ ] SSH key-based authentication only
- [ ] Firewall properly configured
- [ ] Unnecessary ports closed
- [ ] Regular security updates enabled
- [ ] Application running as non-root user

### Access Control
- [ ] API authentication configured
- [ ] Authorization rules set
- [ ] Secrets/credentials secured
- [ ] Environment variables protected

---

## Backup & Recovery

### Backup Strategy
- [ ] Backup plan defined
- [ ] Configuration files backed up
- [ ] Data backup configured (if applicable)
- [ ] Backup restoration tested

### Disaster Recovery
- [ ] Recovery procedure documented
- [ ] Rollback plan defined
- [ ] Previous version kept available

---

## Documentation

### Operations Documentation
- [ ] Deployment procedure documented
- [ ] Configuration documented
- [ ] Troubleshooting guide created
- [ ] Contact information updated

### Runbooks
- [ ] Start/stop procedures
- [ ] Restart procedures
- [ ] Log locations documented
- [ ] Common issues & solutions

---

## Final Checks

### Functionality
- [x] Native library loads correctly on Linux
- [x] All texture formats decode successfully
- [x] Application handles errors gracefully
- [x] Memory management working correctly

### Performance
- [ ] Response times meeting requirements
- [ ] Resource usage acceptable
- [ ] No memory leaks
- [ ] Concurrent requests handled properly

### Reliability
- [ ] Application auto-restarts on failure
- [ ] Logs being captured
- [ ] Monitoring active
- [ ] Alerts configured

### Maintenance
- [ ] Update procedure defined
- [ ] Rollback procedure tested
- [ ] Team trained on operations
- [ ] Documentation complete

---

## Go-Live Checklist

### Pre-Launch
- [ ] All previous checklist items completed
- [ ] Stakeholders notified
- [ ] Maintenance window scheduled (if needed)
- [ ] Rollback plan ready

### Launch
- [ ] Application started successfully
- [ ] Health checks passing
- [ ] No errors in logs
- [ ] Monitoring showing green

### Post-Launch
- [ ] Monitored for first 24 hours
- [ ] Performance metrics reviewed
- [ ] User feedback collected
- [ ] Issues addressed promptly

---

## Success Criteria

✅ **Application Running**
   - Service/container running
   - Responds to health checks
   - No errors in logs

✅ **Functionality Verified**
   - Unity bundles process correctly
   - Textures decode successfully
   - All formats supported

✅ **Performance Acceptable**
   - Response times < requirement
   - Memory usage stable
   - CPU usage reasonable

✅ **Monitoring Active**
   - Health checks running
   - Logs accessible
   - Alerts configured

✅ **Documentation Complete**
   - Operations guide written
   - Troubleshooting documented
   - Team trained

---

## Quick Commands Reference

```bash
# Check service status
sudo systemctl status unitykt

# View logs
sudo journalctl -u unitykt -f

# Restart service
sudo systemctl restart unitykt

# Check if library is loaded
lsof -p $(pgrep -f unitykt) | grep libTextureDecoder

# Monitor resources
top -p $(pgrep -f unitykt)

# Check disk space
df -h

# View recent errors
sudo journalctl -u unitykt -p err -n 50

# Test endpoint
curl http://localhost:8080/health
```

---

## Troubleshooting Quick Reference

| Symptom | Check | Solution |
|---------|-------|----------|
| UnsatisfiedLinkError | JAR contains .so | Rebuild with native lib |
| Port already in use | `netstat -tlnp \| grep 8080` | Change port or kill process |
| Out of memory | `free -h` | Increase `-Xmx` value |
| Service won't start | `journalctl -xe` | Check logs for error |
| Slow response | `top`, `htop` | Check resources, optimize |

---

**Deployment Complete!** 🎉

Your UnityKt application is now running on Linux with full native library support!
