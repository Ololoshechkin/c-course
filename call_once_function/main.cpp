#include <iostream>
#include "call_once_function.h"

template <typename T>
bool constexpr is_lvalue_reference_v = std::is_lvalue_reference<T&&>::value;

template <>
struct std::enable_if<true, int> {
	typedef char type;
};

template <typename T>
void g(T x, std::enable_if_t<true, T>* t = nullptr) {
	std::cout << x;
}

template <>
void g(int x, std::enable_if_t<true, char>* t = nullptr) {
	std::cout << x;
}

template <typename T>
std::enable_if_t<is_lvalue_reference_v<T>, void> f(T&& t) {
	std::cout << t;
}

int main()
{
	int x;


	std::cout << is_lvalue_reference_v<decltype((x))> << '\n';
	std::cout << is_lvalue_reference_v<decltype(5)> << '\n';

//	f(5);
//	f(x);

	g(100);

//	std::cout << "Hello, World!" << std::endl;
//	call_once_function<int()> get_17_once_small(&get_17_once_impl);
////	std::cout << std::move(get_17_once_small)() << '\n';
//	call_once_function<int()> get_18_once_big([]() {
//		return 18;
//	});
////	std::cout << std::move(get_18_once_big)() << '\n';
//	get_17_once_small.swap(get_18_once_big);
////	std::cout << std::move(get_17_once_small)() << '\n';
//	std::cout << std::move(get_18_once_big)() << '\n';
//	call_once_function<int()> empty;
//	get_17_once_small.swap(empty);
//	std::cout << std::move(empty)() << '\n';
//	std::cout << "empty: " << (empty ? "valid" : "invalid") << '\n';
//	std::cout << "get_17_once_small: " << (get_17_once_small ? "valid" : "invalid") << '\n';
//
//	call_once_function<int()> f1([]() {
//		return 1;
//	});
//
//	call_once_function<int()> f2([]() {
//		return 2;
//	});
//
////	std::cout << std::move(f1)() << '\n';
//	std::cout << std::move(f2)() << '\n';
//
//	f2 = std::move(f1);
//
////	std::cout << f1() << '\n';
//	std::cout << std::move(f2)() << '\n';

	return 0;
}