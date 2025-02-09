#!/usr/bin/env python3

import numpy as np

file01 = "binary01"
file02 = "binary02"

step = 16 * 1024 * 1024

with open(file01, "rb") as f1, open(file02, "rb") as f2:
    offset = 0
    while True:
        chunk1 = f1.read(step);
        chunk2 = f2.read(step)

        if not chunk1 and not chunk2:
            break

        if not chunk1 or not chunk2:
            print("File size mismatch (already end)")
            break

        if len(chunk1) != len(chunk2):
            print("File size mismatch")
            break

        if np.array_equal(chunk1, chunk2):
            offset += step
            continue

        for i in range(len(chunk1)):
            if chunk1[i] != chunk2[i]:
                print(f"Offset 0x{offset + i:x}: {chunk1[i]:02x} -> {chunk2[i]:02x}")

        offset += step
