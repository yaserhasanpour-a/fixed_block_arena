#include "benchmark.hpp"

#include <cstddef>
#include <iostream>

namespace {
void print_result(const char* name, const RunResult& r) {
    std::cout << name << "\n"
              << "  allocation: " << r.allocation_ms << " ms\n"
              << "  write:      " << r.write_ms << " ms\n"
              << "  read:       " << r.read_ms << " ms\n"
              << "  checksum:   " << r.checksum << "\n";
}
}

int main() {
    constexpr std::size_t block_count = 100'000;
    constexpr std::size_t block_size = 64;

    const auto baseline = run_baseline(block_count, block_size);
    const auto arena = run_arena(block_count, block_size);
    print_result("Individual unique_ptr blocks", baseline);
    print_result("Contiguous fixed-size arena", arena);
    std::cout << "Checksums match: " << (baseline.checksum == arena.checksum ? "yes" : "NO") << '\n';
    return baseline.checksum == arena.checksum ? 0 : 1;
}

