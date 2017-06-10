//
//  BigintData.h
//  BigintSmallObject
//
//  Created by Vadim on 03.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef BigintData_h
#define BigintData_h

#include <memory>
#include <algorithm>
#include <vector>
#include <string.h>
#include "my_shared_ptr.h"

const size_t SMALL_SIZE = 4;

struct bigint_data {
    bigint_data(size_t n = 0);
    bigint_data(bigint_data const&);
    bigint_data(std::vector<uint32_t> const&);
    bigint_data& operator=(bigint_data const&);
    uint32_t get(size_t) const;
    uint32_t operator[](size_t) const;
    void set(size_t, uint32_t);
    void pop_back();
    void push_back(uint32_t);
    uint32_t back() const;
    size_t size() const;
    void clear();
    bool empty() const;
    void detach();
    void swap(bigint_data&);
    ~bigint_data();
private:
    size_t sz;
    union
    {
        uint32_t small_data[SMALL_SIZE];
        my_shared_ptr data;
    };
    bool is_small() const;
    size_t capacity() const;
    void ensure(size_t);
    my_shared_ptr data_factory(size_t);
};

#endif /* BigintData_h */
