#pragma once 
#include<cstddef>
#include<cstdint>

struct RunResult{
	double allocation_ms = 0;
	double write_ms = 0;
	double read_ms = 0;
        uint64_t checksum = 0;
};
RunResult run_baseline(size_t block_count, size_t block_size);
RunResult run_arena(size_t block_count, size_t block_size);

