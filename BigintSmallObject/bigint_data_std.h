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
    bigint_data_std(size_t n = 0);
    bigint_data_std(bigint_data_std const&);
    bigint_data_std(std::vector<uint32_t> const&);
    bigint_data_std& operator=(bigint_data_std const& other);
    void swap(bigint_data_std&);
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
    ~bigint_data_std();
private:
    std::vector<uint32_t> v;
};

#endif /* bigint_data_std_hpp */

