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
#include <cstdlib>

const size_t SMALL_SIZE = 4;

struct bigint_data {
    bigint_data(size_t n = 0)
    : sz(n)
    {
        if (is_small())
        {
            memset(small_data, 0, SMALL_SIZE * sizeof(uint32_t));
        }
        else
        {
            new (&data) std::shared_ptr<uint32_t>(
                                                  new uint32_t[n + 1],
                                                  std::default_delete<uint32_t[]>()
                                                  );
            data.get()[0] = (uint32_t) n;
            memset(data.get() + 1, 0, capacity() * sizeof(uint32_t));
        }
    }
    bigint_data(bigint_data const & other)
    : sz(other.sz)
    {
        if (other.is_small())
            std::copy(other.small_data,
                      other.small_data + SMALL_SIZE,
                      small_data);
        else
            new (&data) std::shared_ptr<uint32_t> (other.data);
    }
    bigint_data(std::vector<uint32_t> const& v)
    : bigint_data(v.size())
    {
        if (is_small())
            std::copy(v.begin(), v.end(), small_data);
        else
            std::copy(v.begin(), v.end(), data.get() + 1);
    }
    bigint_data& operator=(bigint_data const& other)
    {
        bigint_data tmp(other);
        swap(tmp);
        return *this;
    }
    uint32_t operator[](size_t i) const
    {
        return is_small() ? small_data[i] : data.get()[i + 1];
    }
    void set(size_t i, uint32_t val)
    {
        if (is_small())
            small_data[i] = val;
        else
            detach(), data.get()[i + 1] = val;
    }
    void pop_back()
    {
        bool wasnt_small = !is_small();
        --sz;
        if (is_small() && wasnt_small) {
            uint32_t tmp[SMALL_SIZE];
            std::copy(data.get() + 1, data.get() + sz + 1, tmp);
            data.~shared_ptr();
            std::copy(tmp, tmp + SMALL_SIZE, small_data);
        }
    }
    void push_back(uint32_t val)
    {
        ensure(sz + 1);
        ++sz;
        set(sz - 1, val);
    }
    uint32_t back() const
    {
        return is_small() ? small_data[sz - 1] : data.get()[sz];
    }
    size_t size() const
    {
        return sz;
    }
    void clear()
    {
        sz = 0;
    }
    bool empty() const
    {
        return !sz;
    }
    void detach()
    {
        if (is_small() || data.unique()) return;
        auto tmp_data = data_factory(sz + 1);
        std::copy(data.get(), data.get() + sz + 1, tmp_data.get());
        data.swap(tmp_data);
    }
    ~bigint_data() {
        if (!is_small())
            data.~shared_ptr();
    }
private:
    size_t sz;
    inline bool is_small() const
    {
        return sz <= SMALL_SIZE;
    }
    union
    {
        uint32_t small_data[SMALL_SIZE];
        std::shared_ptr<uint32_t> data;
    };
    size_t capacity() const
    {
        return is_small() ? SMALL_SIZE : (size_t) data.get()[0];
    }
    void ensure(size_t n)
    {
        if (n <= capacity())
            return;
        size_t new_size = (n << 1) - (n >> 1) + 1;
        auto n_data = data_factory(new_size + 1);
        n_data.get()[0] = (uint32_t) new_size;
        if (is_small()) {
            std::copy(small_data, small_data + SMALL_SIZE, n_data.get() + 1);
        }
        else
        {
            std::copy(data.get() + 1, data.get() + sz + 1, n_data.get() + 1);
            data.~shared_ptr();
        }
        new (&data) std::shared_ptr<uint32_t>(n_data);
    }
    std::shared_ptr<uint32_t> data_factory(size_t size)
    {
        return std::shared_ptr<uint32_t>(
                   new uint32_t[size],
                   std::default_delete<uint32_t[]>());
    }
    void swap(bigint_data& other)
    {
        std::swap(sz, other.sz);
        if (is_small())
            std::swap(small_data, other.small_data);
        else
            data.swap(other.data);
    }
};

#endif /* BigintData_h */
