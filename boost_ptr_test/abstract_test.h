//
//  abstract_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef abstract_test_h
#define abstract_test_h

#include <chrono>
#include <vector>

constexpr int BIG_CONST = 500000;

template <typename F>
std::vector<std::chrono::high_resolution_clock::duration> run_benchmark(int test_count, F f)
{
	using namespace std::chrono;
	std::vector<high_resolution_clock::duration> bench;
	for (int i = 0; i < test_count; ++i) {
		auto start = high_resolution_clock::now();
		f(i);
		auto end = high_resolution_clock::now();
		bench.push_back(end - start);
	}
	
	return bench;
}

#endif /* abstract_test_h */
