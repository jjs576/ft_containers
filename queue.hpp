#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "vector.hpp"
#include "heap.hpp"
#include "deque.hpp"
#include "algorithm.hpp"
#include "functional.hpp"

namespace ft
{
	template <typename _Tp, typename _Sequence = deque<_Tp> >
	class queue;

	template <typename _Tp, typename _Seq>
	inline bool
	operator==(const queue<_Tp, _Seq> &, const queue<_Tp, _Seq> &);

	template <typename _Tp, typename _Seq>
	inline bool
	operator<(const queue<_Tp, _Seq> &, const queue<_Tp, _Seq> &);

	template <typename _Tp, typename _Sequence>
	class queue
	{
		typedef typename _Sequence::value_type _Sequence_value_type;

		template <typename _Tp1, typename _Seq1>
		friend bool
		operator==(const queue<_Tp1, _Seq1> &, const queue<_Tp1, _Seq1> &);

		template <typename _Tp1, typename _Seq1>
		friend bool
		operator<(const queue<_Tp1, _Seq1> &, const queue<_Tp1, _Seq1> &);

	public:
		typedef typename _Sequence::value_type value_type;
		typedef typename _Sequence::reference reference;
		typedef typename _Sequence::const_reference const_reference;
		typedef typename _Sequence::size_type size_type;
		typedef _Sequence container_type;

	protected:
		_Sequence c;

	public:
		explicit queue(const _Sequence &__c = _Sequence()) : c(__c) {}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		reference front()
		{
			return c.front();
		}

		const_reference front() const
		{
			return c.front();
		}

		reference back()
		{
			return c.back();
		}

		const_reference back() const
		{
			return c.back();
		}

		void push(const value_type &__x)
		{
			c.push_back(__x);
		}

		void pop()
		{
			c.pop_front();
		}
	};

	template <typename _Tp, typename _Sequence>
	inline bool operator==(const queue<_Tp, _Sequence> &__x, const queue<_Tp, _Sequence> &__y)
	{
		return __x.c == __y.c;
	}

	template <typename _Tp, typename _Sequence>
	inline bool operator<(const queue<_Tp, _Sequence> &__x, const queue<_Tp, _Sequence> &__y)
	{
		return __x.c < __y.c;
	}

	template <typename _Tp, typename _Sequence>
	inline bool operator!=(const queue<_Tp, _Sequence> &__x,
						const queue<_Tp, _Sequence> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Sequence>
	inline bool operator>(const queue<_Tp, _Sequence> &__x, const queue<_Tp, _Sequence> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Sequence>
	inline bool operator<=(const queue<_Tp, _Sequence> &__x,
						const queue<_Tp, _Sequence> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Sequence>
	inline bool operator>=(const queue<_Tp, _Sequence> &__x,
						const queue<_Tp, _Sequence> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _Sequence = vector<_Tp>, typename _Compare = less<typename _Sequence::value_type> >
	class priority_queue
	{
		typedef typename _Sequence::value_type _Sequence_value_type;

	public:
		typedef typename _Sequence::value_type value_type;
		typedef typename _Sequence::reference reference;
		typedef typename _Sequence::const_reference const_reference;
		typedef typename _Sequence::size_type size_type;
		typedef _Sequence container_type;

	protected:
		_Sequence c;
		_Compare comp;

	public:
		explicit priority_queue(const _Compare &__x = _Compare(), const _Sequence &__s = _Sequence()) : c(__s), comp(__x)
		{
			make_heap(c.begin(), c.end(), comp);
		}

		template <typename _InputIterator>
		priority_queue(_InputIterator __first, _InputIterator __last, const _Compare &__x = _Compare(), const _Sequence &__s = _Sequence()) : c(__s), comp(__x)
		{
			c.insert(c.end(), __first, __last);
			make_heap(c.begin(), c.end(), comp);
		}

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		const_reference top() const
		{
			return c.front();
		}
		void push(const value_type &__x)
		{
			try
			{
				c.push_back(__x);
				push_heap(c.begin(), c.end(), comp);
			}
			catch (...)
			{
				c.clear();
				throw;
			}
		}

		void
		pop()
		{
			try
			{
				pop_heap(c.begin(), c.end(), comp);
				c.pop_back();
			}
			catch (...)
			{
				c.clear();
				throw;
			}
		}
	};
}

#endif
