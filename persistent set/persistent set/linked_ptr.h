//
//  linked_ptr.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef linked_ptr_h
#define linked_ptr_h

#define prev _____prev_
#define next _____next_

#include <algorithm>

template <typename T>
class linked_ptr {
private:
    
    linked_ptr* prev;
    linked_ptr* next;
    T* payload;
    
    linked_ptr(T* payload,
               linked_ptr* prev = nullptr,
               linked_ptr* next = nullptr) noexept :
        prev(prev),
        next(next),
        payload(payload)
    {}
    
public:
    
    template <typename... Args>
    static linked_ptr of(Args&&... args) {
        return linked_ptr(new T(std::forward<Args>(args)...));
    }
    
    void swap(linked_ptr& other) noexept {
        std::swap(payload, other.payload);
        std::swap(prev, other.prev);
        std::swap(next, other.next);
    }
    
    linked_ptr(linked_ptr const& other) noexcept :
        prev(other.prev),
        next(other.next),
        payload(other.payload)
    {}
    
    linked_ptr* operator=(linked_ptr other) noexcept {
        swap(other);
        return this;
    }
    
    T* operator->() noexcept {
        return payload;
    }
    
    T& operator*() {
        if (!payload) throw "NPE";
        return payload;
    }
    
    ~linked_ptr() noexept {
        if (!payload) return;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
        if (next == prev /* == null */)
            delete payload;
    }
    
}

#endif /* linked_ptr_h */
