#include "arena.hpp"
#include "benchmark.hpp"
#include<iostream>
#include <cassert>
#include <cstddef>
#include <limits>
#include <new>
using namespace std;
int main() {
    Arena arena(16);
    assert(arena.capacity() == 16 && arena.used() == 0);
    assert(arena.allocate(0) == nullptr);
    auto* first = arena.allocate(8);
    auto* second = arena.allocate(8);
    assert(second == first + 8);
    assert(arena.used() == 16);
    bool threw = false;
    try{ (void)arena.allocate(1);}
    catch( const std::bad_alloc&)
	    {
		    threw = true;
	    }
    assert(threw && arena.used()==16);
    arena.reset();
    assert(arena.used() == 0);
    threw = false;
    try{(void)arena.allocate(numeric_limits<size_t>::max());}
    catch(const bad_alloc&)
             {
		     threw = true;
	     }
    const auto baseline = run_baseline(31, 13);
    const auto optimized = run_arena(31, 13);
    assert(baseline.checksum == optimized.checksum);
    return 0;
}
	     
