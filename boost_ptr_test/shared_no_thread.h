//
// Created by Vadim on 21/12/2017.
//

#ifndef POINTERS_TEST_SHARED_NO_THREAD_H
#define POINTERS_TEST_SHARED_NO_THREAD_H

#include <type_traits>
#include <memory>

typedef decltype(nullptr) nullptr_t;

class  __shared_count_no_thread
		{
	__shared_count_no_thread(const __shared_count_no_thread&);
	__shared_count_no_thread& operator=(const __shared_count_no_thread&);
		
		protected:
		long __shared_owners_;
		virtual ~__shared_count_no_thread();
		private:
		virtual void __on_zero_shared() noexcept = 0;
		
		public:
		
		explicit __shared_count_no_thread(long __refs = 0) noexcept 
		: __shared_owners_(__refs) {}
		
		void __add_shared() noexcept ;
		bool __release_shared() noexcept;
	
		long use_count() const noexcept {
			return __shared_owners_ + 1;
		}
		};

class __shared_weak_count_no_thread
		: private __shared_count_no_thread
{
long __shared_weak_owners_;

public:
explicit __shared_weak_count_no_thread(long __refs = 0) noexcept 
		: __shared_count_no_thread(__refs),
		  __shared_weak_owners_(__refs) {}
protected:
virtual ~__shared_weak_count_no_thread();

public:
void __add_shared() noexcept;
void __add_weak() noexcept;
void __release_shared() noexcept;
void __release_weak() noexcept;

long use_count() const noexcept {return __shared_count_no_thread::use_count();}
virtual void __on_zero_shared_weak() noexcept = 0;
};

template <class _Tp, class _Dp, class _Alloc>
class __shared_ptr_pointer
		: public __shared_weak_count_no_thread
{
	std::__compressed_pair<std::__compressed_pair<_Tp, _Dp>, _Alloc> __data_;
public:
	
	__shared_ptr_pointer(_Tp __p, _Dp __d, _Alloc __a)
			:  __data_(std::__compressed_pair<_Tp, _Dp>(__p, _VSTD::move(__d)), _VSTD::move(__a)) {}

#ifndef _LIBCPP_NO_RTTI
	virtual const void* __get_deleter(const std::type_info&) const _NOEXCEPT;
#endif

private:
	virtual void __on_zero_shared() _NOEXCEPT;
	virtual void __on_zero_shared_weak() _NOEXCEPT;
};

