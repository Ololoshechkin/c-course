//
//  equasion_and_copy_test.h
//  boost_ptr_test
//
//  Created by Vadim on 18/11/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef equasion_and_copy_test_h
#define equasion_and_copy_test_h

#include "abstract_test.h"

template <typename T>
using my_unique_ptr = std::unique_ptr<T, std::default_delete<T>>;

template <
		template<class> class smart_ptr, 
		typename T, 
		T*(*new_T)()
> struct equasion_and_copy_test : public abstract_test {
protected:
	 void test_impl(int test_number) {
		smart_ptr<T> ptr = smart_ptr<T>(new_T());
		for (int i = 0; i < BIG_CONST * 10 * test_number; ++i) {
			smart_ptr<T> ptr2 = ptr;
			ptr = ptr2;
		}
	}
};

/*
 1) clock -> std::chrono::highresolution_cloch::now() - current time
 2) 
*/

template <
		typename T,
		T*(*new_T)()
> struct equasion_and_copy_test<
		my_unique_ptr,
		T,
		new_T
> : public abstract_test {
protected:
	void test_impl(int test_number) {
		std::unique_ptr<T> ptr = std::unique_ptr<T>(new_T());
		for (int i = 0; i < BIG_CONST * 10 * test_number; ++i) {
			std::unique_ptr<T> ptr2 = std::move(ptr);
			ptr = std::move(ptr2);
		}
	}
};
#endif /* equasion_and_copy_test_h */
