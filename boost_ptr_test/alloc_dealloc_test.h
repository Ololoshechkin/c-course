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

template <template<class> class smart_ptr, typename T, T*(*new_T)()>
struct alloc_dealloc_test : public abstract_test<smart_ptr, T> {
protected:
    void test_impl(int test_number) {
        std::vector<smart_ptr<T>> pointers;
        for (int i = 0; i < BIG_CONST * test_number; ++i) {
            pointers.push_back(smart_ptr<T>(new_T())); 
        }
    }
};

#endif /* allocations_test_h */