template<class _Tp>
class shared_ptr_no_thread
		{
				public:
				typedef _Tp element_type;

#if _LIBCPP_STD_VER > 14
				typedef std::weak_ptr<_Tp> weak_type;
#endif
				private:
				element_type*      __ptr_;
	__shared_weak_count_no_thread* __cntrl_;
				
				struct __nat {int __for_bool_;};
				public:
				constexpr shared_ptr_no_thread() noexcept;
				constexpr shared_ptr_no_thread(nullptr_t) noexcept;
				constexpr shared_ptr_no_thread(shared_ptr_no_thread&&) noexcept;
				constexpr shared_ptr_no_thread(shared_ptr_no_thread&) noexcept;
				template<class _Yp>
				explicit shared_ptr_no_thread(_Yp* __p,
				typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type = __nat());
				template<class _Yp, class _Dp>
				shared_ptr_no_thread(_Yp* __p, _Dp __d,
				typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type = __nat());
				template<class _Yp, class _Dp, class _Alloc>
				shared_ptr_no_thread(_Yp* __p, _Dp __d, _Alloc __a,
				typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type = __nat());
				template <class _Dp> shared_ptr_no_thread(nullptr_t __p, _Dp __d);
				template <class _Dp, class _Alloc> shared_ptr_no_thread(nullptr_t __p, _Dp __d, _Alloc __a);
				template<class _Yp>  shared_ptr_no_thread(const shared_ptr_no_thread<_Yp>& __r, element_type* __p) noexcept;
				shared_ptr_no_thread(const shared_ptr_no_thread& __r) noexcept;
				template<class _Yp>
				shared_ptr_no_thread(const shared_ptr_no_thread<_Yp>& __r,
				typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type = __nat())
				noexcept;
				
				~shared_ptr_no_thread();
				
				
				shared_ptr_no_thread& operator=(const shared_ptr_no_thread& __r) noexcept;
				template<class _Yp>
				typename std::enable_if
				<
				std::is_convertible<_Yp*, element_type*>::value,
				shared_ptr_no_thread&
				>::type
				operator=(const shared_ptr_no_thread<_Yp>& __r) noexcept;
				shared_ptr_no_thread& operator=(shared_ptr_no_thread&& __r) noexcept;
				template<class _Yp>
				typename std::enable_if
				<
						std::is_convertible<_Yp*, element_type*>::value,
				shared_ptr_no_thread<_Tp>&
				>::type
				operator=(shared_ptr_no_thread<_Yp>&& __r);
				template<class _Yp>

				
				void swap(shared_ptr_no_thread& __r) noexcept
				{
					_VSTD::swap(__ptr_, __r.__ptr_);
					_VSTD::swap(__cntrl_, __r.__cntrl_);
				}
				
				void reset() noexcept;
				template<class _Yp>
				typename std::enable_if
				<
						std::is_convertible<_Yp*, element_type*>::value,
				void
				>::type
				
	reset(_Yp* __p);
				template<class _Yp, class _Dp>
				typename std::enable_if
				<
						std::is_convertible<_Yp*, element_type*>::value,
				void
				>::type
				
				
				reset(_Yp* __p, _Dp __d);
				template<class _Yp, class _Dp, class _Alloc>
				typename std::enable_if
				<
						std::is_convertible<_Yp*, element_type*>::value,
				void
				>::type
				
				
				reset(_Yp* __p, _Dp __d, _Alloc __a);
				
				
				element_type* get() const noexcept {return __ptr_;}
				
	
				typename std::add_lvalue_reference<element_type>::type operator*() const noexcept
				{return *__ptr_;}
				
				element_type* operator->() const noexcept {return __ptr_;}
				
				long use_count() const noexcept {return __cntrl_ ? __cntrl_->use_count() : 0;}
				
				bool unique() const noexcept {return use_count() == 1;}
				
				explicit operator bool() const noexcept {return get() != 0;}
				template <class _Up>
				
				bool owner_before(shared_ptr_no_thread<_Up> const& __p) const
				{return __cntrl_ < __p.__cntrl_;}
				template <class _Up>
				
//				bool owner_before(weak_ptr<_Up> const& __p) const
//				{return __cntrl_ < __p.__cntrl_;}
				
				bool
				__owner_equivalent(const shared_ptr_no_thread& __p) const
				{return __cntrl_ == __p.__cntrl_;}

//#ifndef _LIBCPP_NO_RTTI
//				template <class _Dp>
//				_Dp* __get_deleter() const noexcept
//				{return (_Dp*)(__cntrl_ ? __cntrl_->__get_deleter(typeid(_Dp)) : 0);}
//#endif  // _LIBCPP_NO_RTTI
//
//#ifndef _LIBCPP_HAS_NO_VARIADICS
//				
//				template<class ..._Args>
//				static
//				shared_ptr_no_thread<_Tp>
//				
//				template<class _Alloc, class ..._Args>
//				static
//				shared_ptr_no_thread<_Tp>
//				allocate_shared(const _Alloc& __a, _Args&& ...__args);
//
//#else  // _LIBCPP_HAS_NO_VARIADICS
//
//    template<class _Alloc>
//        static shared_ptr_no_thread<_Tp>
//        allocate_shared(const _Alloc& __a);
//
//    template<class _Alloc, class _A0>
//        static shared_ptr_no_thread<_Tp>
//        allocate_shared(const _Alloc& __a, _A0& __a0);
//
//    template<class _Alloc, class _A0, class _A1>
//        static shared_ptr_no_thread<_Tp>
//        allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1);
//
//    template<class _Alloc, class _A0, class _A1, class _A2>
//        static shared_ptr_no_thread<_Tp>
//        allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1, _A2& __a2);
//
//#endif  // _LIBCPP_HAS_NO_VARIADICS
				
				private:
				
				void __enable_weak_this(const volatile void*, const volatile void*) noexcept {}
				
				template <class _Up> friend class _LIBCPP_TEMPLATE_VIS shared_ptr_no_thread;
				template <class _Up> friend class _LIBCPP_TEMPLATE_VIS weak_ptr;
		};

