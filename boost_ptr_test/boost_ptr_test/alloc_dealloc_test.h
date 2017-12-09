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

template <typename smart_ptr_t> // shared_ptr<T>
struct alloc_dealloc_test : public abstract_test<smart_ptr_t> {
protected:
    void test_impl(int test_number) {
        std::vector<smart_ptr_t> pointers;
        typedef std::remove_reference_t<
            decltype(*std::declval<smart_ptr_t>())
        > T;
        for (int i = 0; i < 1000 * test_number; ++i) {
            pointers.push_back(smart_ptr_t(new T[4]));
        }
    }
};

#endif /* allocations_test_h */
