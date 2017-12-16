//
//  my_shared_ptr.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef my_shared_ptr_h
#define my_shared_ptr_h

#include <algorithm>
#include <iostream>

template <typename T>
class my_shared_ptr {
private:
    
    struct connected_block {
        T payload;
        size_t cnt;
        template<typename... Args>
        connected_block(Args&&... args) noexcept :
            payload(std::forward<Args>(args)...),
            cnt(1)
        {}
    }* ptr;
    
    void inc_count() noexcept {
        if (ptr) ptr->cnt++;
    }
    
    size_t dec_count() noexcept {
        return --ptr->cnt;
    }
    
    my_shared_ptr(connected_block* ptr) noexcept : ptr(ptr) {
        inc_count();
    }
    
public:
    
    template<typename... Args>
    static my_shared_ptr of(Args&&... args) noexcept {
        return my_shared_ptr(new connected_block(std::forward<Args>(args)...));
    }
    
    my_shared_ptr() noexcept
    : my_shared_ptr(nullptr)
    {}
    
    void swap(my_shared_ptr& other) noexcept {
        std::swap(ptr, other.ptr);
    }
    
    my_shared_ptr(my_shared_ptr const& other) noexcept
    : ptr(other.ptr)
    {
        inc_count();
    }
    
    my_shared_ptr* operator=(my_shared_ptr other) noexcept {
        swap(other);
        return this;
    }
    
    T* operator->() noexcept {
        return ptr ? &ptr->payload : nullptr;
    }
    
    T& operator*() {
        if (!ptr) throw "NPE";
        return ptr->payload;
    }
    
    T const& operator*() const {
        if (!ptr) throw "NPE";
        return ptr->payload;
    }
    
    operator bool() const noexcept {
        return (bool) ptr;
    }
    
    ~my_shared_ptr() noexcept {
        if (!ptr) return;
        if (!dec_count()) {
            delete ptr;
        }
    }
    
    friend bool operator==(my_shared_ptr<T> a, my_shared_ptr<T> b) {
        std::cerr << "==(ptr)\n";
        if (!a.ptr || !b.ptr) {
            return !a.ptr && !b.ptr;
        }
        return *a == *b;
    }
    
};

#endif /* my_shared_ptr_h */
