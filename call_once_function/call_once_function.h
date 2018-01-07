//
// Created by jetbrains on 06/01/2018.
//

#ifndef CALL_ONCE_FUNCTION_CALL_ONCE_FUNCTION_H
#define CALL_ONCE_FUNCTION_CALL_ONCE_FUNCTION_H


#include <cstddef>
#include <type_traits>
#include <functional>

template <typename Ret, typename... Args>
class call_once_function;

template <typename Ret, typename... Args>
class call_once_function<Ret(Args...)>
{
private:

	static const size_t SMALL_OBJECT_SIZE = 32;
	static const size_t SMALL_OBJECT_ALIGN = 8;

	typedef std::aligned_storage<SMALL_OBJECT_SIZE, SMALL_OBJECT_ALIGN> small_or_big_t;

	template <typename T>
	static T* as_big(small_or_big_t& storage) noexcept
	{
		return reinterpret_cast<T*&>(storage);
	}

	template <typename T>
	static T& as_small(small_or_big_t& storage) noexcept
	{
		return reinterpret_cast<T&>(storage);
	}

	class func_ops
	{
	public:

		using delete_t = void (*)(small_or_big_t&);
		using call_t = Ret (*)(small_or_big_t&, Args&& ... args);
		using move_t = void (*)(small_or_big_t&, small_or_big_t*);

		explicit func_ops(delete_t dtor,
						  call_t call,
						  move_t move) noexcept
				: dtor(dtor),
				  call(call),
				  move(move) {}

		template <typename T>
		static void big_dtor(small_or_big_t& storage)
		{
			delete as_big<T>(storage);
		}

		template <typename T>
		static void small_dtor(small_or_big_t& storage)
		{
			as_small<T>(storage).~T();
		}

//		template <typename T>
//		static T* small_move_construct(small_or_big_t&& storage)
//		{
//			new small_or_big_t(T(as_small<T>(storage)));
//		}
//
//		template <typename T>
//		static small_or_big_t* big_move_construct(small_or_big_t&& storage)
//		{
//			new small_or_big_t(as_big<T>(storage));
//		}

		template <typename T>
		static Ret big_call(small_or_big_t& storage, Args&& ... args)
		{
			return std::move((*as_big<T>(storage)))(std::forward<Args>(args)...);
		}

		template <typename T>
		static Ret small_call(small_or_big_t& storage, Args&& ... args)
		{
			return std::move(as_small<T>(storage))(std::forward<Args>(args)...);
		}

		template <typename T>
		static void big_move(small_or_big_t& storage, small_or_big_t* place)
		{
			new(place) T*(std::move(as_big<T>(storage)));
		}

		template <typename T>
		static void small_move(small_or_big_t& storage, small_or_big_t* place)
		{
			new(place) T(std::move(as_small<T>(storage)));
		}

		template <typename T>
		static func_ops* create_small()
		{
			static auto res = func_ops(
					&(func_ops::template small_dtor<T>),
					&(func_ops::template small_call<T>),
					&(func_ops::template small_move<T>)
			);
			return &res;
		}

		template <typename T>
		static func_ops* create_big()
		{
			static auto res = func_ops(
					&(func_ops::template big_dtor<T>),
					&(func_ops::template big_call<T>),
					&(func_ops::template big_move<T>)
			);
			return &res;
		}

		template <typename T>
		static func_ops* create_empty()
		{
			static delete_t dont_delete = [](small_or_big_t&) {};
			static call_t deprecated_call = [](small_or_big_t&, Args&& ...) -> Ret {
				throw std::bad_function_call();
			};
			static move_t dont_move = [](small_or_big_t&, small_or_big_t*) {};
			static auto res = func_ops(dont_delete, deprecated_call, dont_move);
			return &res;
		}

		delete_t dtor;
		call_t call;
		move_t move;
	};

	template <typename T>
	static constexpr bool is_small_v = (
			sizeof(T) <= SMALL_OBJECT_SIZE
			&& alignof(T) <= SMALL_OBJECT_ALIGN
			&& std::is_nothrow_move_constructible<T>::value
	);

	template <typename T>
	static func_ops* get_func_ops()
	{
		if constexpr (is_small_v<T>) {
			return func_ops::template create_small<T>();
		} else {
			return func_ops::template create_big<T>();
		}
	}

	small_or_big_t storage;
	func_ops* ops;

	void move_to(small_or_big_t& s, small_or_big_t* place)
	{
		ops->move(s, place);
	}

	func_ops* empty_ops() const noexcept
	{
		return func_ops::template create_empty<Ret(Args...)>();
	}

public:

	call_once_function() noexcept
			: ops(empty_ops()) {}

	template <typename T>
	explicit call_once_function(T f) noexcept(is_small_v<T>)
			: ops(get_func_ops<T>())
	{
		std::cout << "is_small : " << is_small_v<T> << '\n';
		if constexpr (is_small_v<T>) {
			new(&storage) T(std::move(f));
		} else {
			new(&storage) T*(new T(std::move(f)));
		}
	}

	call_once_function(call_once_function&& other) noexcept
			: ops(other.ops)
	{
		other.move_to(other.storage, &storage);
		other.ops->dtor(other.storage);
		other.ops = empty_ops();
	}

	Ret operator()(Args... args)&&
	{
		call_once_function copy = std::move(*this);
		return copy.ops->call(copy.storage, std::forward<Args>(args)...);
	}

	void swap(call_once_function& other) noexcept
	{
		small_or_big_t tmp1, tmp2;
		ops->move(storage, &tmp1);
		other.ops->move(other.storage, &tmp1);
		move_to(tmp1, &other.storage);
		other.move_to(tmp2, &storage);
		ops->dtor(tmp1);
		other.ops->dtor(tmp2);
		std::swap(ops, other.ops);
	}

	call_once_function& operator=(call_once_function&& other) noexcept
	{
		call_once_function tmp(std::move(other));
		swap(tmp);
		return *this;
	}

	explicit operator bool() const noexcept
	{
		return ops != empty_ops();
	}

	~call_once_function()
	{
		ops->dtor(storage);
	}

};

#endif //CALL_ONCE_FUNCTION_CALL_ONCE_FUNCTION_H
