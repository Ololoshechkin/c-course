//
//  bigint_data.cpp
//  BigintSmallObject
//
//  Created by Vadim on 10.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include "bigint_data.h"
#include <iostream>

size_t bigint_data::big_data::get_capacity() const
{
    return capacity;
}

void bigint_data::big_data::inplace_create(size_t start_capacity)
{
    capacity = start_capacity;
    new (&data) shared_ptr_t_create(capacity);
}

void bigint_data::big_data::fill_zero()
{
    memset(data.get(), 0, sizeof(uint32_t) * capacity);
}

void bigint_data::big_data::inplace_copy(bigint_data::big_data const &other)
{
    capacity = other.capacity;
    new (&data) shared_ptr_t(other.data);
}

bigint_data::big_data::big_data()
: capacity(1)
, data(shared_ptr_t())
{}

bigint_data::big_data::big_data(size_t capacity)
: capacity(capacity)
, data(shared_ptr_t_create(capacity))
{}

void bigint_data::big_data::swap(bigint_data::big_data& other)
{
    std::swap(capacity, other.capacity);
    data.swap(other.data);
}

bigint_data::big_data::~big_data()
{}

bigint_data::bigint_data(size_t n)
: sz(n)
{
    if (is_small())
        memset(small_data, 0, sizeof(small_data));
    else
        big.inplace_create(n), big.fill_zero();
}

bigint_data::bigint_data(bigint_data const& other)
: sz(other.sz)
{
    if (other.is_small())
        std::copy(other.small_data, other.small_data + SMALL_SIZE, small_data);
    else
        big.inplace_copy(other.big);
}

bigint_data::bigint_data(std::vector<uint32_t> const& v)
: sz(v.size())
{
    if (is_small())
        std::copy(v.begin(), v.end(), small_data);
    else
    {
        big.inplace_create(v.size());
        std::copy(v.begin(), v.end(), big.data.get());
    }
}


bigint_data& bigint_data::operator=(const bigint_data &other)
{
    bigint_data tmp(other);
    swap(tmp);
    return *this;
}

uint32_t bigint_data::operator[](size_t i) const
{
    return is_small() ? small_data[i] : big.data.get()[i];
}

void bigint_data::set(size_t i, uint32_t val)
{
    detach();
    no_detach_set(i, val);
}

void bigint_data::no_detach_set(size_t i, uint32_t val)
{
    if (is_small())
        small_data[i] = val;
    else
        big.data.get()[i] = val;
}

void bigint_data::pop_back()
{
    bool wasnt_small = !is_small();
    --sz;
    if (is_small() && wasnt_small) {
        uint32_t tmp[SMALL_SIZE];
        std::copy(big.data.get(), big.data.get() + sz, tmp);
        big.~big_data();
        std::copy(tmp, tmp + SMALL_SIZE, small_data);
    }
}

void bigint_data::push_back(uint32_t val)
{
    ensure(sz + 1);
    ++sz;
    set(sz - 1, val);
}

uint32_t bigint_data::back() const
{
    return is_small() ? small_data[sz - 1] : big.data.get()[sz - 1];
}

size_t bigint_data::size() const
{
    return sz;
}

void bigint_data::clear()
{
    if (!is_small())
        big.~big_data();
    sz = 0;
}

bool bigint_data::empty() const
{
    return !sz;
}

void bigint_data::detach()
{
    if (is_small() || big.data.unique()) return;
    big_data new_bigdata(big.get_capacity());
    std::copy(big.data.get(), big.data.get() + sz, new_bigdata.data.get());
    big.swap(new_bigdata);
}

void bigint_data::swap(bigint_data &other)
{
    std::swap(sz, other.sz);
    std::swap(small_data, other.small_data);
}

bigint_data::~bigint_data()
{
    if (!is_small())
        big.~big_data();
}

bool bigint_data::is_small() const
{
    return sz <= SMALL_SIZE;
}

size_t bigint_data::capacity() const
{
    return is_small() ? SMALL_SIZE : big.get_capacity();
}

void bigint_data::ensure(size_t n)
{
    if (n <= capacity())
        return;
    big_data new_bigdata(n << 1);
    if (is_small()) {
        std::copy(small_data, small_data + sz, new_bigdata.data.get());
        big.inplace_copy(new_bigdata);
    }
    else
    {
        std::copy(big.data.get(), big.data.get() + sz, new_bigdata.data.get());
        big.swap(new_bigdata);
    }
}
