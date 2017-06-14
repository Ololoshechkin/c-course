//
//  bigint_data_std.cpp
//  BigintSmallObject
//
//  Created by Vadim on 09.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include "bigint_data_std.h"

bigint_data_std::bigint_data_std(size_t n)
{
    v.assign(n, 0);
}

bigint_data_std::bigint_data_std(bigint_data_std const & other)
: v(other.v)
{}

bigint_data_std::bigint_data_std(std::vector<uint32_t> const& v2)
: bigint_data_std(v2.size())
{
    for (size_t i = 0; i < v2.size(); ++i)
        v[i] = v2[i];
}

bigint_data_std& bigint_data_std::operator=(bigint_data_std const& other)
{
    v = other.v;
    return *this;
}

void bigint_data_std::swap(bigint_data_std& other)
{
    std::swap(v, other.v);
}

uint32_t bigint_data_std::operator[](size_t i) const
{
    return v[i];
}

void bigint_data_std::set(size_t i, uint32_t val)
{
    v[i] = val;
}

void bigint_data_std::no_detach_set(size_t i, uint32_t val)
{
    set(i, val);
}

void bigint_data_std::pop_back()
{
    v.pop_back();
}

void bigint_data_std::push_back(uint32_t val)
{
    v.push_back(val);
}

uint32_t bigint_data_std::back() const
{
    uint32_t ans = v.back();
    return ans;
}

size_t bigint_data_std::size() const
{
    return v.size();
}

void bigint_data_std::clear()
{
    v.clear();
}

bool bigint_data_std::empty() const
{
    return v.empty();
}

void bigint_data_std::detach()
{}

bigint_data_std::~bigint_data_std()
{}










