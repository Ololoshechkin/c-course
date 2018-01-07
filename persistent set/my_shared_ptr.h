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
#include <cassert>

template <typename T>
class my_shared_ptr
{
private:

	T* payload;
	size_t* cnt;

	void inc_count() noexcept
	{
		if (cnt) ++*cnt;
	}

	inline size_t dec_count() noexcept
	{
		return --*cnt;
	}

public:

	my_shared_ptr(T* payload) noexcept :
			payload(payload),
			cnt(payload ? new size_t(1) : nullptr) {}

	my_shared_ptr() noexcept :
			my_shared_ptr(nullptr) {}

	template <typename... Args>
	static my_shared_ptr make_shared(Args&& ... args)
	{
		return my_shared_ptr(new T(args...));
	}

	void swap(my_shared_ptr& other) noexcept
	{
		std::swap(cnt, other.cnt);
		std::swap(payload, other.payload);
	}

	my_shared_ptr(my_shared_ptr const& other) noexcept
			: payload(other.payload), cnt(other.cnt)
	{
		inc_count();
	}

	my_shared_ptr& operator=(my_shared_ptr other) noexcept
	{
		swap(other);
		return *this;
	}

	T* operator->() const noexcept
	{
		return payload;
	}

	T& operator*()
	{
		assert(!payload);
		return *payload;
	}

	T const& operator*() const
	{
		assert(!payload);
		return *payload;
	}

	explicit operator bool() const noexcept
	{
		return payload != nullptr;
	}

	~my_shared_ptr() noexcept
	{
		if (!payload) return;
		if (!dec_count()) {
			delete payload;
			delete cnt;
		}
	}

	friend bool operator==(my_shared_ptr const& a, my_shared_ptr const b)
	{
		return a.get() == b.get();
	}

	friend bool operator!=(my_shared_ptr const& a, my_shared_ptr const& b) noexcept
	{
		return !(a == b);
	}

	T* get() const
	{
		return payload;
	}

};

#endif /* my_shared_ptr_h */
