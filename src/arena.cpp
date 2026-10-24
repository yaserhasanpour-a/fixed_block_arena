#include "arena.hpp"
#include "benchmark.hpp"
#include<chrono>
#include<cstdint>
#include<vector>
using namespace std;
Arena::Arena(std::size_t capacity):
	storage_(capacity ? make_unique<byte[]>(capacity) : nullptr),
	capacity_(capacity)
        {}
byte* Arena::allocate(size_t size)
{
	if(size==0 )
		return nullptr;
	if(size > capacity_ - used_)
		throw bad_alloc{};

	byte* p= storage_.get() + used_;
	used_ += size;
	return p;
}
RunResult run_arena(size_t block_count, size_t block_size)
{
	using Clock = chrono::steady_clock;
	Arena arena(block_count * block_size);
	vector<byte*>pointers;
	pointers.reserve(block_count);
	RunResult result;
	auto start = Clock::now();
	for(size_t i=0; i < block_count ; ++i)
	       pointers.push_back(arena.allocate(block_size));
        auto end = Clock::now();
        result.allocation_ms = chrono::duration<double, milli>(end- start).count();
	start = Clock::now();
	for(size_t i=0; i<block_count; ++i)
	{
	    for(size_t j=0; j< block_size; ++j)
	 
	        pointers[i][j]= static_cast<byte>(10*i+j);
	  }
	  end = Clock::now();
	  result.write_ms = chrono::duration<double, milli>(end - start).count();
	  //////////////////////////////////////////////////////////////////
	  uint64_t checksum =0;
	  start = Clock::now();
	  for(size_t i=0; i<block_count; ++i)
	  {
	       for(size_t j=0; j<block_size; ++j)
		       checksum += to_integer<int>(pointers[i][j]);
	  }
	  end = Clock::now();
	  result.read_ms = chrono::duration<double, milli>(end - start).count();
	  result.checksum = checksum;
	  return result;
}
        	


