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
decltype(auto) copy_benchmark(int operations_count) {
	return run_benchmark([operations_count]() {
		smart_ptr<T> ptr = smart_ptr<T>(new T());
		for (int i = 0; i < operations_count / 2; ++i) {
			clobber();
			smart_ptr<T> ptr2 = ptr;
			escape(&ptr2);
			ptr = ptr2;
			clobber();
		}
	});
}


template <template<class> class smart_ptr, typename T>
decltype(auto) move_benchmark(int operations_count) {
	return run_benchmark([operations_count]() {
		smart_ptr<T> ptr = smart_ptr<T>(new T());
		smart_ptr<T> ptr2;
		for (int i = 0; i < operations_count / 2; ++i) {
			clobber();
			ptr2 = std::move(ptr);
			escape(&ptr2);
			ptr = std::move(ptr2);
			clobber();
		}
	});
}

#endif /* equasion_and_copy_test_h */
