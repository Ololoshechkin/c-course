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

uint64_t rdtsc(){
	unsigned int lo, hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}

void escape(void* p)
{
	asm volatile("" : : "g"(p) : "memory");
}

void clobber()
{
	asm volatile("" : : : "memory");
}

template <typename F>
uint64_t run_benchmark(F f)
{
	uint64_t start = rdtsc();
	f();
	return rdtsc() - start;
}

#endif /* abstract_test_h */
