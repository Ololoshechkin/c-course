//
//  shared_ptr.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef shared_ptr_h
#define shared_ptr_h

#include <algorithm>

template <typename T>
class shared_ptr {
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
        ptr->cnt++;
    }
    
    size_t dec_count() noexcept {
        return --ptr->cnt;
    }
    
    shared_ptr(connected_block* ptr) noexcept : ptr(ptr) {
        inc_count();
    }
    
public:
    
    template<typename... Args>
    static shared_ptr of(Args&&... args) noexcept {
        return shared_ptr(new connected_block(std::forward<Args>(args)...));
    }
    
    shared_ptr() noexcept
    : shared_ptr(nullptr)
    {}
    
    void swap(shared_ptr& other) noexcept {
        std::swap(ptr, other.ptr);
    }
    
    shared_ptr(shared_ptr const& other) noexcept :
        ptr(other.ptr)
    {
        inc_count();
    }
    
    shared_ptr* operator=(shared_ptr other) noexcept {
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
    
    operator bool() const noexcept {
        return (bool) *this;
    }
    
    ~shared_ptr() noexcept {
        if (!ptr) return;
        if (!dec_count()) {
            delete ptr;
        }
    }
    
    
};

#endif /* shared_ptr_h */
