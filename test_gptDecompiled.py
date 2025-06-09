#!/usr/bin/env python3
import os
import subprocess
import sys

# — CONFIGURATION — 
DIRS = [
    'baseline',
    'control_flow_obfuscation',
    'encrypted_strings',
    'expression_obfuscation',
    'function_pointers',
    'redundant_code',
]

TEST_CASES = [
    "",
    "hello",
    "world",
    "AeIoU",
    "rhythm",
    "a quick brown fox jumps over the lazy dog",
    "12345!@#$%",
]

VOWELS = set('aeiou')

def expected_count(s: str) -> str:
    cnt = sum(ch in VOWELS for ch in s)
    if cnt == 0:
        return "No vowels found."
    else:
        return f"Your input has {cnt} vowel(s)."

def run_and_strip(binary: str, inp: str) -> str:
    p = subprocess.run(
        [binary],
        input=inp + "\n",
        text=True,
        capture_output=True,
        timeout=3
    )
    out = p.stdout.strip()

    # 1) If the real message is in there, grab that
    if "No vowels found." in out:
        return "No vowels found."
    if "Your input has" in out:
        start = out.find("Your input has")
        # find end-of-sentence
        end = out.find(".", start)
        if end != -1:
            return out[start:end+1]
        else:
            return out[start:].strip()
    # 2) otherwise, just return whatever it gave us
    return out

def main():
    total = 0
    failures = 0

    for d in DIRS:
        print(f"\n=== Directory: {d} ===")
        src = os.path.join(d, 'gptDecompiled.c')
        exe = os.path.join(d, 'gptDecompiled')

        # compile if needed
        if os.path.isfile(src):
            print(f" Compiling {src} …", end='')
            rc = subprocess.run(['gcc', src, '-o', exe, '-std=c99', '-O2']).returncode
            if rc != 0:
                print(" ❌ compile error")
                failures += len(TEST_CASES)
                continue
            print(" OK")

        if not os.path.isfile(exe):
            print(f" Skipping {d}: no executable")
            continue

        # run each test
        for tc in TEST_CASES:
            total += 1
            try:
                got = run_and_strip(exe, tc)
            except Exception as e:
                print(f"  [ERROR] {tc!r}: {e}")
                failures += 1
                continue

            exp = expected_count(tc)
            if got == exp:
                print(f"  [PASS] {tc!r} → {got!r}")
            else:
                print(f"  [FAIL] {tc!r} → got: {got!r}, expected: {exp!r}")
                failures += 1

    print("\nSummary:")
    print(f"  Total tests run: {total}")
    print(f"  Failures       : {failures}")
    sys.exit(1 if failures else 0)

if __name__ == '__main__':
    main()
