//
//  bigint_data_std.hpp
//  BigintSmallObject
//
//  Created by Vadim on 09.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef bigint_data_std_hpp
#define bigint_data_std_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>

struct bigint_data_std {
    bigint_data_std(size_t n = 0)
    {
        v.assign(n, 0);
    }
    bigint_data_std(bigint_data_std const & other)
    : v(other.v)
    {}
    bigint_data_std(std::vector<uint32_t> const& v2)
    : bigint_data_std(v2.size())
    {
        for (size_t i = 0; i < v2.size(); ++i)
            v[i] = v2[i];
    }
    bigint_data_std& operator=(bigint_data_std const& other)
    {
        //bigint_data_std tmp(other);
        //swap(tmp);
        v = other.v;
        return *this;
    }
    void swap(bigint_data_std& other)
    {
        std::swap(v, other.v);
    }
    uint32_t operator[](size_t i) const
    {
        return v[i];
    }
    void set(size_t i, uint32_t val)
    {
        v[i] = val;
    }
    void pop_back()
    {
        v.pop_back();
    }
    void push_back(uint32_t val)
    {
        v.push_back(val);
    }
    uint32_t back() const
    {
        uint32_t ans = v.back();
        return ans;
    }
    size_t size() const
    {
        return v.size();
    }
    void clear()
    {
        v.clear();
    }
    bool empty() const
    {
        return v.empty();
    }
    ~bigint_data_std()
    {
        v.clear();
    }
private:
    std::vector<uint32_t> v;
};

#endif /* bigint_data_std_hpp */

