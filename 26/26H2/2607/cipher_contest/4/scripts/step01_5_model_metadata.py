#!/usr/bin/env python3

import hashlib
import json
from pathlib import Path

MODELS_DIR = Path("/workspace/models/extracted")


def sha256(path: Path):
    h = hashlib.sha256()

    with open(path, "rb") as f:
        while True:
            chunk = f.read(1024 * 1024)

            if not chunk:
                break

            h.update(chunk)

    return h.hexdigest()


def human_size(size):
    units = ["B", "KB", "MB", "GB"]

    idx = 0

    size = float(size)

    while size >= 1024 and idx < len(units) - 1:
        size /= 1024
        idx += 1

    return f"{size:.2f} {units[idx]}"


def read_safetensor_header(path: Path):
    """
    safetensors format

    [8-byte little endian]
    header_length

    [header_length bytes]
    json header
    """

    with open(path, "rb") as f:

        header_size = int.from_bytes(f.read(8), "little")

        header = f.read(header_size)

        try:
            return json.loads(header.decode())

        except Exception:

            return None


def print_line():

    print("=" * 90)


summary = []

print_line()
print("MODEL METADATA")
print_line()

for model in sorted(MODELS_DIR.iterdir()):

    if not model.is_dir():
        continue

    config = list(model.rglob("config.json"))

    weights = list(model.rglob("*.safetensors"))

    print_line()
    print(model.name)
    print_line()

    row = {
        "Model": model.name
    }

    #
    # config
    #

    if config:

        cfg = config[0]

        cfg_json = json.load(open(cfg))

        print("Config")

        print(" SHA256 :", sha256(cfg))

        keys = [
            "architectures",
            "model_type",
            "hidden_size",
            "num_hidden_layers",
            "vocab_size",
            "torch_dtype"
        ]

        for k in keys:

            print(f" {k:22}: {cfg_json.get(k)}")

            row[k] = cfg_json.get(k)

    else:

        print("No config found")

    print()

    #
    # weights
    #

    for w in weights:

        print("Weight")

        print(" File :", w.name)

        print(" Size :", human_size(w.stat().st_size))

        print(" SHA256 :", sha256(w))

        header = read_safetensor_header(w)

        if header is None:

            print(" Header : Failed")

        else:

            print(" Header Keys :", len(header.keys()))

            if "__metadata__" in header:

                print(" Metadata :", header["__metadata__"])

            else:

                print(" Metadata : None")

        print()

    summary.append(row)

print_line()

print("SUMMARY")

print_line()

columns = [
    "Model",
    "architectures",
    "model_type",
    "hidden_size",
    "num_hidden_layers",
    "vocab_size",
    "torch_dtype"
]

fmt = "{:<32} {:<24} {:<12} {:<10} {:<8} {:<10} {:<10}"

print(fmt.format(*columns))

print("-" * 120)

for row in summary:

    print(fmt.format(
        str(row.get("Model")),
        str(row.get("architectures")),
        str(row.get("model_type")),
        str(row.get("hidden_size")),
        str(row.get("num_hidden_layers")),
        str(row.get("vocab_size")),
        str(row.get("torch_dtype"))
    ))
