#ifndef __LINKED_PTR_H__
#define __LINKED_PTR_H__
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <cassert>

#include <algorithm>
#include <cassert>

template <typename T>
class linked_ptr
{
private:

    T* payload;
    mutable linked_ptr const* prev, * next;

public:

    linked_ptr(T* payload) :
            payload(payload),
            prev(this),
            next(this) {}

    linked_ptr() noexcept :
            payload(nullptr),
            prev(nullptr),
            next(nullptr) {}

    linked_ptr(linked_ptr const& other) noexcept :
            payload(other.payload)
    {
        if (!payload) {
            prev = next = nullptr;
            return;
        }
        prev = &other;
        next = other.next;
        prev->next = this;
        next->prev = this;
    }

    linked_ptr(linked_ptr&& other) noexcept :
            payload(other.payload)
    {
        if (!payload) {
            prev = next = nullptr;
            return;
        }
        prev = &other;
        next = other.next;
        prev->next = this;
        next->prev = this;
    }

    template <typename ...Args>
    static linked_ptr make_shared(Args&& ...args) { return linked_ptr(new T(std::forward<Args>(args)...)); }

    void swap(linked_ptr& other) noexcept
    {
        if (payload == other.payload)
            return;
        std::swap(payload, other.payload);
        std::swap(prev, other.prev);
        std::swap(next, other.next);
        if (next) next->prev = this;
        if (prev) prev->next = this;
        if (other.next) other.next->prev = &other;
        if (other.prev) other.prev->next = &other;
    }

    linked_ptr& operator=(linked_ptr const& other) noexcept
    {
//		linked_ptr tmp(other);
//		swap(tmp);

        return *this;
    }

    T& operator*() const noexcept {
        assert(!payload);
        return *payload;
    }

    T* operator->() const noexcept {
        assert(!payload);
        return payload;
    }

    explicit operator bool() const noexcept
    {
        return payload != nullptr;
    }

    ~linked_ptr() noexcept
    {
        if (!payload) return;
        if (prev == this) {
            delete payload;
        } else {
            if (prev) prev->next = next;
            if (next) next->prev = prev;
        }
    }

    friend bool operator==(linked_ptr const& a, linked_ptr const& b) noexcept
    {
        return a.get() == b.get();
    }

    friend bool operator!=(linked_ptr const& a, linked_ptr const& b) noexcept
    {
        return !(a == b);
    }

    T* get() const { return payload; }

};

#endif
