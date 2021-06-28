#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <cstring>

namespace ft
{

	template <typename _Tp>
	inline void
	swap(_Tp &__a, _Tp &__b)
	{
		const _Tp __tmp = __a;
		__a = __b;
		__b = __tmp;
	}

	template <bool _BoolType>
	struct __iter_swap
	{
		template <typename _ForwardIterator1, typename _ForwardIterator2>
		static void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
		{
			typedef typename iterator_traits<_ForwardIterator1>::value_type _ValueType1;
			const _ValueType1 __tmp = *__a;
			*__a = *__b;
			*__b = __tmp;
		}
	};

	template <>
	struct __iter_swap<true>
	{
		template <typename _ForwardIterator1, typename _ForwardIterator2>
		static void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
		{
			swap(*__a, *__b);
		}
	};

	template <typename _ForwardIterator1, typename _ForwardIterator2>
	inline void iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
	{
		typedef typename iterator_traits<_ForwardIterator1>::value_type _ValueType1;
		typedef typename iterator_traits<_ForwardIterator2>::value_type _ValueType2;

		typedef typename iterator_traits<_ForwardIterator1>::reference _ReferenceType1;
		typedef typename iterator_traits<_ForwardIterator2>::reference _ReferenceType2;
		__iter_swap<__are_same<_ValueType1, _ValueType2>::__value && __are_same<_ValueType1 &, _ReferenceType1>::__value && __are_same<_ValueType2 &, _ReferenceType2>::__value>::iter_swap(__a, __b);
	}

#undef min
#undef max

	template <typename _Tp>
	inline const _Tp &min(const _Tp &__a, const _Tp &__b)
	{
		if (__b < __a)
			return __b;
		return __a;
	}

	template <typename _Tp>
	inline const _Tp &max(const _Tp &__a, const _Tp &__b)
	{
		if (__a < __b)
			return __b;
		return __a;
	}

	template <typename _Tp, typename _Compare>
	inline const _Tp &min(const _Tp &__a, const _Tp &__b, _Compare __comp)
	{
		if (__comp(__b, __a))
			return __b;
		return __a;
	}

	template <typename _Tp, typename _Compare>
	inline const _Tp &max(const _Tp &__a, const _Tp &__b, _Compare __comp)
	{
		if (__comp(__a, __b))
			return __b;
		return __a;
	}

	template <bool, typename>
	struct __copy
	{
		template <typename _II, typename _OI>
		static _OI
		copy(_II __first, _II __last, _OI __result)
		{
			for (; __first != __last; ++__result, ++__first)
				*__result = *__first;
			return __result;
		}
	};

	template <bool _BoolType>
	struct __copy<_BoolType, random_access_iterator_tag>
	{
		template <typename _II, typename _OI>
		static _OI
		copy(_II __first, _II __last, _OI __result)
		{
			typedef typename iterator_traits<_II>::difference_type _Distance;
			for (_Distance __n = __last - __first; __n > 0; --__n)
			{
				*__result = *__first;
				++__first;
				++__result;
			}
			return __result;
		}
	};

	template <>
	struct __copy<true, random_access_iterator_tag>
	{
		template <typename _Tp>
		static _Tp *
		copy(const _Tp *__first, const _Tp *__last, _Tp *__result)
		{
			std::memmove(__result, __first, sizeof(_Tp) * (__last - __first));
			return __result + (__last - __first);
		}
	};

	template <typename _II, typename _OI>
	inline _OI __copy_aux(_II __first, _II __last, _OI __result)
	{
		typedef typename iterator_traits<_II>::value_type _ValueTypeI;
		typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
		typedef typename iterator_traits<_II>::iterator_category _Category;
		const bool __simple = (is_scalar<_ValueTypeI>::__value && is_pointer<_II>::__value && is_pointer<_OI>::__value && __are_same<_ValueTypeI, _ValueTypeO>::__value);

		return __copy<__simple, _Category>::copy(__first, __last, __result);
	}

	template <bool, bool>
	struct __copy_normal
	{
		template <typename _II, typename _OI>
		static _OI copy_n(_II __first, _II __last, _OI __result)
		{
			return __copy_aux(__first, __last, __result);
		}
	};

