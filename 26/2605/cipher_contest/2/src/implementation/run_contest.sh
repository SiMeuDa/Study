#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

gcc -O3 -Wall -Wextra -o contest_implementation contest_implementation.c
./contest_implementation

