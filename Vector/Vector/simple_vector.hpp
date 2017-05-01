//
//  simple_vector.hpp
//  Vector
//
//  Created by Vadim on 22.04.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>

#ifndef simple_vector_h
#define simple_vector_h

template <typename T>
class simple_vector
{
private:
    int size, capacity;
    T* data;
public:
    typedef T* iterator;
    simple_vector() : size(0), capacity(0), data(nullptr)
    {}
    simple_vector(int sz) : size(sz), capacity(sz), data(new T[sz])
    {}
    bool empty()
    {
        return !size;
    }
    int get_size()
    {
        return size;
    }
    int get_capacity()
    {
        return capacity;
    }
    void push_back(T const& value)
    {
        if (size == capacity)
            push_back_and_resize(value);
        else
            data[size++] = value;
    }
    void push_back_and_resize(T const& value)
    {
        if (empty())
        {
            std::cout << "empty()\n";
            size = 1;
            capacity = 2;
            data = new T[2];
            data[0] = value;
        }
        else
        {
            capacity *= 2;
            T* new_data = new T[capacity];
            for (int i = 0; i < size; ++i)
                new_data[i] = data[i];
            new_data[size++] = value;
            delete data;
            data = new_data;
        }
    }
    
    iterator begin()
    {
        return data;
    }
    
    iterator end()
    {
        return data + size;
    }
    T& back()
    {
        return data[size - 1];
    }
};

#endif /* simple_vector_h */
