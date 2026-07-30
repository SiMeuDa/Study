#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

gcc contest_fast.c -o contest_fast -O3 -march=native -mtune=native -flto -fomit-frame-pointer -frename-registers -funroll-loops
./contest_fast

