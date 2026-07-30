#!/usr/bin/env python3

import re
from pathlib import Path
from collections import Counter

LOG = Path("/workspace/logs/extracted/server.log")
OUTPUT = Path("/workspace/outputs/log_profiler.txt")

TOP_MESSAGE_PREFIX = 50
TOP_MODEL = 20
TOP_HOUR = 48

KEYWORDS = [
    "secret",
    "key",
    "flag",
    "weather",
    "temperature",
    "stegan",
    "encode",
    "decode",
    "hidden",
    "embed",
    "watermark",
    "prompt",
    "system",
    "developer",
    "assistant",
    "user",
    "tool",
    "inject",
    "token",
    "inference",
    "generate",
    "completion",
]

LEVEL_RE = re.compile(
    r"^\[(.*?)\]\s+([A-Z]+):\s+(.*)$"
)

MODEL_RE = re.compile(
    r"'([^']+)'"
)

stats = {
    "lines": 0,
    "bad": 0,
}

level_counter = Counter()
hour_counter = Counter()
model_counter = Counter()
keyword_counter = Counter()
message_prefix_counter = Counter()

first_timestamp = None
last_timestamp = None


def out(fp, text=""):
    fp.write(str(text) + "\n")


def line(fp):
    out(fp, "=" * 90)


OUTPUT.parent.mkdir(parents=True, exist_ok=True)

with OUTPUT.open("w", encoding="utf-8") as report:

    line(report)
    out(report, "LOG PROFILER")
    line(report)

    with open(LOG, "r", encoding="utf-8", errors="ignore") as f:

        for line_text in f:

            stats["lines"] += 1

            line_text = line_text.rstrip()

            m = LEVEL_RE.match(line_text)

            if not m:
                stats["bad"] += 1
                continue

            timestamp, level, message = m.groups()

            if first_timestamp is None:
                first_timestamp = timestamp

            last_timestamp = timestamp

            level_counter[level] += 1

            if len(timestamp) >= 13:
                hour_counter[timestamp[:13]] += 1

            for name in MODEL_RE.findall(message):
                model_counter[name] += 1

            msg_lower = message.lower()

            for k in KEYWORDS:
                if k in msg_lower:
                    keyword_counter[k] += 1

            prefix = message.split(".", 1)[0]
            prefix = prefix.split(":", 1)[0]
            prefix = prefix.strip()

            if len(prefix) > 100:
                prefix = prefix[:100]

            message_prefix_counter[prefix] += 1

    line(report)
    out(report, "GENERAL")
    line(report)

    out(report, f"Total Lines        : {stats['lines']:,}")
    out(report, f"Parse Failure      : {stats['bad']:,}")
    out(report)

    out(report, f"First Timestamp    : {first_timestamp}")
    out(report, f"Last Timestamp     : {last_timestamp}")

    out(report)
    line(report)
    out(report, "LOG LEVELS")
    line(report)

    for level, cnt in level_counter.most_common():
        out(report, f"{level:12} {cnt:,}")

    out(report)
    line(report)
    out(report, "MODELS")
    line(report)

    for model, cnt in model_counter.most_common(TOP_MODEL):
        out(report, f"{model:45} {cnt:,}")

    out(report)
    line(report)
    out(report, "KEYWORDS")
    line(report)

    for k in KEYWORDS:
        out(report, f"{k:15} {keyword_counter[k]:,}")

    out(report)
    line(report)
    out(report, "TOP MESSAGE PREFIX")
    line(report)

    for msg, cnt in message_prefix_counter.most_common(TOP_MESSAGE_PREFIX):
        out(report, f"{cnt:10,}  {msg}")

    out(report)
    line(report)
    out(report, "TOP HOURS")
    line(report)

    for hour, cnt in hour_counter.most_common(TOP_HOUR):
        out(report, f"{hour}:00   {cnt:,}")

    out(report)
    line(report)
    out(report, "SUMMARY")
    line(report)

    out(report, f"Unique Levels           : {len(level_counter)}")
    out(report, f"Unique Models           : {len(model_counter)}")
    out(report, f"Unique Message Prefixes : {len(message_prefix_counter):,}")

print(f"\n[+] Report saved to: {OUTPUT}")
