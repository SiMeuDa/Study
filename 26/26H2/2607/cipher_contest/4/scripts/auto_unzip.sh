#!/bin/bash

mkdir -p extracted

for zip in *.zip; do
    name="${zip%.zip}"
    echo "[+] Extracting $zip"
    mkdir -p "extracted/$name"
    unzip -q "$zip" -d "extracted/$name"
done
