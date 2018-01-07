//
//  my_my_linked_ptr.h
//  persistent set
//
//  Created by Vadim on 14/10/2017.
//  Copyright © 2017 Vadim. All rights reserved.
//

#ifndef my_linked_ptr_h
#define my_linked_ptr_h

#include <algorithm>
#include <cassert>

template <typename T>
class my_linked_ptr
{
private:

	T* payload;
	mutable my_linked_ptr const* prev, * next;

public:

	my_linked_ptr(T* payload) :
			payload(payload),
			prev(this),
			next(this) {}

	my_linked_ptr() noexcept :
			payload(nullptr),
			prev(nullptr),
			next(nullptr) {}

	my_linked_ptr(my_linked_ptr const& other) noexcept :
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
	static my_linked_ptr make_shared(Args&& ...args) { return my_linked_ptr(new T(std::forward<Args>(args)...)); }

	void swap(my_linked_ptr& other) noexcept
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

	my_linked_ptr& operator=(my_linked_ptr const& other) noexcept
	{
//		my_linked_ptr tmp(other);
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

	~my_linked_ptr() noexcept
	{
		if (!payload) return;
		if (prev == this) {
			delete payload;
		} else {
			if (prev) prev->next = next;
			if (next) next->prev = prev;
		}
	}

	friend bool operator==(my_linked_ptr const& a, my_linked_ptr const& b) noexcept
	{
		return a.get() == b.get();
	}

	friend bool operator!=(my_linked_ptr const& a, my_linked_ptr const& b) noexcept
	{
		return !(a == b);
	}

	T* get() const { return payload; }

};

#endif /* my_linked_ptr_h */
