//
//  my_shared_ptr.hpp
//  BigintSmallObject
//
//  Created by Vadim on 10.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef my_shared_ptr_hpp
#define my_shared_ptr_hpp

#include <cstdint>
#include <cstddef>

class my_shared_ptr {
private:
    size_t* cnt;
    uint32_t* ptr;
public:
    my_shared_ptr(uint32_t* ptr = nullptr);
    my_shared_ptr(my_shared_ptr const&);
    void swap(my_shared_ptr& other);
    my_shared_ptr& operator=(my_shared_ptr const&);
    bool unique() const;
    uint32_t* get() const;
    uint32_t& operator*() const;
    uint32_t* operator->() const;
    ~my_shared_ptr();
};

#endif /* my_shared_ptr_hpp */
