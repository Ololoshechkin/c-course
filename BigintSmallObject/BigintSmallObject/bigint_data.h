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
#include <memory>
#include "my_shared_ptr.h"

#define shared_ptr_t std::shared_ptr<uint32_t>
#define shared_ptr_t_create(capacity) std::shared_ptr<uint32_t>(new uint32_t[capacity], std::default_delete<uint32_t[]>())

const size_t SMALL_SIZE = 6;

struct bigint_data
{
    struct big_data
    {
        size_t capacity;
        size_t get_capacity() const;
        shared_ptr_t data;
        void inplace_create(size_t);
        void inplace_copy(big_data const&);
        big_data();
        void swap(big_data&);
        ~big_data();
    };
    bigint_data(size_t n = 0);
    bigint_data(bigint_data const&);
    bigint_data(std::vector<uint32_t> const&);
    bigint_data& operator=(bigint_data const&);
    uint32_t operator[](size_t) const;
    void set(size_t, uint32_t);
    void no_detach_set(size_t, uint32_t);
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
        big_data big;
    };
    bool is_small() const;
    size_t capacity() const;
    void ensure(size_t);
};

#endif /* BigintData_h */
