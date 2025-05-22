#!/usr/bin/env python3

import os
import subprocess

def find_and_analyze_gpt_decompiled(start_dir="."):
    for dirpath, _, filenames in os.walk(start_dir):
        for filename in filenames:
            if filename == "obfuscated.c":
                full_path = os.path.join(dirpath, filename)
                print(f"\n📎 Analyzing {full_path}")
                subprocess.run(["lizard", full_path])

if __name__ == "__main__":
    find_and_analyze_gpt_decompiled()
