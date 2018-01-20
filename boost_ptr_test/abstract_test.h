//
//  abstract_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef abstract_test_h
#define abstract_test_h

#include <vector>
#include <cstdint>
#include <cmath>

uint64_t rdtsc()
{
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t) hi << 32) | lo;
}

void escape(void* p)
{
	asm volatile("" : : "g"(p) : "memory");
}

void clobber()
{
	asm volatile("" : : : "memory");
}

struct benchmark_res
{
	uint64_t res;
	uint64_t disp;

	benchmark_res(uint64_t res, uint64_t disp)
			: res(res), disp(disp) {}

	operator uint64_t()
	{
		return res;
	}

	benchmark_res operator/(int x) {
		return benchmark_res(res / x, disp / x);
	}

	benchmark_res operator*(int x) {
		return benchmark_res(2 * res, disp);
	}

};

const int ITERS = 10;

template <typename F>
benchmark_res run_benchmark(F f)
{
	std::vector<uint64_t> results(ITERS);
	uint64_t start;
	for (int i = 0; i < ITERS; ++i) {
		start = rdtsc();
		f();
		results[i] = rdtsc() - start;
	}
	double mid = 0;
	double disp = 0.0;
	for (uint64_t x : results)
		mid += x;
	mid /= ITERS;
	for (uint64_t x : results)
		disp += (x - mid) * (x - mid);
	disp = sqrt(disp) / ITERS;
	return benchmark_res(static_cast<uint64_t>(mid), static_cast<uint64_t>(disp));
}

#endif /* abstract_test_h */
