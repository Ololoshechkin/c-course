//
//  my_linked_ptr.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef my_linked_ptr_h
#define my_linked_ptr_h
#include <algorithm>

template <typename T>
class my_linked_ptr {
private:
    
    my_linked_ptr* prev;
    my_linked_ptr* next;
    T* payload;
    
    my_linked_ptr(T* payload,
               my_linked_ptr* prev,
               my_linked_ptr* next) noexcept
    :   prev(prev),
        next(next),
        payload(payload)
    {}
    
public:
    
    my_linked_ptr(T* ptr) noexcept
    : my_linked_ptr(ptr, nullptr, nullptr)
    {}
    
    template <typename... Args>
    static my_linked_ptr make_shared(Args&& ... args) {
        return my_linked_ptr(new T(std::forward<Args>(args)...));
    }
    
    my_linked_ptr() noexcept
    : my_linked_ptr(nullptr)
    {}
    
    void swap(my_linked_ptr& other) noexcept {
        std::swap(payload, other.payload);
        std::swap(prev, other.prev);
        std::swap(next, other.next);
    }
    
    my_linked_ptr(my_linked_ptr const& other) noexcept :
        prev(other.prev),
        next(other.next),
        payload(other.payload)
    {}
    
    my_linked_ptr* operator=(my_linked_ptr other) noexcept {
        swap(other);
        return this;
    }
    
    T* operator->() const noexcept {
        return payload;
    }
    
    T& operator*() {
        if (!payload) throw "NPE";
        return payload;
    }
    
    operator bool() const noexcept {
        return (bool) payload;
    }
    
    ~my_linked_ptr() noexcept {
        if (!payload) return;
        if (prev == this) {
            delete payload;
        } else {
            if (prev) prev->next = next;
            if (next) next->prev = prev;
        }
    }
    
    friend bool operator==(my_linked_ptr<T> a, my_linked_ptr<T> b) {
        return a.payload == b.payload;
    }
	
	T* get() const {
		return payload;
	}
    
};

#endif /* my_linked_ptr_h */
