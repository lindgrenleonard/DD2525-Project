# Testing Instructions

## Prerequisites

- **Python 3** (any actively-supported 3.x release)  
- **pip** (bundled with Python ≥ 3.4)  
- **Lizard** – source-code complexity analyzer  
- **`venv`** (optional, but recommended for an isolated environment)

---

### 1 · Create and activate a virtual environment (optional)

```bash
python3 -m venv venv          # create the venv
source venv/bin/activate      # Linux / macOS
# .\venv\Scripts\activate     # Windows PowerShell
```

### 2 · Install dependencies
```bash
pip install lizard
```

### 3 · Make the test scripts executable (Unix/macOS only)
```bash
chmod +x test_gptDecompiled.py analyze_gpt.py
```

4 · Run the tests
From the root directory of the project:
```bash
./test_gptDecompiled.py
./analyze_gpt.py
```
