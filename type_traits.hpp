#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{

	template <typename _Iterator, typename _Container>
	class __normal_iterator;
	struct __true_type
	{
	};
	struct __false_type
	{
	};

	template <bool>
	struct __truth_type
	{
		typedef __false_type __type;
	};

	template <>
	struct __truth_type<true>
	{
		typedef __true_type __type;
	};

	template <class _Sp, class _Tp>
	struct __traitor
	{
		enum
		{
			__value = _Sp::__value || _Tp::__value
		};
		typedef typename __truth_type<__value>::__type __type;
	};

	template <typename, typename>
	struct __are_same
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <typename _Tp>
	struct __are_same<_Tp, _Tp>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <typename, bool>
	struct __enable_if
	{
	};

	template <typename _Tp>
	struct __enable_if<_Tp, true>
	{
		typedef _Tp __type;
	};

	template <typename _Tp>
	struct __is_void
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <>
	struct __is_void<void>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	// Integer types

	template <typename _Tp>
	struct __is_integer
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <>
	struct __is_integer<bool>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<char>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<signed char>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned char>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<short>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned short>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<int>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned int>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<long>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned long>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<long long>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned long long>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	// Floating point types

	template <typename _Tp>
	struct __is_floating
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <>
	struct __is_floating<float>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_floating<double>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <>
	struct __is_floating<long double>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	// Pointer types

	template <typename _Tp>
	struct __is_pointer
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <typename _Tp>
	struct __is_pointer<_Tp *>
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	// Normal iterator type

	template <typename _Tp>
	struct __is_normal_iterator
	{
		enum
		{
			__value = 0
		};
		typedef __false_type __type;
	};

	template <typename _Iterator, typename _Container>
	struct __is_normal_iterator<__normal_iterator<_Iterator, _Container> >
	{
		enum
		{
			__value = 1
		};
		typedef __true_type __type;
	};

	template <typename _Tp>
	struct __is_arithmetic
		: public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >{};

	template <typename _Tp>
	struct __is_fundamental
		: public __traitor<__is_void<_Tp>, __is_arithmetic<_Tp> >{};

	template <typename _Tp>
	struct __is_scalar
		: public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >{};

	typedef char __one;
	typedef char __two[2];

	template <typename _Tp>
	__one __test_type(int _Tp::*);
	template <typename _Tp>
	__two &__test_type(...);

	template <typename _Tp>
	struct __is_pod
	{
		enum
		{
			__value = (sizeof(__test_type<_Tp>(0)) != sizeof(__one))
		};
	};
}

#endif