	template <>
	struct __copy_normal<true, false>
	{
		template <typename _II, typename _OI>
		static _OI copy_n(_II __first, _II __last, _OI __result)
		{
			return __copy_aux(__first.base(), __last.base(), __result);
		}
	};

	template <>
	struct __copy_normal<false, true>
	{
		template <typename _II, typename _OI>
		static _OI copy_n(_II __first, _II __last, _OI __result)
		{
			return _OI(__copy_aux(__first, __last, __result.base()));
		}
	};

	template <>
	struct __copy_normal<true, true>
	{
		template <typename _II, typename _OI>
		static _OI copy_n(_II __first, _II __last, _OI __result)
		{
			return _OI(__copy_aux(__first.base(), __last.base(),
								  __result.base()));
		}
	};

	template <typename _InputIterator, typename _OutputIterator>
	inline _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result)
	{
		const bool __in = is_normal_iterator<_InputIterator>::__value;
		const bool __out = is_normal_iterator<_OutputIterator>::__value;
		return __copy_normal<__in, __out>::copy_n(__first, __last,
												  __result);
	}

	template <bool, typename>
	struct __copy_backward
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			while (__first != __last)
				*--__result = *--__last;
			return __result;
		}
	};

	template <bool _BoolType>
	struct __copy_backward<_BoolType, random_access_iterator_tag>
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			typename iterator_traits<_BI1>::difference_type __n;
			for (__n = __last - __first; __n > 0; --__n)
				*--__result = *--__last;
			return __result;
		}
	};

	template <>
	struct __copy_backward<true, random_access_iterator_tag>
	{
		template <typename _Tp>
		static _Tp *copy_b(const _Tp *__first, const _Tp *__last, _Tp *__result)
		{
			const ptrdiff_t _Num = __last - __first;
			std::memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
			return __result - _Num;
		}
	};

	template <typename _BI1, typename _BI2>
	inline _BI2 __copy_backward_aux(_BI1 __first, _BI1 __last, _BI2 __result)
	{
		typedef typename iterator_traits<_BI1>::value_type _ValueType1;
		typedef typename iterator_traits<_BI2>::value_type _ValueType2;
		typedef typename iterator_traits<_BI1>::iterator_category _Category;
		const bool __simple = (is_scalar<_ValueType1>::__value && is_pointer<_BI1>::__value && is_pointer<_BI2>::__value && __are_same<_ValueType1, _ValueType2>::__value);

		return __copy_backward<__simple, _Category>::copy_b(__first, __last, __result);
	}

	template <bool, bool>
	struct __copy_backward_normal
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b_n(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			return __copy_backward_aux(__first, __last, __result);
		}
	};

	template <>
	struct __copy_backward_normal<true, false>
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b_n(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			return __copy_backward_aux(__first.base(), __last.base(), __result);
		}
	};

	template <>
	struct __copy_backward_normal<false, true>
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b_n(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			return _BI2(__copy_backward_aux(__first, __last, __result.base()));
		}
	};

	template <>
	struct __copy_backward_normal<true, true>
	{
		template <typename _BI1, typename _BI2>
		static _BI2 copy_b_n(_BI1 __first, _BI1 __last, _BI2 __result)
		{
			return _BI2(__copy_backward_aux(__first.base(), __last.base(), __result.base()));
		}
	};

	template <typename _BI1, typename _BI2>
	inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
	{
		const bool __bi1 = is_normal_iterator<_BI1>::__value;
		const bool __bi2 = is_normal_iterator<_BI2>::__value;
		return __copy_backward_normal<__bi1, __bi2>::copy_b_n(__first, __last, __result);
	}

	template <bool>
	struct __fill
	{
		template <typename _ForwardIterator, typename _Tp>
		static void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__value)
		{
			for (; __first != __last; ++__first)
				*__first = __value;
		}
	};

	template <>
	struct __fill<true>
	{
		template <typename _ForwardIterator, typename _Tp>
		static void fill(_ForwardIterator __first, _ForwardIterator __last,
						 const _Tp &__value)
		{
			const _Tp __tmp = __value;
			for (; __first != __last; ++__first)
				*__first = __tmp;
		}
	};

	template <typename _ForwardIterator, typename _Tp>
	void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp &__value)
	{
		const bool __scalar = is_scalar<_Tp>::__value;
		__fill<__scalar>::fill(__first, __last, __value);
	}

	inline void fill(unsigned char *__first, unsigned char *__last, const unsigned char &__c)
	{
		const unsigned char __tmp = __c;
		std::memset(__first, __tmp, __last - __first);
	}

	inline void fill(signed char *__first, signed char *__last, const signed char &__c)
	{
		const signed char __tmp = __c;
		std::memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
	}

	inline void fill(char *__first, char *__last, const char &__c)
	{
		const char __tmp = __c;
		std::memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
	}

	template <bool>
	struct __fill_n
	{
		template <typename _OutputIterator, typename _Size, typename _Tp>
		static _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp &__value)
		{
			for (; __n > 0; --__n, ++__first)
				*__first = __value;
			return __first;
		}
	};

	template <>
	struct __fill_n<true>
	{
		template <typename _OutputIterator, typename _Size, typename _Tp>
		static _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp &__value)
		{
			const _Tp __tmp = __value;
			for (; __n > 0; --__n, ++__first)
				*__first = __tmp;
			return __first;
		}
	};

	template <typename _OutputIterator, typename _Size, typename _Tp>
	_OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp &__value)
	{
		const bool __scalar = is_scalar<_Tp>::__value;
		return __fill_n<__scalar>::fill_n(__first, __n, __value);
	}

	template <typename _Size>
	inline unsigned char *fill_n(unsigned char *__first, _Size __n, const unsigned char &__c)
	{
		fill(__first, __first + __n, __c);
		return __first + __n;
	}

	template <typename _Size>
	inline signed char *fill_n(char *__first, _Size __n, const signed char &__c)
	{
		fill(__first, __first + __n, __c);
		return __first + __n;
	}

	template <typename _Size>
	inline char *fill_n(char *__first, _Size __n, const char &__c)
	{
		fill(__first, __first + __n, __c);
		return __first + __n;
	}

	template <typename _InputIterator1, typename _InputIterator2>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
	{
		while (__first1 != __last1 && *__first1 == *__first2)
		{
			++__first1;
			++__first2;
		}
		return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
	}

	template <typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
	pair<_InputIterator1, _InputIterator2> mismatch(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __binary_pred)
	{
		while (__first1 != __last1 && __binary_pred(*__first1, *__first2))
		{
			++__first1;
			++__first2;
		}
		return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
	}

	template <typename _InputIterator1, typename _InputIterator2>
	inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
	{
		for (; __first1 != __last1; ++__first1, ++__first2)
			if (!(*__first1 == *__first2))
				return false;
		return true;
	}

	template <typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
	inline bool equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __binary_pred)
	{
		for (; __first1 != __last1; ++__first1, ++__first2)
			if (!__binary_pred(*__first1, *__first2))
				return false;
		return true;
	}

	template <typename _InputIterator1, typename _InputIterator2>
	bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
	{
		for (; __first1 != __last1 && __first2 != __last2;
			 ++__first1, ++__first2)
		{
			if (*__first1 < *__first2)
				return true;
			if (*__first2 < *__first1)
				return false;
		}
		return __first1 == __last1 && __first2 != __last2;
	}

	template <typename _InputIterator1, typename _InputIterator2, typename _Compare>
	bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
	{
		for (; __first1 != __last1 && __first2 != __last2;
			 ++__first1, ++__first2)
		{
			if (__comp(*__first1, *__first2))
				return true;
			if (__comp(*__first2, *__first1))
				return false;
		}
		return __first1 == __last1 && __first2 != __last2;
	}

	inline bool
	lexicographical_compare(const unsigned char *__first1, const unsigned char *__last1, const unsigned char *__first2, const unsigned char *__last2)
	{

		const size_t __len1 = __last1 - __first1;
		const size_t __len2 = __last2 - __first2;
		const int __result = std::memcmp(__first1, __first2, min(__len1, __len2));
		return __result != 0 ? __result < 0 : __len1 < __len2;
	}

	inline bool
	lexicographical_compare(const char *__first1, const char *__last1, const char *__first2, const char *__last2)
	{
		return lexicographical_compare((const signed char *)__first1, (const signed char *)__last1, (const signed char *)__first2, (const signed char *)__last2);
	}

}

#endif