template<class _Tp>
inline
_LIBCPP_CONSTEXPR
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread() noexcept
		: __ptr_(0),
		  __cntrl_(0)
{
}

template<class _Tp>
inline
_LIBCPP_CONSTEXPR
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(nullptr_t) noexcept
		: __ptr_(0),
		  __cntrl_(0)
{
}

template<class _Tp>
template<class _Yp>
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(_Yp* __p,
                            typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type)
		: __ptr_(__p)
{
	std::unique_ptr<_Yp> __hold(__p);
	typedef __shared_ptr_pointer<_Yp*, std::default_delete<_Yp>, std::allocator<_Yp> > _CntrlBlk;
	__cntrl_ = new _CntrlBlk(__p, std::default_delete<_Yp>(), std::allocator<_Yp>());
	__hold.release();
	__enable_weak_this(__p, __p);
}

template<class _Tp>
template<class _Yp, class _Dp>
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(_Yp* __p, _Dp __d,
                            typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type)
		: __ptr_(__p)
{
#ifndef _LIBCPP_NO_EXCEPTIONS
	try
	{
#endif  // _LIBCPP_NO_EXCEPTIONS
		typedef __shared_ptr_pointer<_Yp*, _Dp, std::allocator<_Yp> > _CntrlBlk;
		__cntrl_ = new _CntrlBlk(__p, __d, std::allocator<_Yp>());
		__enable_weak_this(__p, __p);
#ifndef _LIBCPP_NO_EXCEPTIONS
	}
	catch (...)
	{
		__d(__p);
		throw;
	}
#endif  // _LIBCPP_NO_EXCEPTIONS
}

template<class _Tp>
template<class _Dp>
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(nullptr_t __p, _Dp __d)
		: __ptr_(0)
{
#ifndef _LIBCPP_NO_EXCEPTIONS
	try
	{
#endif  // _LIBCPP_NO_EXCEPTIONS
		typedef __shared_ptr_pointer<nullptr_t, _Dp, std::allocator<_Tp> > _CntrlBlk;
		__cntrl_ = new _CntrlBlk(__p, __d, std::allocator<_Tp>());
#ifndef _LIBCPP_NO_EXCEPTIONS
	}
	catch (...)
	{
		__d(__p);
		throw;
	}
#endif  // _LIBCPP_NO_EXCEPTIONS
}
//
//template<class _Tp>
//template<class _Yp, class _Dp, class _Alloc>
//shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(_Yp* __p, _Dp __d, _Alloc __a,
//                            typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type)
//		: __ptr_(__p)
//{
//#ifndef _LIBCPP_NO_EXCEPTIONS
//	try
//	{
//#endif  // _LIBCPP_NO_EXCEPTIONS
//		typedef __shared_ptr_pointer<_Yp*, _Dp, _Alloc> _CntrlBlk;
//		typedef typename std::__allocator_traits_rebind<_Alloc, _CntrlBlk>::type _A2;
//		typedef std::__allocator_destructor<_A2> _D2;
//		_A2 __a2(__a);
//		::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
//				_CntrlBlk(__p, __d, __a);
//		__cntrl_ = _VSTD::addressof(*__hold2.release());
//		__enable_weak_this(__p, __p);
//#ifndef _LIBCPP_NO_EXCEPTIONS
//	}
//	catch (...)
//	{
//		__d(__p);
//		throw;
//	}
//#endif  // _LIBCPP_NO_EXCEPTIONS
//}

//template<class _Tp>
//template<class _Dp, class _Alloc>
//shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(nullptr_t __p, _Dp __d, _Alloc __a)
//		: __ptr_(0)
//{
//#ifndef _LIBCPP_NO_EXCEPTIONS
//	try
//	{
//#endif  // _LIBCPP_NO_EXCEPTIONS
//		typedef __shared_ptr_pointer<nullptr_t, _Dp, _Alloc> _CntrlBlk;
//		typedef typename std::__allocator_traits_rebind<_Alloc, _CntrlBlk>::type _A2;
//		typedef std::__allocator_destructor<_A2> _D2;
//		_A2 __a2(__a);
//		::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
//				_CntrlBlk(__p, __d, __a);
//		__cntrl_ = _VSTD::addressof(*__hold2.release());
//#ifndef _LIBCPP_NO_EXCEPTIONS
//	}
//	catch (...)
//	{
//		__d(__p);
//		throw;
//	}
//#endif  // _LIBCPP_NO_EXCEPTIONS
//}

