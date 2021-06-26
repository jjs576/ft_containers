#ifndef STACK_HPP
#define STACK_HPP

#include "deque.hpp"

namespace ft
{
	template <typename _Tp, typename _Sequence = deque<_Tp> >
	class stack;

	template <typename _Tp, typename _Seq>
	inline bool operator==(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y);

	template <typename _Tp, typename _Seq>
	inline bool operator<(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y);

	template <typename _Tp, typename _Sequence>
	class stack
	{
		typedef typename _Sequence::value_type _Sequence_value_type;

		template <typename _Tp1, typename _Seq1>
		friend bool
		operator==(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);

		template <typename _Tp1, typename _Seq1>
		friend bool
		operator<(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);

	public:
		typedef typename _Sequence::value_type value_type;
		typedef typename _Sequence::reference reference;
		typedef typename _Sequence::const_reference const_reference;
		typedef typename _Sequence::size_type size_type;
		typedef _Sequence container_type;

	protected:
		_Sequence c;

	public:
		explicit stack(const _Sequence &__c = _Sequence()) : c(__c) {}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		reference top()
		{
			return c.back();
		}
		const_reference top() const
		{
			return c.back();
		}

		void push(const value_type &__x)
		{
			c.push_back(__x);
		}

		void pop()
		{
			c.pop_back();
		}
	};

	template <typename _Tp, typename _Seq>
	inline bool operator==(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __x.c == __y.c;
	}

	template <typename _Tp, typename _Seq>
	inline bool operator<(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __x.c < __y.c;
	}

	template <typename _Tp, typename _Seq>
	inline bool operator!=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Seq>
	inline bool operator>(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Seq>
	inline bool operator<=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Seq>
	inline bool operator>=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__x < __y);
	}
}

#endif
