#!/bin/bash
# Linux build script for TextureDecoder
# Flags:
#   --clean  Remove build directory before configuring
#   --help   Show usage

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build-linux"

usage() {
    cat <<EOF
Usage: ./build-linux.sh [--clean]
    --clean    Remove build directory before build
    --help     Show this help
EOF
}

log() { printf '%s\n' "[INFO] $*"; }
warn() { printf '%s\n' "[WARN] $*"; }
err()  { printf '%s\n' "[ERROR] $*" >&2; }

remove_dir() {
    local target="$1"
    [[ -d "$target" ]] || return 0
    log "Removing dir: $target"
    if rm -rf "$target" 2>/dev/null; then return 0; fi
    warn "Direct removal failed; fixing permissions"
    if command -v sudo >/dev/null 2>&1; then
        sudo chown -R "$USER":"$USER" "$target" 2>/dev/null || true
        sudo chmod -R u+w "$target" 2>/dev/null || true
        sudo rm -rf "$target" 2>/dev/null && return 0 || true
    fi
    err "Remoção automática falhou. Execute manualmente:"
    err "  sudo chown -R $USER:$USER '$target' && sudo rm -rf '$target'"
    err "Ou via PowerShell: Remove-Item -Recurse -Force '$target'"
    exit 1
}

is_stale_cache() {
    local cache="$BUILD_DIR/CMakeCache.txt"
    [[ -f "$cache" ]] || return 1
    local home_line source_dir
    home_line=$(grep '^CMAKE_HOME_DIRECTORY:INTERNAL=' "$cache" || true)
    if grep -q '^CMAKE_HOME_DIRECTORY:INTERNAL=/workspace' "$cache"; then return 0; fi
    if [[ -n "$home_line" ]]; then
        source_dir="${home_line##*=}"
        [[ "$source_dir" != "$SCRIPT_DIR" ]] && return 0
    fi
    return 1
}

force_clean=false
for arg in "${@:-}"; do
    case "$arg" in
        --clean) force_clean=true ;;
        --help) usage; exit 0 ;;
        *) err "Unknown arg: $arg"; usage; exit 1 ;;
    esac
done

if $force_clean; then remove_dir "$BUILD_DIR"; fi
if is_stale_cache; then
    log "Stale CMake cache detected (path mismatch)."
    remove_dir "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

log "Configuring (source: $SCRIPT_DIR)"
cmake -S "$SCRIPT_DIR" -B . -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON

log "Building"
cmake --build . --config Release -- -j"$(nproc 2>/dev/null || echo 4)"

log "Done"
log "Output: $SCRIPT_DIR/../src/main/resources/natives/linux-x86_64/libTextureDecoder.so"
