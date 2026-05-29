#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

gcc -O3 -Wall -Wextra -o contest contest.c
./contest

