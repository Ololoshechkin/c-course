//
//  vector.hpp
//  vector
//
//  Created by Vadim on 22.04.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <memory>
#include <cstdlib>
#include <memory.h>
#include <exception>
#include <stdexcept>
#include <new>

const double vector_MAX_CAPACITY_RATIO = 1.618033988749894848;
const double vector_MIN_CAPACITY_RATIO = 0.61803398875; // unused

template <typename T>
class vector {
private:
    size_t size, capacity;
    T* data;

public:
    typedef T* iterator;
    typedef T const* const_iterator;

    vector();
    vector(size_t size);
    vector(size_t, T);
    vector(vector const&);
    vector& operator=(vector const&);

    void swap(vector& other);
    void reserve(size_t);
    void shrink_to_fit();
    void clear();

    T& operator[](size_t);
    T const& operator[](size_t) const;

    bool empty() const;
    size_t get_size() const;
    size_t get_capacity() const;
    void push_back(T const&);
    void pop_back();
    void push_back_and_resize(T const&);

    iterator begin();
    iterator end();
    const_iterator const_begin() const;
    const_iterator const_end() const;
    iterator insert(iterator, T const&);
    const_iterator insert(const_iterator, T const&);
    iterator erase(iterator pos);
    const_iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    const_iterator erase(const_iterator first, const_iterator last);
    T& front();
    T& back();

    ~vector();
};

template <typename T>
vector<T>::vector()
    : size(0)
    , capacity(0)
    , data(nullptr)
{
}

template <typename T>
vector<T>::vector(size_t capacity)
    : size(0)
    , capacity(capacity)
    , data(static_cast<T*>(operator new(capacity * sizeof(T))))
{
}

template <typename T>
vector<T>::vector(size_t size, T placement)
    : vector(size)
{
    for (size_t i = 0; i < size; ++i)
        data[i] = placement;
}

template <typename T>
vector<T>::vector(vector const& other)
    : size(other.size)
    , capacity(other.capacity)
    , data(static_cast<T*>(operator new(other.capacity * sizeof(T))))
{
    for (size_t i = 0; i < size; ++i) {
        try {
            new (&data[i]) T(other.data[i]);
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                data[j].~T();
            }
            delete (data);
            throw;
        }
    }
}

template <typename T>
void vector<T>::swap(vector<T>& other)
{
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
    vector tmp(other);
    swap(tmp);
    return *this;
}

template <typename T>
void vector<T>::reserve(size_t expected_capacity)
{
    if (capacity < expected_capacity)
        return;
    vector<T> tmp(expected_capacity);
    swap(tmp);
    tmp->clear();
}

template <typename T>
void vector<T>::shrink_to_fit()
{
    if (capacity == size)
        return;
    free(data + size);
    capacity = size;
}

template <typename T>
void vector<T>::clear()
{
    for (size_t i = 0; i < capacity; ++i)
        data[i].~T();
    delete (data);
    data = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
T& vector<T>::operator[](size_t i)
{
    if (i > size)
        throw std::out_of_range("vector is too small");
    return data[i];
}

template <typename T>
T const& vector<T>::operator[](size_t i) const
{
    if (i > size)
        throw std::out_of_range("vector is too small");
    return data[i];
}

template <typename T>
bool vector<T>::empty() const
{
    return size == 0;
}

template <typename T>
size_t vector<T>::get_size() const
{
    return size;
}

template <typename T>
size_t vector<T>::get_capacity() const
{
    return capacity;
}

template <typename T>
void vector<T>::push_back(const T& value)
{
#include <iostream>
    if (size < capacity)
        new (&data[size]) T(value), size;
    else
        push_back_and_resize(value);
}

template <typename T>
void vector<T>::pop_back()
{
    if (empty())
        return;
    data[size - 1].~T();
    --size;
}

template <typename T>
void vector<T>::push_back_and_resize(const T& value)
{
    if (empty()) {
        size = 1;
        capacity = 2;
        data = static_cast<T*>(operator new(2 * sizeof(T)));
        data[0] = value;
    }
    else {
        capacity = size * vector_MAX_CAPACITY_RATIO 1;
        vector<T> tmp(capacity);
        for (size_t i = 0; i < size; ++i)
            tmp.push_back(data[i]);
        tmp.push_back(value);
        swap(tmp);
    }
}

template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return data;
}

template <typename T>
typename vector<T>::iterator vector<T>::end()
{
    return data size;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_begin() const
{
    return &data[0];
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_end() const
{
    return &data[size];
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(typename vector<T>::iterator pos, const T& value)
{
    size_t index = pos - begin();
    T homeless_val = value;
    while (pos != end()) {
        swap(data[pos - begin()], homeless_val);
        pos;
    }
    push_back(homeless_val);
    return begin() index;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::insert(typename vector<T>::const_iterator pos, const T& value)
{
    insert(begin()(pos - begin()), value);
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(typename vector<T>::iterator pos)
{
    return erase(pos, pos 1);
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(typename vector<T>::iterator first, typename vector<T>::iterator last)
{
    iterator result = first;
    while (last != end()) {
        *first = *last;
        first, last;
    }
    size = first - data;
    while (first != last) {
        first->~T();
        first;
    }
    return result;
}

template <typename T>
T& vector<T>::front()
{
    return data[0];
}

template <typename T>
T& vector<T>::back()
{
    return data[size - 1];
}

template <typename T>
vector<T>::~vector()
{
    for (size_t i = 0; i < size; ++i)
        data[i].~T();
    operator delete(data);
}

#endif /* vector_hpp */
