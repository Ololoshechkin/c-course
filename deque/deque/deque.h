//
//  deque.h
//  deque
//
//  Created by Vadim on 01.07.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef deque_h
#define deque_h

#include <algorithm>
#include <iostream>

template <typename T>
class deque {
private:
    size_t sz, capacity;
    size_t left;
    T* data;
    
    size_t right()
    {
        if (!sz) return 0;
        return (left + sz) % capacity;
    }
    
    size_t exact_right() const
    {
        return (left + sz - 1) % capacity;
    }
    
    void ensure_capacity(size_t expected_size)
    {
        if (!expected_size) clear();
        if (expected_size >= capacity) {
            deque<T> tmp((capacity << 1) + 2);
            for (size_t i = 0, pos = left; i < sz; ++i, pos = (pos + 1) % capacity)
                tmp.push_back(data[pos]);
            swap(tmp);
        }
    }
    
    deque(size_t capacity)
    : sz(0)
    , capacity(capacity)
    , left(0)
    , data(static_cast<T*>(operator new(capacity * sizeof(T))))
    {}
    
public:
    
    deque()
    : sz(0)
    , capacity(0)
    , left(0)
    , data(nullptr)
    {}
    
    void swap(deque& other)
    {
        std::swap(sz, other.sz);
        std::swap(left, other.left);
        std::swap(capacity, other.capacity);
        std::swap(data, other.data);
    }
    
    deque(deque const& other)
    : sz(other.sz)
    , capacity(other.capacity)
    , left(other.left)
    , data(static_cast<T*>(operator new(other.capacity * sizeof(T))))
    {
        for (size_t i = 0; i < sz; ++i) {
            try {
               new (&data[i]) T(other.data[i]);
            } catch(...) {
                for (size_t j = 0; j < i; ++j) {
                    data[j].~T();
                }
                delete (data);
                throw;
            }
        }
    }
    
    deque& operator=(deque const& other)
    {
        deque<T> tmp(other);
        swap(tmp);
        return *this;
    }
    
    bool empty() const
    {
        return !sz;
    }
    
    size_t size() const
    {
        return sz;
    }
    
    void clear()
    {
        for (size_t i = 0; i < capacity; ++i)
            data[i].~T();
        delete(data);
        sz = 0;
        capacity = 0;
        data = nullptr;
    }
    
    void push_back(T const& element)
    {
        ensure_capacity(sz + 1);
        new (&data[right()]) T(element);
        sz++;
    }
    
    void push_front(T const& element)
    {
        ensure_capacity(sz + 1);
        left = (capacity + left - 1) % capacity;
        new (&data[left]) T(element);
        sz++;
    }
    
    void pop_front()
    {
        data[left].~T();
        left++;
        left %= capacity;
        sz--;
    }
    
    void pop_back()
    {
        data[exact_right()].~T();
        sz--;
    }
    
    T const& front() const
    {
        return data[left];
    }
    
    T const& back() const
    {
        return data[exact_right()];
    }
    
    T& front()
    {
        return data[left];
    }
    
    T& back()
    {
        return data[exact_right()];
    }
    
    T& operator[](size_t i)
    {
        return data[(left + i) % capacity];
    }
    
    T const& operator[](size_t i) const
    {
        return data[(left + i) % capacity];
    }
    template<typename V>
    struct generic_iterator
    {
        generic_iterator& operator++()
        {
            ++index;
            return *this;
        }
        generic_iterator& operator--()
        {
            --index;
            return *this;
        }
        generic_iterator operator++(int)
        {
            generic_iterator answer = *this;
            ++(*this);
            return answer;
        }
        generic_iterator operator--(int)
        {
            generic_iterator answer = *this;
            --(*this);
            return answer;
        }
        V& operator*() const
        {
            return *(begin + get_pos());
        }
        friend bool operator==(generic_iterator const& it, generic_iterator const& other)
        {
            return it.begin == other.begin && it.left == other.left && it.capacity == other.capacity && it.index == other.index;
        }
        friend bool operator!=(generic_iterator const& it, generic_iterator const& other)
        {
            return !(it == other);
        }
        friend size_t operator-(generic_iterator const& it,generic_iterator const& other)
        {
            return it.index - other.index;
        }
        friend generic_iterator operator+(generic_iterator const& it, size_t delta)
        {
            return generic_iterator(it.begin, it.index + delta, it.left, it.capacity);
        }
        friend generic_iterator operator-(generic_iterator const& it, size_t delta)
        {
            return it + (-delta);
        }
        friend generic_iterator operator+(size_t delta, generic_iterator const& it)
        {
            return it + delta;
        }
        friend generic_iterator operator-(size_t delta, generic_iterator const& it)
        {
            return it - delta;
        }
        friend generic_iterator& operator+=(generic_iterator& it, size_t delta)
        {
            it = it + delta;
            return it;
        }
        friend generic_iterator& operator-=(generic_iterator& it, size_t delta)
        {
            it = it - delta;
            return it;
        }
        template <typename V2>
        generic_iterator(const generic_iterator<V2> &other,
                    typename std::enable_if<std::is_same<V, const V2>::value>::type * = nullptr)
        : begin(other.begin)
        , index(other.index)
        , left(other.left)
        , capacity(other.capacity)
        {}
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef V* pointer;
        typedef V& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    private:
        T* begin;
        size_t index, left;
        size_t capacity;
        size_t get_pos() const
        {
            return (left + index) % capacity;
        }
        generic_iterator(T* begin, size_t index, size_t left, size_t capacity)
        : begin(begin)
        , index(index)
        , left(left)
        , capacity(capacity)
        {}
        friend deque<T>;
    };
    typedef generic_iterator<T> iterator;
    typedef generic_iterator<const T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    iterator begin()
    {
        return iterator(data, 0, left, capacity);
    }
    
    const_iterator begin() const
    {
        return const_iterator(data, 0, left, capacity);
    }
    
    iterator end()
    {
        return iterator(data, sz, left, capacity);
    }
    
    const_iterator end() const
    {
        return const_iterator(data, sz, left, capacity);
    }
    
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }
    
    iterator insert(const_iterator it, T const& element)
    {
        if (empty()) {
            push_back(element);
            return begin();
        }
        size_t pos = it.index;
        if (pos <= sz - pos) {
            push_front(element);
            iterator cur = begin(), target = cur + pos;;
            ++cur;
            while ((cur - 1) != target) {
                *(cur - 1) = *cur;
                cur++;
            }
            *target = element;
        } else {
            iterator cur = begin() + pos;
            T homeless_val = element;
            while (cur != end()) {
                std::swap(*cur, homeless_val);
                ++cur;
            }
            push_back(homeless_val);
        }
        return begin() + pos;
    }
    
    iterator erase(const_iterator it)
    {
        size_t pos = it.index;
        if (pos <= sz - pos) {
            iterator cur = begin() + pos;;
            while (cur != begin()) {
                *cur = *(cur - 1);
                --cur;
            }
            pop_front();
        } else {
            iterator cur = begin() + pos;
            while (cur != (end() - 1)) {
                *cur = *(cur + 1);
                cur++;
            }
            pop_back();
        }
        return begin() + pos;
    }

    ~deque()
    {
        if (!capacity)
            return;
        for (size_t i = 0, pos = left; i < sz; ++i, pos = (pos + 1) % capacity)
            data[i].~T();
        operator delete(data);
    }
   
};

template<typename T>
void swap(deque<T>& l, deque<T>& r)
{
    l.swap(r);
}

#endif /* deque_h */
