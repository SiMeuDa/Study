#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

gcc -O3 -Wall -Wextra -march=meteorlake -mtune=meteorlake -mavx2 -mbmi2 -flto -funroll-loops -fomit-frame-pointer -o contest improve.c
./contest

