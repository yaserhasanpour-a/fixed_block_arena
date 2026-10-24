Fixed-Size Block Memory Arena
============================

Overview
This C++ project compares two memory allocation approaches:
1. Separate blocks owned by std::unique_ptr<std::byte[]>
2. Blocks allocated from one contiguous arena buffer

Ownership
With separate allocations, each unique_ptr owns its block.
With the arena, the arena owns the entire buffer.
Pointers returned by the arena do not own the memory.

Requirements
- A compiler supporting C++17
- CMake

Build and Run
Run these commands from the project root:

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/arena_benchmark

Benchmark
The benchmark measures allocation, writing, and reading.
It also compares checksums between the two approaches.

Example results from one local run:
- Separate allocations: 34.77 ms
- Arena allocation:      4.68 ms

The arena's allocation phase was approximately 7.4 times
faster in that run. Both checksums were 815971840.
The build configuration for that run was not recorded.

Notes
- Performance depends on hardware, compiler settings,
  and system load.
- Matching checksums do not prove memory safety.
- Do not use arena pointers after the arena is destroyed.
- After reset, previous allocations must no longer be
  used before their storage is reused.

Learning Goals
RAII, memory ownership, unique_ptr, contiguous memory,
and performance benchmarking.

