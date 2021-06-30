#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{
	struct _List_node_base
	{
		_List_node_base *_M_next;
		_List_node_base *_M_prev;

		static void swap(_List_node_base &__x, _List_node_base &__y)
		{
			if (__x._M_next != &__x)
			{
				if (__y._M_next != &__y)
				{
					ft::swap(__x._M_next, __y._M_next);
					ft::swap(__x._M_prev, __y._M_prev);
					__x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
					__y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
				}
				else
				{
					__y._M_next = __x._M_next;
					__y._M_prev = __x._M_prev;
					__y._M_next->_M_prev = __y._M_prev->_M_next = &__y;
					__x._M_next = __x._M_prev = &__x;
				}
			}
			else if (__y._M_next != &__y)
			{
				__x._M_next = __y._M_next;
				__x._M_prev = __y._M_prev;
				__x._M_next->_M_prev = __x._M_prev->_M_next = &__x;
				__y._M_next = __y._M_prev = &__y;
			}
		}

		void transfer(_List_node_base *const __first, _List_node_base *const __last)
		{
			if (this != __last)
			{
				__last->_M_prev->_M_next = this;
				__first->_M_prev->_M_next = __last;
				this->_M_prev->_M_next = __first;

				_List_node_base *const __tmp = this->_M_prev;
				this->_M_prev = __last->_M_prev;
				__last->_M_prev = __first->_M_prev;
				__first->_M_prev = __tmp;
			}
		}

		void reverse()
		{
			_List_node_base *__tmp = this;
			do
			{
				ft::swap(__tmp->_M_next, __tmp->_M_prev);
				__tmp = __tmp->_M_prev;
			} while (__tmp != this);
		}

		void hook(_List_node_base *const __position)
		{
			this->_M_next = __position;
			this->_M_prev = __position->_M_prev;
			__position->_M_prev->_M_next = this;
			__position->_M_prev = this;
		}

		void unhook()
		{
			_List_node_base *const __next_node = this->_M_next;
			_List_node_base *const __prev_node = this->_M_prev;
			__prev_node->_M_next = __next_node;
			__next_node->_M_prev = __prev_node;
		}
	};

	template <typename _Tp>
	struct _List_node : public _List_node_base
	{
		_Tp _M_data;
	};

	template <typename _Tp>
	struct _List_iterator
	{
		typedef _List_iterator<_Tp> _Self;
		typedef _List_node<_Tp> _Node;

		typedef ptrdiff_t difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef _Tp *pointer;
		typedef _Tp &reference;

		_List_iterator() : _M_node() {}

		_List_iterator(_List_node_base *__x) : _M_node(__x) {}

		reference operator*() const
		{
			return static_cast<_Node *>(_M_node)->_M_data;
		}

		pointer operator->() const
		{
			return &static_cast<_Node *>(_M_node)->_M_data;
		}

		_Self &operator++()
		{
			_M_node = _M_node->_M_next;
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _M_node->_M_next;
			return __tmp;
		}

		_Self &operator--()
		{
			_M_node = _M_node->_M_prev;
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _M_node->_M_prev;
			return __tmp;
		}

		bool operator==(const _Self &__x) const
		{
			return _M_node == __x._M_node;
		}

		bool operator!=(const _Self &__x) const
		{
			return _M_node != __x._M_node;
		}

		_List_node_base *_M_node;
	};

	template <typename _Tp>
	struct _List_const_iterator
	{
		typedef _List_const_iterator<_Tp> _Self;
		typedef const _List_node<_Tp> _Node;
		typedef _List_iterator<_Tp> iterator;

		typedef ptrdiff_t difference_type;
		typedef bidirectional_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef const _Tp *pointer;
		typedef const _Tp &reference;

		_List_const_iterator() : _M_node() {}

		_List_const_iterator(const _List_node_base *__x) : _M_node(__x) {}

		_List_const_iterator(const iterator &__x) : _M_node(__x._M_node) {}
		reference operator*() const
		{
			return static_cast<_Node *>(_M_node)->_M_data;
		}

		pointer operator->() const
		{
			return &static_cast<_Node *>(_M_node)->_M_data;
		}

		_Self &operator++()
		{
			_M_node = _M_node->_M_next;
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _M_node->_M_next;
			return __tmp;
		}

		_Self &operator--()
		{
			_M_node = _M_node->_M_prev;
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _M_node->_M_prev;
			return __tmp;
		}

		bool operator==(const _Self &__x) const
		{
			return _M_node == __x._M_node;
		}

		bool operator!=(const _Self &__x) const
		{
			return _M_node != __x._M_node;
		}

		const _List_node_base *_M_node;
	};

	template <typename _Val>
	inline bool operator==(const _List_iterator<_Val> &__x,
						   const _List_const_iterator<_Val> &__y)
	{
		return __x._M_node == __y._M_node;
	}

	template <typename _Val>
	inline bool operator!=(const _List_iterator<_Val> &__x,
						   const _List_const_iterator<_Val> &__y)
	{
		return __x._M_node != __y._M_node;
	}

	template <typename _Tp, typename _Alloc>
	class _List_base
	{
	protected:
		typedef typename _Alloc::template rebind<_List_node<_Tp> >::other _Node_Alloc_type;

		struct _List_impl : public _Node_Alloc_type
		{
			_List_node_base _M_node;
			_List_impl(const _Node_Alloc_type &__a) : _Node_Alloc_type(__a) {}
		};

		_List_impl _M_impl;

		_List_node<_Tp> *_M_get_node()
		{
			return _M_impl._Node_Alloc_type::allocate(1);
		}

		void
		_M_put_node(_List_node<_Tp> *__p)
		{
			_M_impl._Node_Alloc_type::deallocate(__p, 1);
		}

	public:
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const
		{
			return allocator_type(*static_cast<const _Node_Alloc_type *>(&this->_M_impl));
		}

		_List_base(const allocator_type &__a) : _M_impl(__a)
		{
			_M_init();
		}

		~_List_base()
		{
			_M_clear();
		}

		void _M_clear()
		{
			typedef _List_node<_Tp> _Node;
			_Node *__cur = static_cast<_Node *>(this->_M_impl._M_node._M_next);
			while (__cur != &this->_M_impl._M_node)
			{
				_Node *__tmp = __cur;
				__cur = static_cast<_Node *>(__cur->_M_next);
				this->get_allocator().destroy(&__tmp->_M_data);
				_M_put_node(__tmp);
			}
		}

		void _M_init()
		{
			this->_M_impl._M_node._M_next = &this->_M_impl._M_node;
			this->_M_impl._M_node._M_prev = &this->_M_impl._M_node;
		}
	};

	template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
	class list : protected _List_base<_Tp, _Alloc>
	{
			typedef _List_base<_Tp, _Alloc> _Base;

	public:
		typedef _Tp value_type;
		typedef typename _Alloc::pointer pointer;
		typedef typename _Alloc::const_pointer const_pointer;
		typedef typename _Alloc::reference reference;
		typedef typename _Alloc::const_reference const_reference;
		typedef _List_iterator<_Tp> iterator;
		typedef _List_const_iterator<_Tp> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename _Base::allocator_type allocator_type;

	protected:
		typedef _List_node<_Tp> _Node;

		using _Base::_M_get_node;
		using _Base::_M_impl;
		using _Base::_M_put_node;

		_Node *_M_create_node(const value_type &__x)
		{
			_Node *__p = this->_M_get_node();
			try
			{
				this->get_allocator().construct(&__p->_M_data, __x);
			}
			catch (...)
			{
				_M_put_node(__p);
				throw;
			}
			return __p;
		}

	public:
		explicit list(const allocator_type &__a = allocator_type()) : _Base(__a) {}

		list(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type()) : _Base(__a)
		{
			this->insert(begin(), __n, __value);
		}

		explicit list(size_type __n) : _Base(allocator_type())
		{
			this->insert(begin(), __n, value_type());
		}

		list(const list &__x) : _Base(__x.get_allocator())
		{
			this->insert(begin(), __x.begin(), __x.end());
		}

		template <typename _InputIterator>
		list(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) : _Base(__a)
		{
			this->insert(begin(), __first, __last);
		}

		list &operator=(const list &__x)
		{
			if (this != &__x)
			{
				iterator __first1 = begin();
				iterator __last1 = end();
				const_iterator __first2 = __x.begin();
				const_iterator __last2 = __x.end();
				for (; __first1 != __last1 && __first2 != __last2;
					 ++__first1, ++__first2)
					*__first1 = *__first2;
				if (__first2 == __last2)
					erase(__first1, __last1);
				else
					insert(__last1, __first2, __last2);
			}
			return *this;
		}

		void assign(size_type __n, const value_type &__val)
		{
			_M_fill_assign(__n, __val);
		}

		template <typename _InputIterator>
		void assign(_InputIterator __first, _InputIterator __last)
		{
			typedef typename is_integer<_InputIterator>::__type _Integral;
			_M_assign_dispatch(__first, __last, _Integral());
		}

		allocator_type get_allocator() const
		{
			return _Base::get_allocator();
		}

		iterator begin()
		{
			return this->_M_impl._M_node._M_next;
		}

		const_iterator begin() const
		{
			return this->_M_impl._M_node._M_next;
		}

		iterator end()
		{
			return &this->_M_impl._M_node;
		}

		const_iterator end() const
		{
			return &this->_M_impl._M_node;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return this->_M_impl._M_node._M_next == &this->_M_impl._M_node;
		}

		size_type size() const
		{
			return ft::distance(begin(), end());
		}

		size_type max_size() const
		{
			return size_type(-1);
		}

		void resize(size_type __new_size, const value_type &__x)
		{
			iterator __i = begin();
			size_type __len = 0;
			for (; __i != end() && __len < __new_size; ++__i, ++__len)
				;
			if (__len == __new_size)
				erase(__i, end());
			else
				insert(end(), __new_size - __len, __x);
		}

		void resize(size_type __new_size)
		{
			this->resize(__new_size, value_type());
		}

		reference front()
		{
			return *begin();
		}

		const_reference front() const
		{
			return *begin();
		}

		reference back()
		{
			iterator __tmp = end();
			--__tmp;
			return *__tmp;
		}

		const_reference back() const
		{
			const_iterator __tmp = end();
			--__tmp;
			return *__tmp;
		}

		void push_front(const value_type &__x)
		{
			this->_M_insert(begin(), __x);
		}

		void pop_front()
		{
			this->_M_erase(begin());
		}

		void push_back(const value_type &__x)
		{
			this->_M_insert(end(), __x);
		}

		void pop_back()
		{
			this->_M_erase(this->_M_impl._M_node._M_prev);
		}

		iterator insert(iterator __position, const value_type &__x)
		{
			_Node *__tmp = _M_create_node(__x);
			__tmp->hook(__position._M_node);
			return __tmp;
		}

		void insert(iterator __position, size_type __n, const value_type &__x)
		{
			_M_fill_insert(__position, __n, __x);
		}

		template <typename _InputIterator>
		void insert(iterator __position, _InputIterator __first,
					_InputIterator __last)
		{
			typedef typename is_integer<_InputIterator>::__type _Integral;
			_M_insert_dispatch(__position, __first, __last, _Integral());
		}

		iterator erase(iterator __position)
		{
			iterator __ret = __position._M_node->_M_next;
			_M_erase(__position);
			return __ret;
		}

		iterator erase(iterator __first, iterator __last)
		{
			while (__first != __last)
				__first = erase(__first);
			return __last;
		}

		void swap(list &__x)
		{
			_List_node_base::swap(this->_M_impl._M_node, __x._M_impl._M_node);
		}

		void clear()
		{
			_Base::_M_clear();
			_Base::_M_init();
		}

		void splice(iterator __position, list &__x)
		{
			if (!__x.empty())
				this->_M_transfer(__position, __x.begin(), __x.end());
		}

		void splice(iterator __position, list &, iterator __i)
		{
			iterator __j = __i;
			++__j;
			if (__position == __i || __position == __j)
				return;
			this->_M_transfer(__position, __i, __j);
		}

		void splice(iterator __position, list &, iterator __first, iterator __last)
		{
			if (__first != __last)
				this->_M_transfer(__position, __first, __last);
		}

		void remove(const _Tp &__value)
		{
			iterator __first = begin();
			iterator __last = end();
			while (__first != __last)
			{
				iterator __next = __first;
				++__next;
				if (*__first == __value)
					_M_erase(__first);
				__first = __next;
			}
		}

		template <typename _Predicate>
		void remove_if(_Predicate __pred)
		{

			iterator __first = begin();
			iterator __last = end();
			while (__first != __last)
			{
				iterator __next = __first;
				++__next;
				if (__pred(*__first))
					_M_erase(__first);
				__first = __next;
			}
		}

		void unique()
		{
			iterator __first = begin();
			iterator __last = end();
			if (__first == __last)
				return;
			iterator __next = __first;
			while (++__next != __last)
			{
				if (*__first == *__next)
					_M_erase(__next);
				else
					__first = __next;
				__next = __first;
			}
		}

		template <typename _BinaryPredicate>
		void unique(_BinaryPredicate __binary_pred)
		{
			iterator __first = begin();
			iterator __last = end();
			if (__first == __last)
				return;
			iterator __next = __first;
			while (++__next != __last)
			{
				if (__binary_pred(*__first, *__next))
					_M_erase(__next);
				else
					__first = __next;
				__next = __first;
			}
		}

		void merge(list &__x)
		{
			if (this != &__x)
			{
				iterator __first1 = begin();
				iterator __last1 = end();
				iterator __first2 = __x.begin();
				iterator __last2 = __x.end();
				while (__first1 != __last1 && __first2 != __last2)
					if (*__first2 < *__first1)
					{
						iterator __next = __first2;
						_M_transfer(__first1, __first2, ++__next);
						__first2 = __next;
					}
					else
						++__first1;
				if (__first2 != __last2)
					_M_transfer(__last1, __first2, __last2);
			}
		}

		template <typename _StrictWeakOrdering>
		void merge(list &__x, _StrictWeakOrdering __comp)
		{
			if (this != &__x)
			{
				iterator __first1 = begin();
				iterator __last1 = end();
				iterator __first2 = __x.begin();
				iterator __last2 = __x.end();
				while (__first1 != __last1 && __first2 != __last2)
					if (__comp(*__first2, *__first1))
					{
						iterator __next = __first2;
						_M_transfer(__first1, __first2, ++__next);
						__first2 = __next;
					}
					else
						++__first1;
				if (__first2 != __last2)
					_M_transfer(__last1, __first2, __last2);
			}
		}

		void reverse()
		{
			this->_M_impl._M_node.reverse();
		}

		void sort()
		{
			if (this->_M_impl._M_node._M_next != &this->_M_impl._M_node && this->_M_impl._M_node._M_next->_M_next != &this->_M_impl._M_node)
			{
				list __carry;
				list __tmp[64];
				list *__fill = &__tmp[0];
				list *__counter;

				do
				{
					__carry.splice(__carry.begin(), *this, begin());

					for (__counter = &__tmp[0]; __counter != __fill && !__counter->empty(); ++__counter)
					{
						__counter->merge(__carry);
						__carry.swap(*__counter);
					}
					__carry.swap(*__counter);
					if (__counter == __fill)
						++__fill;
				} while (!empty());

				for (__counter = &__tmp[1]; __counter != __fill; ++__counter)
					__counter->merge(*(__counter - 1));
				swap(*(__fill - 1));
			}
		}

		template <typename _StrictWeakOrdering>
		void sort(_StrictWeakOrdering __comp)
		{
			if (this->_M_impl._M_node._M_next != &this->_M_impl._M_node && this->_M_impl._M_node._M_next->_M_next != &this->_M_impl._M_node)
			{
				list __carry;
				list __tmp[64];
				list *__fill = &__tmp[0];
				list *__counter;

				do
				{
					__carry.splice(__carry.begin(), *this, begin());

					for (__counter = &__tmp[0]; __counter != __fill && !__counter->empty(); ++__counter)
					{
						__counter->merge(__carry, __comp);
						__carry.swap(*__counter);
					}
					__carry.swap(*__counter);
					if (__counter == __fill)
						++__fill;
				} while (!empty());

				for (__counter = &__tmp[1]; __counter != __fill; ++__counter)
					__counter->merge(*(__counter - 1), __comp);
				swap(*(__fill - 1));
			}
		}

	protected:
		template <typename _Integer>
		void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
		{
			_M_fill_assign(static_cast<size_type>(__n), static_cast<value_type>(__val));
		}

		template <typename _InputIterator>
		void _M_assign_dispatch(_InputIterator __first2, _InputIterator __last2, __false_type)
		{
			iterator __first1 = begin();
			iterator __last1 = end();
			for (; __first1 != __last1 && __first2 != __last2;
				 ++__first1, ++__first2)
				*__first1 = *__first2;
			if (__first2 == __last2)
				erase(__first1, __last1);
			else
				insert(__last1, __first2, __last2);
		}

		void _M_fill_assign(size_type __n, const value_type &__val)
		{
			iterator __i = begin();
			for (; __i != end() && __n > 0; ++__i, --__n)
				*__i = __val;
			if (__n > 0)
				insert(end(), __n, __val);
			else
				erase(__i, end());
		}

		template <typename _Integer>
		void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x, __true_type)
		{
			_M_fill_insert(__pos, static_cast<size_type>(__n),
						   static_cast<value_type>(__x));
		}

		template <typename _InputIterator>
		void _M_insert_dispatch(iterator __pos, _InputIterator __first, _InputIterator __last, __false_type)
		{
			for (; __first != __last; ++__first)
				_M_insert(__pos, *__first);
		}

		void _M_fill_insert(iterator __pos, size_type __n, const value_type &__x)
		{
			for (; __n > 0; --__n)
				_M_insert(__pos, __x);
		}

		void _M_transfer(iterator __position, iterator __first, iterator __last)
		{
			__position._M_node->transfer(__first._M_node, __last._M_node);
		}

		void _M_insert(iterator __position, const value_type &__x)
		{
			_Node *__tmp = _M_create_node(__x);
			__tmp->hook(__position._M_node);
		}

		void _M_erase(iterator __position)
		{
			__position._M_node->unhook();
			_Node *__n = static_cast<_Node *>(__position._M_node);
			this->get_allocator().destroy(&__n->_M_data);
			_M_put_node(__n);
		}
	};

	template <typename _Tp, typename _Alloc>
	inline bool operator==(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
		const_iterator __end1 = __x.end();
		const_iterator __end2 = __y.end();

		const_iterator __i1 = __x.begin();
		const_iterator __i2 = __y.begin();
		while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2)
		{
			++__i1;
			++__i2;
		}
		return __i1 == __end1 && __i2 == __end2;
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator!=(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<=(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>=(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _Alloc>
	inline void swap(list<_Tp, _Alloc> &__x, list<_Tp, _Alloc> &__y)
	{
		__x.swap(__y);
	}
}

#endif
