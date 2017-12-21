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
decltype(auto) alloc_dealloc_benchmark(int operations_count) {
	return run_benchmark([operations_count]() {
		for (int i = 0; i < operations_count; ++i) {
			auto ptr = smart_ptr<T>(new T());
			clobber();
			escape(&ptr);
		}
	});
}

template <typename T>
decltype(auto) raw_alloc_benchmark(int operations_count) {
	return run_benchmark([operations_count]() {
		for (int i = 0; i < operations_count; ++i) {
			auto obj = new T();
			clobber();
			escape(obj);
		}
	});
}


#endif /* allocations_test_h */
