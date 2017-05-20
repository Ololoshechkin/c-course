#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define DECLARE_SET(T) \
struct set_##T\
{\
	typedef bool (*less_t)(T const&, T const&);\
	\
	set_##T(less_t less) : less(less) {}\
	\
	T first();	\
\
private:\
	less_t less;\
};

DECLARE_SET(double);

template <typename T>
struct set
{
};

template <typename T>
bool lessF(T const& a, T const& b)
{
	return a < b;
}

//primary template:
template <typename T>
struct vect
{};

//explicit template:
template <>
struct vect<bool>
{};

//partual template:
template <typename U>
struct vect<U*>
{};


// meta-function:
template <typename A, typename B>
struct is_sameT
{
	static const bool value = false;
};

template <typename A>
struct is_sameT<A, A>
{
	static const bool value = true;
};


// geom example:
template <typename T>
struct numeric_traits
{};

template <>
struct numeric_traits<float>
{
	static float constexpr epsilon = 1e-5;
};

template <>
struct numeric_traits<double>
{
	static double constexpr epsilon = 1e-10;
};

template <typename T>
bool eps_equal(T a, T b)
{
	return std::abs(a - b) < numeric_traits<T>::epsilon;
}

// default params
template <typename T = int>
struct ptr
{
	T* val;
};

template <typename T>
void f()
{
	typename T::xx a;
	//T b;
	//T::foo < b > c; // expr
	//T::template foo<b> d; // declatation
	
	//int g(T::foo); // variable
	//int g(typename T::foo);// function
	
	//(T::foo)-b; // binary
	//(typename T::foo)-b; //typecast
}

int main()
{ 
	bool ok = lessF(1, 2);//auto detect type (int)
	
	vect<int> vi;// primary template is chosen
	vect<bool> vb;// explicit template for bool is chosen
	vect<int*> vip;// primary template is chosen
	
	
	cout << is_sameT<int, bool>::value << endl; // false
	cout << is_sameT<int, int>::value << endl; // true
	
	double x = 0.5, y = 0.5 + numeric_traits<double>::epsilon / 2.0;
	cout << eps_equal(x, y) << endl; // true
	x = 0.5, y = 0.5 + numeric_traits<float >::epsilon;
	cout << eps_equal(x, y) << endl; // false
	
	ptr<> p; // default. p : ptr<int>
	p.val = new int();
	return 0;
}