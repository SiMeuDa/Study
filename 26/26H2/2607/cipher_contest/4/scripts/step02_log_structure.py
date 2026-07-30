#!/usr/bin/env python3

import json
from pathlib import Path
from collections import Counter

LOG_FILE = Path("/workspace/logs/extracted/server.log")

SAMPLE_COUNT = 5


def human_size(size):
    units = ["B", "KB", "MB", "GB", "TB"]
    size = float(size)
    idx = 0

    while size >= 1024 and idx < len(units) - 1:
        size /= 1024
        idx += 1

    return f"{size:.2f} {units[idx]}"


print("=" * 90)
print("SERVER.LOG STRUCTURE ANALYZER")
print("=" * 90)

if not LOG_FILE.exists():
    print(f"ERROR: {LOG_FILE} not found.")
    exit(1)

print(f"File : {LOG_FILE}")
print(f"Size : {human_size(LOG_FILE.stat().st_size)}")
print()

line_count = 0
json_count = 0
decode_errors = 0

key_counter = Counter()
role_counter = Counter()
top_level_types = Counter()

max_line_length = 0
max_line_number = 0

sample_lines = []

timestamp_examples = []

total_line_length = 0

with open(LOG_FILE, "rb") as f:

    for raw in f:

        line_count += 1

        try:
            line = raw.decode("utf-8").rstrip("\n")

        except UnicodeDecodeError:
            decode_errors += 1
            continue

        length = len(line)

        total_line_length += length

        if length > max_line_length:
            max_line_length = length
            max_line_number = line_count

        if len(sample_lines) < SAMPLE_COUNT:
            sample_lines.append(line[:500])

        line = line.strip()

        if not line:
            continue

        if line[0] not in "{[":
            continue

        try:
            obj = json.loads(line)

            json_count += 1

            top_level_types[type(obj).__name__] += 1

            if isinstance(obj, dict):

                for k in obj.keys():
                    key_counter[k] += 1

                if "role" in obj:
                    role_counter[str(obj["role"])] += 1

                for t in (
                    "timestamp",
                    "time",
                    "datetime",
                    "created_at",
                    "created",
                ):
                    if t in obj and len(timestamp_examples) < 5:
                        timestamp_examples.append(obj[t])

        except Exception:
            pass

print("=" * 90)
print("BASIC STATISTICS")
print("=" * 90)

print(f"Lines                 : {line_count:,}")
print(f"JSON Records          : {json_count:,}")
print(f"Decode Errors         : {decode_errors:,}")

if line_count:
    print(f"Average Line Length   : {total_line_length / line_count:.2f}")

print(f"Longest Line          : {max_line_length:,}")
print(f"Longest Line Number   : {max_line_number:,}")

print()

print("=" * 90)
print("TOP LEVEL JSON TYPES")
print("=" * 90)

if top_level_types:
    for t, c in top_level_types.most_common():
        print(f"{t:20} {c}")
else:
    print("No JSON detected.")

print()

print("=" * 90)
print("TOP KEYS")
print("=" * 90)

if key_counter:
    for k, c in key_counter.most_common(30):
        print(f"{k:30} {c}")
else:
    print("No JSON keys found.")

print()

print("=" * 90)
print("ROLES")
print("=" * 90)

if role_counter:
    for k, c in role_counter.items():
        print(f"{k:20} {c}")
else:
    print("No role field detected.")

print()

print("=" * 90)
print("TIMESTAMP EXAMPLES")
print("=" * 90)

if timestamp_examples:
    for t in timestamp_examples:
        print(t)
else:
    print("No timestamp field detected.")

print()

print("=" * 90)
print("FIRST SAMPLE LINES")
print("=" * 90)

for i, line in enumerate(sample_lines, 1):
    print(f"[{i}]")
    print(line)
    print("-" * 60)

print()

print("=" * 90)
print("SUMMARY")
print("=" * 90)

if json_count == line_count:
    print("Format : JSON Lines (JSONL)")
elif json_count == 0:
    print("Format : Plain Text")
else:
    print("Format : Mixed")

print()

print("Analysis Complete.")
