//
//  my_shared_ptr.cpp
//  BigintSmallObject
//
//  Created by Vadim on 10.06.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include "my_shared_ptr.h"
#include <algorithm>
#include <iostream>

my_shared_ptr::my_shared_ptr(uint32_t* ptr)
: cnt(nullptr)
, ptr(ptr)
{
    if (ptr)
        cnt = new size_t(1);//, std::cout << "alloc : " << ptr << '\n';
}

my_shared_ptr::my_shared_ptr(my_shared_ptr const& other)
: cnt(other.cnt)
, ptr(other.ptr)
{
    if (cnt)
        ++(*cnt);
}

void my_shared_ptr::swap(my_shared_ptr& other)
{
    std::swap(cnt, other.cnt);
    std::swap(ptr, other.ptr);
}

my_shared_ptr& my_shared_ptr::operator=(my_shared_ptr const&other)
{
    my_shared_ptr tmp(other);
    swap(tmp);
    return *this;
}

bool my_shared_ptr::unique() const
{
    return *cnt == 1;
}

uint32_t* my_shared_ptr::get() const
{
    //std::cout << "access : " << ptr << '\n';
    return ptr;
}

uint32_t& my_shared_ptr::operator*() const
{
    //std::cout << "access : " << ptr << '\n';
    return *ptr;
}

uint32_t* my_shared_ptr::operator->() const
{
    //std::cout << "access : " << ptr << '\n';
    return ptr;
}

my_shared_ptr::~my_shared_ptr()
{
    if (cnt && !(--*cnt)) {
        //std::cout << "delete : " << ptr << '\n';
        delete[] ptr, delete cnt;
    }
}













