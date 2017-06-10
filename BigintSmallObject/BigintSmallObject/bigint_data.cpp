//
//  bigint_data.cpp
//  BigintSmallObject
//
//  Created by Vadim on 10.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include "bigint_data.h"

bigint_data::bigint_data(size_t n)
: sz(n)
{
    if (is_small())
    {
        memset(small_data, 0, sizeof(small_data));
    }
    else
    {
        new (&data) my_shared_ptr(new uint32_t[n + 1]);
        data.get()[0] = (uint32_t) n;
        memset(data.get() + 1, 0, capacity() * sizeof(uint32_t));
    }
}

bigint_data::bigint_data(bigint_data const& other)
: sz(other.sz)
{
    if (other.is_small())
        std::copy(other.small_data, other.small_data + SMALL_SIZE, small_data);
    else
        new (&data) my_shared_ptr(other.data);
}

bigint_data::bigint_data(std::vector<uint32_t> const& v)
: sz(v.size())
{
    if (is_small())
        std::copy(v.begin(), v.end(), small_data);
    else
    {
        new (&data) my_shared_ptr(new uint32_t[v.size() + 1]);
        data.get()[0] = (uint32_t) v.size();
        std::copy(v.begin(), v.end(), data.get() + 1);
    }
}


bigint_data& bigint_data::operator=(const bigint_data &other)
{
    bigint_data tmp(other);
    swap(tmp);
    return *this;
}

uint32_t bigint_data::get(size_t i) const
{
    return is_small() ? small_data[i] : data.get()[i + 1];
}

uint32_t bigint_data::operator[](size_t i) const
{
    return get(i);
}

void bigint_data::set(size_t i, uint32_t val)
{
    if (is_small())
        small_data[i] = val;
    else
    {
        detach();
        data.get()[i + 1] = val;
    }
}

void bigint_data::pop_back()
{
    bool wasnt_small = !is_small();
    --sz;
    if (is_small() && wasnt_small) {
        uint32_t tmp[SMALL_SIZE];
        std::copy(data.get() + 1, data.get() + SMALL_SIZE + 1, tmp);
        data.~my_shared_ptr();
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
    return get(sz - 1);
}

size_t bigint_data::size() const
{
    return sz;
}

void bigint_data::clear()
{
    while (sz)
        pop_back();
}

bool bigint_data::empty() const
{
    return !sz;
}

void bigint_data::detach()
{
    if (is_small() || data.unique()) return;
    auto tmp_data = data_factory(sz + 1);
    std::copy(data.get(), data.get() + sz + 1, tmp_data.get());
    std::swap(data, tmp_data);
}

void bigint_data::swap(bigint_data &other)
{
    std::swap(sz, other.sz);
    std::swap(small_data, other.small_data);
}

bigint_data::~bigint_data()
{
    if (!is_small())
        data.~my_shared_ptr();
}

bool bigint_data::is_small() const
{
    return sz <= SMALL_SIZE;
}

size_t bigint_data::capacity() const
{
    return is_small() ? SMALL_SIZE : (size_t) data.get()[0];
}

void bigint_data::ensure(size_t n)
{
    if (n <= capacity())
        return;
    size_t new_size = 1.5 * n + 1;
    auto n_data = data_factory(new_size + 1);
    n_data.get()[0] = (uint32_t) new_size;
    if (is_small()) {
        std::copy(small_data, small_data + SMALL_SIZE, n_data.get() + 1);
    }
    else
    {
        std::copy(data.get() + 1, data.get() + sz + 1, n_data.get() + 1);
    }
    new (&data) my_shared_ptr(n_data);
}

my_shared_ptr bigint_data::data_factory(size_t size)
{
    return my_shared_ptr(new uint32_t[size]);
}

