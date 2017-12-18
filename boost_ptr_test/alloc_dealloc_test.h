//
//  allocations_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef allocations_test_h
#define allocations_test_h

#include "abstract_test.h"

template <template <typename > class smart_ptr, typename T>
void alloc_dealloc_test_impl(int test_number) {
	std::vector<smart_ptr<T>> pointers;
	for (int i = 0; i < BIG_CONST * test_number; ++i)
		pointers.push_back(smart_ptr<T>(new T()));
}

template <template <typename > class smart_ptr, typename T>
decltype(auto) alloc_dealloc_benchmark(int test_count) {
	return run_benchmark(test_count, [](int test_number) { alloc_dealloc_test_impl<smart_ptr, T>(test_number); });
}


#endif /* allocations_test_h */
