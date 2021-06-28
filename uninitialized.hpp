#ifndef UNINITIALIZED_HPP
#define UNINITIALIZED_HPP

#include <cstring>
#include "algorithm.hpp"
#include "construct.hpp"

namespace ft
{
	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, __true_type)
	{
		return copy(__first, __last, __result);
	}

	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, __false_type)
	{
		_ForwardIterator __cur = __result;
		try
		{
			for (; __first != __last; ++__first, ++__cur)
				_Construct(&*__cur, *__first);
			return __cur;
		}
		catch (...)
		{
			_Destroy(__result, __cur);
			throw;
		}
	}

	template <typename _InputIterator, typename _ForwardIterator>
	inline _ForwardIterator uninitialized_copy(_InputIterator __first, _InputIterator __last, _ForwardIterator __result)
	{
		typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
		typedef typename is_scalar<_ValueType>::__type _Is_POD;
		return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
	}

	inline char *uninitialized_copy(const char *__first, const char *__last, char *__result)
	{
		std::memmove(__result, __first, __last - __first);
		return __result + (__last - __first);
	}

	inline wchar_t *uninitialized_copy(const wchar_t *__first, const wchar_t *__last, wchar_t *__result)
	{
		std::memmove(__result, __first, sizeof(wchar_t) * (__last - __first));
		return __result + (__last - __first);
	}

	template <typename _ForwardIterator, typename _Tp>
	inline void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__x, __true_type)
	{
		fill(__first, __last, __x);
	}

	template <typename _ForwardIterator, typename _Tp>
	void
	__uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__x, __false_type)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __cur != __last; ++__cur)
				_Construct(&*__cur, __x);
		}
		catch (...)
		{
			_Destroy(__first, __cur);
			throw;
		}
	}

	template <typename _ForwardIterator, typename _Tp>
	inline void
	uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__x)
	{
		typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
		typedef typename is_scalar<_ValueType>::__type _Is_POD;
		__uninitialized_fill_aux(__first, __last, __x, _Is_POD());
	}

	template <typename _ForwardIterator, typename _Size, typename _Tp>
	inline void
	__uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp &__x, __true_type)
	{
		fill_n(__first, __n, __x);
	}

	template <typename _ForwardIterator, typename _Size, typename _Tp>
	void __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _Tp &__x, __false_type)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __n > 0; --__n, ++__cur)
				_Construct(&*__cur, __x);
		}
		catch (...)
		{
			_Destroy(__first, __cur);
			throw;
		}
	}

	template <typename _ForwardIterator, typename _Size, typename _Tp>
	inline void uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp &__x)
	{
		typedef typename iterator_traits<_ForwardIterator>::value_type _ValueType;
		typedef typename is_scalar<_ValueType>::__type _Is_POD;
		__uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
	}

	template <typename _InputIterator, typename _ForwardIterator, typename _Allocator>
	_ForwardIterator __uninitialized_copy_a(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _Allocator __alloc)
	{
		_ForwardIterator __cur = __result;
		try
		{
			for (; __first != __last; ++__first, ++__cur)
				__alloc.construct(&*__cur, *__first);
			return __cur;
		}
		catch (...)
		{
			ft::_Destroy(__result, __cur, __alloc);
			throw;
		}
	}

	template <typename _InputIterator, typename _ForwardIterator, typename _Tp>
	inline _ForwardIterator __uninitialized_copy_a(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, allocator<_Tp>)
	{
		return uninitialized_copy(__first, __last, __result);
	}

	template <typename _ForwardIterator, typename _Tp, typename _Allocator>
	void __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__x, _Allocator __alloc)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __cur != __last; ++__cur)
				__alloc.construct(&*__cur, __x);
		}
		catch (...)
		{
			_Destroy(__first, __cur, __alloc);
			throw;
		}
	}

	template <typename _ForwardIterator, typename _Tp, typename _Tp2>
	inline void __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__x, allocator<_Tp2>)
	{
		uninitialized_fill(__first, __last, __x);
	}

	template <typename _ForwardIterator, typename _Size, typename _Tp, typename _Allocator>
	void __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, const _Tp &__x, _Allocator __alloc)
	{
		_ForwardIterator __cur = __first;
		try
		{
			for (; __n > 0; --__n, ++__cur)
				__alloc.construct(&*__cur, __x);
		}
		catch (...)
		{
			ft::_Destroy(__first, __cur, __alloc);
			throw;
		}
	}

	template <typename _ForwardIterator, typename _Size, typename _Tp, typename _Tp2>
	void __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, const _Tp &__x, allocator<_Tp2>)
	{
		uninitialized_fill_n(__first, __n, __x);
	}

	template <typename _InputIterator1, typename _InputIterator2, typename _ForwardIterator, typename _Allocator>
	inline _ForwardIterator __uninitialized_copy_copy(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2, _ForwardIterator __result, _Allocator __alloc)
	{
		_ForwardIterator __mid = __uninitialized_copy_a(__first1, __last1, __result, __alloc);
		try
		{
			return __uninitialized_copy_a(__first2, __last2, __mid, __alloc);
		}
		catch (...)
		{
			_Destroy(__result, __mid, __alloc);
			throw;
		}
	}

	template <typename _ForwardIterator, typename _Tp, typename _InputIterator, typename _Allocator>
	inline _ForwardIterator __uninitialized_fill_copy(_ForwardIterator __result, _ForwardIterator __mid, const _Tp &__x, _InputIterator __first, _InputIterator __last, _Allocator __alloc)
	{
		__uninitialized_fill_a(__result, __mid, __x, __alloc);
		try
		{
			return __uninitialized_copy_a(__first, __last, __mid, __alloc);
		}
		catch (...)
		{
			_Destroy(__result, __mid, __alloc);
			throw;
		}
	}

	template <typename _InputIterator, typename _ForwardIterator, typename _Tp, typename _Allocator>
	inline void __uninitialized_copy_fill(_InputIterator __first1, _InputIterator __last1, _ForwardIterator __first2, _ForwardIterator __last2, const _Tp &__x, _Allocator __alloc)
	{
		_ForwardIterator __mid2 = __uninitialized_copy_a(__first1, __last1, __first2, __alloc);
		try
		{
			__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
		}
		catch (...)
		{
			_Destroy(__first2, __mid2, __alloc);
			throw;
		}
	}

}

#endif
