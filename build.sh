#!/usr/bin/env bash
# build.sh  --  usage: ./build.sh [build|clean|rebuild|run]   (V=1 for full commands)
set -euo pipefail

# ---------- config ----------
NAME="paxon"
PROJ="Paxon"
TARGET="aarch64-unknown-linux"
SRC_DIR="src"
INC_DIRS=(includes .)
BUILD_DIR="build"
LINKER_SCRIPT=""
ENTRY=""                       # e.g. ENTRY=_start ./build.sh  (if linker.ld has no ENTRY())
LD_EMU="aarch64elf"            # arm64pe only if you're making a PE/EFI image
JOBS="$(nproc)"

CC=clang CXX=clang++ AS=clang LD=ld.lld
BIN="$BUILD_DIR/$NAME"

inc=(); for d in "${INC_DIRS[@]}"; do inc+=("-I$d"); done

COMMON=(
	--target="$TARGET"
	-ffreestanding
	-g -gdwarf
        
	-Wall -Wextra -Werror
	-Wno-unused-variable -Wno-unused-command-line-argument
        
	-fno-unwind-tables -fno-asynchronous-unwind-tables
        
	"${inc[@]}" -MMD -MP
)

CFLAGS=("${COMMON[@]}" --std=c23 -fno-stack-protector)

CXXFLAGS=("${COMMON[@]}" --std=c++26 -fno-exceptions -fno-rtti -fshort-wchar
          -nostdinc++ -Wno-c++17-extensions -fno-stack-protector)

ASFLAGS=("${COMMON[@]}")
LDFLAGS=(-m "$LD_EMU" -nostdlib)
[[ -n "$ENTRY" ]] && LDFLAGS+=(-e "$ENTRY")

SELF="${BASH_SOURCE[0]}"

# ---------- helpers ----------
log() { printf '[%-3s] %s\n' "$1" "$2"; }
run() { [[ -n "${V:-}" ]] && printf '  $ %s\n' "$*"; "$@"; }

# does this object need rebuilding?
stale() {
    local src=$1 obj=$2 dep="${2%.o}.d" f
    [[ -f $obj && -f $dep ]] || return 0
    [[ $src -nt $obj || $SELF -nt $obj ]] && return 0
    while read -r f; do
        [[ $f -nt $obj ]] && return 0
    done < <(sed -e 's/^[^:]*://' -e 's/\\$//' "$dep" | tr -s ' ' '\n' | grep . || true)
    return 1
}

compile() {
    local src=$1 obj=$2 tag
    mkdir -p "$(dirname "$obj")"
    case "$src" in
        *.c)       log CC  "$src"; run "$CC"  "${CFLAGS[@]}"   -c "$src" -o "$obj" ;;
        *.cpp)     log CXX "$src"; run "$CXX" "${CXXFLAGS[@]}" -c "$src" -o "$obj" ;;
        *.s|*.S)   log AS  "$src"; run "$AS"  "${ASFLAGS[@]}"  -c "$src" -o "$obj" ;;
    esac
}

# ---------- commands ----------
do_clean() { rm -rf "$BUILD_DIR"; log RM "$BUILD_DIR"; }

do_build() {
    printf '======== BUILDING %s ========\n' "$PROJ"
    mkdir -p "$BUILD_DIR"

    local objs=() fail=0 src obj
    while IFS= read -r -d '' src; do
        obj="$BUILD_DIR/${src#"$SRC_DIR"/}.o"      # foo.c -> build/foo.c.o (no foo.c/foo.S clash)
        objs+=("$obj")
        stale "$src" "$obj" || continue

        while (( $(jobs -rp | wc -l) >= JOBS )); do wait -n || fail=1; done
        compile "$src" "$obj" &
    done < <(find "$SRC_DIR" -type f \( -name '*.c' -o -name '*.cpp' -o -name '*.s' -o -name '*.S' \) -print0 | sort -z)

    while (( $(jobs -rp | wc -l) > 0 )); do wait -n || fail=1; done
    (( fail )) && { echo "build failed" >&2; exit 1; }

    # relink only if something changed
    local relink=0
    [[ -f $BIN && ! $LINKER_SCRIPT -nt $BIN && ! $SELF -nt $BIN ]] || relink=1
    for obj in "${objs[@]}"; do [[ $obj -nt $BIN ]] && relink=1; done

    if (( relink )); then
        log LD "$BIN"
        run "$LD" "${LDFLAGS[@]}" "${objs[@]}" -o "$BIN"
    else
        echo "nothing to do"
    fi
}

case "${1:-build}" in
    build)   do_build ;;
    clean)   do_clean ;;
    rebuild) do_clean; do_build ;;
    run)     do_build; pkill qemu-system-aar || true; ./qemu.sh ;;
    *)       echo "usage: $0 [build|clean|rebuild|run]" >&2; exit 2 ;;
esac
