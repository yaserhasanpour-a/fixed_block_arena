#include<chrono>
#include<cstddef>
#include<memory>
#include<vector>
#include "benchmark.hpp"
#include<new>
#include<vector>
using namespace std;
RunResult run_baseline(size_t block_count, size_t block_size)
{
	using Clock = chrono::steady_clock;
	vector<unique_ptr<byte[]>>blocks;
	vector<byte*>pointers;
	pointers.reserve(block_count);
	blocks.reserve(block_count);
	RunResult result;
	auto start = Clock::now();
	for(size_t i=0; i < block_count; ++i)
	{
		auto block = make_unique<byte[]>(block_size);
		pointers.push_back(block.get());
		blocks.push_back(std::move(block));
	}
	auto end = Clock::now();
	result.allocation_ms = chrono::duration<double, milli>(end - start).count();

	/////////////////////////////////////////////////////////////
	start = Clock::now();
	for(size_t i=0; i<block_count; ++i)
	{
		for(size_t j=0; j<block_size; ++j)
		{
			pointers[i][j] = static_cast<byte>(10 * i + j);
		}
	}

        end = Clock::now();
	result.write_ms = chrono::duration<double, milli>( end - start).count();
	//////////////////////////////////////////////////////////////////
	start = Clock::now();
	uint64_t checksum = 0;
	for(size_t i=0; i< block_count; ++i)
	{
		for(size_t j =0; j < block_size; ++j)
		{ 
			checksum += to_integer<int>(pointers[i][j]);
		}
	}
	end = Clock::now();
	result.read_ms = chrono::duration<double, milli>(end- start).count();
	result.checksum= checksum;
	return result;
}

