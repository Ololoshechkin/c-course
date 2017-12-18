//
//  copy_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef equasion_and_copy_test_h
#define equasion_and_copy_test_h

#include "abstract_test.h"


template <template<class> class smart_ptr, typename T>
void copy_test(int test_number) {
	smart_ptr<T> ptr = smart_ptr<T>(new T());
	for (int i = 0; i < BIG_CONST * 10 * test_number; ++i) {
		smart_ptr<T> ptr2 = ptr;
		ptr = ptr2;
	}
}

template <template<class> class smart_ptr, typename T>
void move_test(int test_number) {
	smart_ptr<T> ptr = smart_ptr<T>(new T());
	for (int i = 0; i < BIG_CONST * 10 * test_number; ++i) {
		smart_ptr<T> ptr2 = std::move(ptr);
		ptr =  std::move(ptr2);
	}
}

template <template<class> class smart_ptr, typename T>
decltype(auto) copy_benchmark(int test_count) {
	return run_benchmark(test_count, [](int i) { return copy_test<smart_ptr, T>(i);});
}


template <template<class> class smart_ptr, typename T>
decltype(auto) move_benchmark(int test_count) {
	return run_benchmark(test_count, [](int i) { return move_test<smart_ptr, T>(i);});
}

#endif /* equasion_and_copy_test_h */
