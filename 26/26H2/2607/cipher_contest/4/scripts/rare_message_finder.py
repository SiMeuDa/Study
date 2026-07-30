#!/usr/bin/env python3
"""
rare_message_finder.py

Purpose
-------
Find rare log messages from a very large text log.

Features
--------
- Streaming (memory efficient)
- Counts message prefixes
- Counts complete messages
- Extracts entries appearing <= threshold times

Author
------
Forensic Analysis
"""

from collections import Counter
from pathlib import Path
import argparse
import re


# ------------------------------------------------------------
# Regular Expressions
# ------------------------------------------------------------

LOG_RE = re.compile(
    r'^\[(.*?)\]\s+([A-Z]+):\s+(.*)$'
)


# ------------------------------------------------------------
# Parse One Line
# ------------------------------------------------------------

def parse_line(line: str):
    """
    Parse one log line.

    Returns
    -------
    tuple(level, message) or None
    """

    m = LOG_RE.match(line)

    if not m:
        return None

    level = m.group(2)
    message = m.group(3).strip()

    return level, message


# ------------------------------------------------------------
# Prefix Extraction
# ------------------------------------------------------------

def extract_prefix(message: str) -> str:
    """
    Return prefix before variable data.

    Example

    Loading model 'TinyLlama'

    ->

    Loading model
    """

    parts = message.split()

    return " ".join(parts[:3])


# ------------------------------------------------------------
# Streaming Scan
# ------------------------------------------------------------

def scan_log(log_path: Path):

    prefix_counter = Counter()

    message_counter = Counter()

    total = 0

    with log_path.open(
        "r",
        encoding="utf-8",
        errors="replace"
    ) as f:

        for line in f:

            parsed = parse_line(line)

            if parsed is None:
                continue

            _, message = parsed

            prefix = extract_prefix(message)

            prefix_counter[prefix] += 1

            message_counter[message] += 1

            total += 1

            if total % 5_000_000 == 0:
                print(f"[+] Processed {total:,} lines")

    return prefix_counter, message_counter


# ------------------------------------------------------------
# Save Result
# ------------------------------------------------------------

def save_counter(counter, outfile, threshold):

    with open(outfile, "w", encoding="utf-8") as f:

        for text, count in sorted(
            counter.items(),
            key=lambda x: (x[1], x[0])
        ):

            if count <= threshold:

                f.write(f"[{count}] {text}\n")


# ------------------------------------------------------------
# Main
# ------------------------------------------------------------

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "logfile",
        type=Path
    )

    parser.add_argument(
        "--threshold",
        type=int,
        default=3,
        help="Maximum occurrence count"
    )

    parser.add_argument(
        "--output",
        default="rare_output"
    )

    args = parser.parse_args()

    print()

    print("Scanning log...")

    prefix_counter, message_counter = scan_log(args.logfile)

    Path(args.output).mkdir(
        exist_ok=True
    )

    save_counter(
        prefix_counter,
        Path(args.output) / "rare_prefixes.txt",
        args.threshold
    )

    save_counter(
        message_counter,
        Path(args.output) / "rare_messages.txt",
        args.threshold
    )

    print()

    print("Finished.")

    print(f"Unique Prefix : {len(prefix_counter):,}")

    print(f"Unique Message: {len(message_counter):,}")


if __name__ == "__main__":
    main()
