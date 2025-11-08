# Cache Simulator (CS3339 HW3)

## Description

This program simulates a CPU cache with configurable size and associativity.  
It reads a sequence of memory addresses from an input file and reports whether each access is a **HIT** or a **MISS**.  

- Each cache entry has a **valid bit** and a **tag**.  
- Cache uses **LRU (Least Recently Used)** replacement policy for fully-populated sets.  
- Output is written to a file called `cache_sim_output`.  
- No actual data is stored in the cache — hits/misses are determined solely from addresses.  

## Files

- `main.cpp` — main program that reads arguments, input file, and writes output.  
- `cache.h` / `cache.cpp` — cache implementation (Entry class + Cache class).  
- Example input files: `input.txt`, `test_input.txt`.  

## Requirements

- **C++ compiler** (e.g., g++ on Windows, Linux, or macOS).  
- Standard C++ libraries.  

## Build Instructions (Windows / g++)

Open a terminal in the project directory and run:

```bash
g++ main.cpp cache.cpp -o cache_sim
cache_sim <num_entries> <associativity> <input_file>
