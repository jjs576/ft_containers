#ifndef HEAP_HPP
#define HEAP_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename _RandomAccessIterator, typename _Distance>
	bool __is_heap(_RandomAccessIterator __first, _Distance __n)
	{
		_Distance __parent = 0;
		for (_Distance __child = 1; __child < __n; ++__child)
		{
			if (__first[__parent] < __first[__child])
				return false;
			if ((__child & 1) == 0)
				++__parent;
		}
		return true;
	}

	template <typename _RandomAccessIterator, typename _Distance, typename _StrictWeakOrdering>
	bool __is_heap(_RandomAccessIterator __first, _StrictWeakOrdering __comp, _Distance __n)
	{
		_Distance __parent = 0;
		for (_Distance __child = 1; __child < __n; ++__child)
		{
			if (__comp(__first[__parent], __first[__child]))
				return false;
			if ((__child & 1) == 0)
				++__parent;
		}
		return true;
	}

	template <typename _RandomAccessIterator>
	bool __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
	{
		return __is_heap(__first, ft::distance(__first, __last));
	}

	template <typename _RandomAccessIterator, typename _StrictWeakOrdering>
	bool __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _StrictWeakOrdering __comp)
	{
		return __is_heap(__first, __comp, ft::distance(__first, __last));
	}

	template <typename _RandomAccessIterator, typename _Distance, typename _Tp>
	void __push_heap(_RandomAccessIterator __first, _Distance __holeIndex, _Distance __topIndex, _Tp __value)
	{
		_Distance __parent = (__holeIndex - 1) / 2;
		while (__holeIndex > __topIndex && *(__first + __parent) < __value)
		{
			*(__first + __holeIndex) = *(__first + __parent);
			__holeIndex = __parent;
			__parent = (__holeIndex - 1) / 2;
		}
		*(__first + __holeIndex) = __value;
	}

	template <typename _RandomAccessIterator>
	inline void
	push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::value_type _ValueType;
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type _DistanceType;

		__push_heap(__first, _DistanceType((__last - __first) - 1), _DistanceType(0), _ValueType(*(__last - 1)));
	}

	template <typename _RandomAccessIterator, typename _Distance, typename _Tp, typename _Compare>
	void
	__push_heap(_RandomAccessIterator __first, _Distance __holeIndex, _Distance __topIndex, _Tp __value, _Compare __comp)
	{
		_Distance __parent = (__holeIndex - 1) / 2;
		while (__holeIndex > __topIndex && __comp(*(__first + __parent), __value))
		{
			*(__first + __holeIndex) = *(__first + __parent);
			__holeIndex = __parent;
			__parent = (__holeIndex - 1) / 2;
		}
		*(__first + __holeIndex) = __value;
	}

	template <typename _RandomAccessIterator, typename _Compare>
	inline void
	push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::value_type _ValueType;
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type _DistanceType;

		__push_heap(__first, _DistanceType((__last - __first) - 1), _DistanceType(0), _ValueType(*(__last - 1)), __comp);
	}

	template <typename _RandomAccessIterator, typename _Distance, typename _Tp>
	void __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex, _Distance __len, _Tp __value)
	{
		const _Distance __topIndex = __holeIndex;
		_Distance __secondChild = 2 * __holeIndex + 2;
		while (__secondChild < __len)
		{
			if (*(__first + __secondChild) < *(__first + (__secondChild - 1)))
				__secondChild--;
			*(__first + __holeIndex) = *(__first + __secondChild);
			__holeIndex = __secondChild;
			__secondChild = 2 * (__secondChild + 1);
		}
		if (__secondChild == __len)
		{
			*(__first + __holeIndex) = *(__first + (__secondChild - 1));
			__holeIndex = __secondChild - 1;
		}
		__push_heap(__first, __holeIndex, __topIndex, __value);
	}

	template <typename _RandomAccessIterator, typename _Tp>
	inline void __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _RandomAccessIterator __result, _Tp __value)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type _Distance;
		*__result = *__first;
		__adjust_heap(__first, _Distance(0), _Distance(__last - __first), __value);
	}

	template <typename _RandomAccessIterator>
	inline void
	pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::value_type _ValueType;

		__pop_heap(__first, __last - 1, __last - 1, _ValueType(*(__last - 1)));
	}

	template <typename _RandomAccessIterator, typename _Distance, typename _Tp, typename _Compare>
	void __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex, _Distance __len, _Tp __value, _Compare __comp)
	{
		const _Distance __topIndex = __holeIndex;
		_Distance __secondChild = 2 * __holeIndex + 2;
		while (__secondChild < __len)
		{
			if (__comp(*(__first + __secondChild), *(__first + (__secondChild - 1))))
				__secondChild--;
			*(__first + __holeIndex) = *(__first + __secondChild);
			__holeIndex = __secondChild;
			__secondChild = 2 * (__secondChild + 1);
		}
		if (__secondChild == __len)
		{
			*(__first + __holeIndex) = *(__first + (__secondChild - 1));
			__holeIndex = __secondChild - 1;
		}
		__push_heap(__first, __holeIndex, __topIndex, __value, __comp);
	}

	template <typename _RandomAccessIterator, typename _Tp, typename _Compare>
	inline void __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _RandomAccessIterator __result, _Tp __value, _Compare __comp)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type _Distance;
		*__result = *__first;
		__adjust_heap(__first, _Distance(0), _Distance(__last - __first), __value, __comp);
	}

	template <typename _RandomAccessIterator, typename _Compare>
	inline void pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
	{

		typedef typename iterator_traits<_RandomAccessIterator>::value_type
			_ValueType;
		__pop_heap(__first, __last - 1, __last - 1, _ValueType(*(__last - 1)), __comp);
	}

	template <typename _RandomAccessIterator>
	void make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::value_type
			_ValueType;
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type
			_DistanceType;

		if (__last - __first < 2)
			return;

		const _DistanceType __len = __last - __first;
		_DistanceType __parent = (__len - 2) / 2;
		while (true)
		{
			__adjust_heap(__first, __parent, __len, _ValueType(*(__first + __parent)));
			if (__parent == 0)
				return;
			__parent--;
		}
	}

	template <typename _RandomAccessIterator, typename _Compare>
	inline void make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
	{
		typedef typename iterator_traits<_RandomAccessIterator>::value_type _ValueType;
		typedef typename iterator_traits<_RandomAccessIterator>::difference_type _DistanceType;

		if (__last - __first < 2)
			return;

		const _DistanceType __len = __last - __first;
		_DistanceType __parent = (__len - 2) / 2;
		while (true)
		{
			__adjust_heap(__first, __parent, __len, _ValueType(*(__first + __parent)), __comp);
			if (__parent == 0)
				return;
			__parent--;
		}
	}

	template <typename _RandomAccessIterator>
	void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
	{

		while (__last - __first > 1)
			ft::pop_heap(__first, __last--);
	}

	template <typename _RandomAccessIterator, typename _Compare>
	void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
	{
		while (__last - __first > 1)
			ft::pop_heap(__first, __last--, __comp);
	}

}

#endif
