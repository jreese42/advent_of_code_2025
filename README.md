# Advent of Code 2025

My solutions for Advent of Code 2025 in C++.

## Project Structure

```
advent_of_code_2025/
├── src/
│   ├── day_1/
│   │   ├── day_1.cpp
│   │   └── input
│   ├── day_2/
│   │   ├── day_2.cpp
│   │   └── input
│   └── ... (day_3 through day_12)
├── build/          (generated)
├── Makefile
└── .vscode/
    ├── tasks.json
    └── launch.json
```

## Building and Running

### Using Make

Build and run a specific day:
```bash
make DAY=1              # Build and run day 1
make build DAY=5        # Build only day 5
make debug DAY=3        # Build with debug symbols
make all-days           # Build all 12 days
make clean              # Remove build artifacts
```