template<class _Tp>
template<class _Yp>
inline
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(const shared_ptr_no_thread<_Yp>& __r, element_type *__p) noexcept
		: __ptr_(__p),
		  __cntrl_(__r.__cntrl_)
{
	if (__cntrl_)
		__cntrl_->__add_shared();
}

template<class _Tp>
inline
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(const shared_ptr_no_thread& __r) noexcept
		: __ptr_(__r.__ptr_),
		  __cntrl_(__r.__cntrl_)
{
	if (__cntrl_)
		__cntrl_->__add_shared();
}

template<class _Tp>
template<class _Yp>
inline
shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(const shared_ptr_no_thread<_Yp>& __r,
                            typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type)
noexcept
		: __ptr_(__r.__ptr_),
		  __cntrl_(__r.__cntrl_)
{
	if (__cntrl_)
		__cntrl_->__add_shared();
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
inline
constexpr shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(shared_ptr_no_thread&& __r) noexcept
		: __ptr_(__r.__ptr_),
		  __cntrl_(__r.__cntrl_)
{
	__r.__ptr_ = 0;
	__r.__cntrl_ = 0;
}

//template<class _Tp>
//template<class _Yp>
//inline
//shared_ptr_no_thread<_Tp>::shared_ptr_no_thread(shared_ptr_no_thread<_Yp>&& __r,
//                            typename std::enable_if<std::is_convertible<_Yp*, element_type*>::value, __nat>::type)
//noexcept
//		: __ptr_(__r.__ptr_),
//		  __cntrl_(__r.__cntrl_)
//{
//	__r.__ptr_ = 0;
//	__r.__cntrl_ = 0;
//}

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

#else  // _LIBCPP_HAS_NO_VARIADICS


template<class _Tp>
template<class _Alloc>
shared_ptr_no_thread<_Tp>
shared_ptr_no_thread<_Tp>::allocate_shared(const _Alloc& __a)
{
    unique_ptr<_CntrlBlk, _D2> __hold2(__alloc2.allocate(1), _D2(__alloc2, 1));
    typedef __shared_ptr_no_thread_emplace<_Tp, _Alloc> _CntrlBlk;
    typedef typename __allocator_traits_rebind<_Alloc, _CntrlBlk>::type _Alloc2;
    typedef __allocator_destructor<_Alloc2> _D2;
    _Alloc2 __alloc2(__a);
    ::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
        _CntrlBlk(__a);
    shared_ptr_no_thread<_Tp> __r;
    __r.__ptr_ = __hold2.get()->get();
    __r.__cntrl_ = _VSTD::addressof(*__hold2.release());
    __r.__enable_weak_this(__r.__ptr_, __r.__ptr_);
    return __r;
}

template<class _Tp>
template<class _Alloc, class _A0>
shared_ptr_no_thread<_Tp>
shared_ptr_no_thread<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0)
{
    typedef __shared_ptr_no_thread_emplace<_Tp, _Alloc> _CntrlBlk;
    typedef typename __allocator_traits_rebind<_Alloc, _CntrlBlk>::type _Alloc2;
    typedef __allocator_destructor<_Alloc2> _D2;
    _Alloc2 __alloc2(__a);
    ::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
        _CntrlBlk(__a, __a0);
    shared_ptr_no_thread<_Tp> __r;
    __r.__ptr_ = __hold2.get()->get();
    __r.__cntrl_ = _VSTD::addressof(*__hold2.release());
    __r.__enable_weak_this(__r.__ptr_, __r.__ptr_);
    return __r;
}

template<class _Tp>
template<class _Alloc, class _A0, class _A1>
shared_ptr_no_thread<_Tp>
shared_ptr_no_thread<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1)
{
    typedef __shared_ptr_no_thread_emplace<_Tp, _Alloc> _CntrlBlk;
    typedef typename __allocator_traits_rebind<_Alloc, _CntrlBlk>::type _Alloc2;
    typedef __allocator_destructor<_Alloc2> _D2;
    _Alloc2 __alloc2(__a);
    ::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
        _CntrlBlk(__a, __a0, __a1);
    shared_ptr_no_thread<_Tp> __r;
    __r.__ptr_ = __hold2.get()->get();
    __r.__cntrl_ = _VSTD::addressof(*__hold2.release());
    __r.__enable_weak_this(__r.__ptr_, __r.__ptr_);
    return __r;
}

