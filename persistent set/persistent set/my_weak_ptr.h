//
// Created by Vadim on 25/12/2017.
//

#ifndef PERSISTENT_SET_MY_WEAK_PTR_H
#define PERSISTENT_SET_MY_WEAK_PTR_H

template <typename T>
class my_weak_ptr {
private:
	T* ptr;
public:
	template <template<typename> class shared_ptr_t>
	my_weak_ptr(shared_ptr_t<T> const& sh_ptr) 
			: ptr(sh_ptr.get())
	{}
	my_weak_ptr(T* raw_ptr):
		ptr(raw_ptr)
	{}
	T* get() const {
		return ptr;
	}
};

#endif //PERSISTENT_SET_MY_WEAK_PTR_H
