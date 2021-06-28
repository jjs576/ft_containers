#ifndef CONSTRUCT_HPP
#define CONSTRUCT_HPP

#include "type_traits.hpp"

namespace ft
{

	template <typename _T1, typename _T2>
	inline void
	_Construct(_T1 *__p, const _T2 &__value)
	{
		::new (static_cast<void *>(__p)) _T1(__value);
	}

	template <typename _T1>
	inline void _Construct(_T1 *__p)
	{
		::new (static_cast<void *>(__p)) _T1();
	}

	template <typename _Tp>
	inline void
	_Destroy(_Tp *__pointer)
	{
		__pointer->~_Tp();
	}

	template <typename _ForwardIterator>
	inline void
	__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
	{
		for (; __first != __last; ++__first)
			ft::_Destroy(&*__first);
	}

	template <typename _ForwardIterator>
	inline void	__destroy_aux(_ForwardIterator, _ForwardIterator, __true_type)
	{
	}

	template <typename _ForwardIterator>
	inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
	{
		typedef typename iterator_traits<_ForwardIterator>::value_type _Value_type;
		typedef typename is_scalar<_Value_type>::__type _Has_trivial_destructor;

		ft::__destroy_aux(__first, __last, _Has_trivial_destructor());
	}

	template <typename _Tp>
	class allocator;

	template <typename _ForwardIterator, typename _Allocator>
	void _Destroy(_ForwardIterator __first, _ForwardIterator __last, _Allocator __alloc)
	{
		for (; __first != __last; ++__first)
			__alloc.destroy(&*__first);
	}

	template <typename _ForwardIterator, typename _Allocator, typename _Tp>
	inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last, allocator<_Tp>)
	{
		ft::_Destroy(__first, __last);
	}
}

#endif