template<class _Tp>
template<class _Alloc, class _A0, class _A1, class _A2>
shared_ptr_no_thread<_Tp>
shared_ptr_no_thread<_Tp>::allocate_shared(const _Alloc& __a, _A0& __a0, _A1& __a1, _A2& __a2)
{
    typedef __shared_ptr_no_thread_emplace<_Tp, _Alloc> _CntrlBlk;
    typedef typename __allocator_traits_rebind<_Alloc, _CntrlBlk>::type _Alloc2;
    typedef __allocator_destructor<_Alloc2> _D2;
    _Alloc2 __alloc2(__a);
    ::new(static_cast<void*>(_VSTD::addressof(*__hold2.get())))
        _CntrlBlk(__a, __a0, __a1, __a2);
    shared_ptr_no_thread<_Tp> __r;
    __r.__ptr_ = __hold2.get()->get();
    __r.__cntrl_ = _VSTD::addressof(*__hold2.release());
    __r.__enable_weak_this(__r.__ptr_, __r.__ptr_);
    return __r;
}

#endif  // _LIBCPP_HAS_NO_VARIADICS

template<class _Tp>
shared_ptr_no_thread<_Tp>::~shared_ptr_no_thread()
{
	if (__cntrl_)
		__cntrl_->__release_shared();
}

template<class _Tp>
inline
shared_ptr_no_thread<_Tp>&
shared_ptr_no_thread<_Tp>::operator=(const shared_ptr_no_thread& __r) noexcept
{
shared_ptr_no_thread(__r).swap(*this);
return *this;
}

template<class _Tp>
template<class _Yp>
inline
typename std::enable_if
		<
				std::is_convertible<_Yp*, typename shared_ptr_no_thread<_Tp>::element_type*>::value,
				shared_ptr_no_thread<_Tp>&
>::type
shared_ptr_no_thread<_Tp>::operator=(const shared_ptr_no_thread<_Yp>& __r) noexcept
{
shared_ptr_no_thread(__r).swap(*this);
return *this;
}

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
inline
shared_ptr_no_thread<_Tp>&
shared_ptr_no_thread<_Tp>::operator=(shared_ptr_no_thread&& __r) noexcept
{
shared_ptr_no_thread(_VSTD::move(__r)).swap(*this);
return *this;
}

template<class _Tp>
template<class _Yp>
inline
typename std::enable_if
		<
				std::is_convertible<_Yp*, typename shared_ptr_no_thread<_Tp>::element_type*>::value,
				shared_ptr_no_thread<_Tp>&
>::type
shared_ptr_no_thread<_Tp>::operator=(shared_ptr_no_thread<_Yp>&& __r)
{
	shared_ptr_no_thread(_VSTD::move(__r)).swap(*this);
	return *this;
}

#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

template<class _Tp>
inline
void
shared_ptr_no_thread<_Tp>::reset() noexcept
{
shared_ptr_no_thread().swap(*this);
}

template<class _Tp>
template<class _Yp>
inline
typename std::enable_if
		<
				std::is_convertible<_Yp*, typename shared_ptr_no_thread<_Tp>::element_type*>::value,
				void
		>::type
shared_ptr_no_thread<_Tp>::reset(_Yp* __p)
{
	shared_ptr_no_thread(__p).swap(*this);
}

template<class _Tp>
template<class _Yp, class _Dp>
inline
typename std::enable_if
		<
				std::is_convertible<_Yp*, typename shared_ptr_no_thread<_Tp>::element_type*>::value,
				void
		>::type
shared_ptr_no_thread<_Tp>::reset(_Yp* __p, _Dp __d)
{
	shared_ptr_no_thread(__p, __d).swap(*this);
}

template<class _Tp>
template<class _Yp, class _Dp, class _Alloc>
inline
typename std::enable_if
		<
				std::is_convertible<_Yp*, typename shared_ptr_no_thread<_Tp>::element_type*>::value,
				void
		>::type
shared_ptr_no_thread<_Tp>::reset(_Yp* __p, _Dp __d, _Alloc __a)
{
	shared_ptr_no_thread(__p, __d, __a).swap(*this);
}
