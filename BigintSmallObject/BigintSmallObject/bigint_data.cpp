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
        for (size_t i = 0; i < SMALL_SIZE; ++i)
            small_data[i] = 0;
    }
    else
    {
        new (&data) std::shared_ptr<uint32_t>(
                        new uint32_t[n + 1],
                        std::default_delete<uint32_t[]>());
        data.get()[0] = (uint32_t) n;
        for (size_t i = 1; i <= n; ++i)
            data.get()[i] = 0;
    }
}

bigint_data::bigint_data(bigint_data const& other)
: sz(other.sz)
{
    if (other.is_small())
        for (size_t i = 0; i < SMALL_SIZE; ++i)
            small_data[i] = other.small_data[i];
    else
        new (&data) std::shared_ptr<uint32_t>(other.data);
}

bigint_data::bigint_data(std::vector<uint32_t> const& v)
: sz(v.size())
{
    if (is_small())
        for (size_t i = 0; i < v.size(); ++i)
            small_data[i] = v[i];
    else
    {
        new (&data) std::shared_ptr<uint32_t>(
                     new uint32_t[v.size() + 1],
                     std::default_delete<uint32_t[]>());
        data.get()[0] = (uint32_t) v.size();
        for (size_t i = 0; i < v.size(); ++i)
            data.get()[i + 1] = v[i];
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
        detach();
        uint32_t tmp[SMALL_SIZE];
        for (size_t i = 0; i < SMALL_SIZE; ++i)
            tmp[i] = data.get()[i + 1];
        data.~shared_ptr();
        for (size_t i = 0; i < SMALL_SIZE; ++i)
            small_data[i] = tmp[i];
    }
}

void bigint_data::push_back(uint32_t val)
{
    ensure(sz + 1);
    detach();
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
    std::shared_ptr<uint32_t> tmp_data = data_factory(sz + 1);
    for (size_t i = 0; i < sz + 1; ++i)
        tmp_data.get()[i] = data.get()[i];
    data.swap(tmp_data);
}

void bigint_data::swap(bigint_data &other)
{
    std::swap(sz, other.sz);
    for (size_t i = 0; i < SMALL_SIZE; ++i)
        std::swap(small_data[i], other.small_data[i]);
}

bigint_data::~bigint_data()
{
    if (!is_small())
        data.~shared_ptr();
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
        for (size_t i = 0; i < sz; ++i)
            n_data.get()[i + 1] = small_data[i];
    }
    else
    {
        for (size_t i = 0; i < sz; ++i)
            n_data.get()[i + 1] = data.get()[i + 1];
    }
    new (&data) std::shared_ptr<uint32_t>(n_data);
}

std::shared_ptr<uint32_t> bigint_data::data_factory(size_t size)
{
    return std::shared_ptr<uint32_t>(
                new uint32_t[size],
                std::default_delete<uint32_t[]>());
}

