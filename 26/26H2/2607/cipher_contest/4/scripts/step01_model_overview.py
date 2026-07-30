#!/usr/bin/env python3

import json
from pathlib import Path

MODELS_DIR = Path("/workspace/models/extracted")


def human_size(size):
    units = ["B", "KB", "MB", "GB", "TB"]
    i = 0
    size = float(size)

    while size >= 1024 and i < len(units) - 1:
        size /= 1024
        i += 1

    return f"{size:.2f} {units[i]}"


def print_line():
    print("=" * 80)


def inspect_model(model_root):
    print_line()
    print(f"Model : {model_root.name}")
    print_line()

    files = list(model_root.rglob("*"))

    safetensors = list(model_root.rglob("*.safetensors"))
    bins = list(model_root.rglob("*.bin"))

    config = list(model_root.rglob("config.json"))

    tokenizer = list(model_root.rglob("tokenizer*"))

    print(f"Total Files        : {len(files)}")
    print(f"Safetensors        : {len(safetensors)}")
    print(f"PyTorch Bin        : {len(bins)}")
    print(f"Tokenizer Files    : {len(tokenizer)}")
    print()

    if safetensors:
        print("Weight Files")

        for f in safetensors:
            print(f"  {f.relative_to(model_root)}")
            print(f"    Size : {human_size(f.stat().st_size)}")

        print()

    if bins:
        print("PyTorch Files")

        for f in bins:
            print(f"  {f.relative_to(model_root)}")
            print(f"    Size : {human_size(f.stat().st_size)}")

        print()

    if config:

        cfg_path = config[0]

        print("Config")

        with open(cfg_path, "r", encoding="utf-8") as fp:
            cfg = json.load(fp)

        keys = [
            "architectures",
            "model_type",
            "hidden_size",
            "intermediate_size",
            "num_hidden_layers",
            "num_attention_heads",
            "num_key_value_heads",
            "vocab_size",
            "max_position_embeddings",
            "torch_dtype"
        ]

        for k in keys:

            if k in cfg:
                print(f"  {k:28}: {cfg[k]}")

        print()
        print(f"Total Config Keys : {len(cfg.keys())}")

    else:
        print("Config : NOT FOUND")

    print()
    print("Top Level Files")

    for f in sorted(model_root.iterdir()):
        print(" ", f.name)

    print()


def main():

    print_line()
    print("MODEL OVERVIEW")
    print_line()

    model_dirs = []

    for item in MODELS_DIR.iterdir():

        if item.is_dir():

            # 실제 모델 디렉터리 찾기
            subdirs = [d for d in item.iterdir() if d.is_dir()]

            if len(subdirs) == 1:
                model_dirs.append(subdirs[0])
            else:
                model_dirs.append(item)

    for m in sorted(model_dirs):
        inspect_model(m)


if __name__ == "__main__":
    main()
