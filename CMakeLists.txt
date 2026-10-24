cmake_minimum_required(VERSION 3.16)
project(fixed_block_arena LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(arena_core src/arena.cpp src/baseline.cpp)
target_include_directories(arena_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(arena_benchmark src/Main.cpp)
target_link_libraries(arena_benchmark PRIVATE arena_core)
	
       
