#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>
#include <cstddef>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "construct.hpp"
#include "uninitialized.hpp"

namespace ft
{
	inline size_t __deque_buf_size(size_t __size)
	{
		return __size < 512 ? size_t(512 / __size) : size_t(1);
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	struct _Deque_iterator
	{
		typedef _Deque_iterator<_Tp, _Tp &, _Tp *> iterator;
		typedef _Deque_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;

		static size_t _S_buffer_size()
		{
			return __deque_buf_size(sizeof(_Tp));
		}

		typedef random_access_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef _Ptr pointer;
		typedef _Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _Tp **_Map_pointer;
		typedef _Deque_iterator _Self;

		_Tp *_M_cur;
		_Tp *_M_first;
		_Tp *_M_last;
		_Map_pointer _M_node;

		_Deque_iterator(_Tp *__x, _Map_pointer __y) : _M_cur(__x), _M_first(*__y), _M_last(*__y + _S_buffer_size()), _M_node(__y) {}

		_Deque_iterator() : _M_cur(0), _M_first(0), _M_last(0), _M_node(0) {}

		_Deque_iterator(const iterator &__x) : _M_cur(__x._M_cur), _M_first(__x._M_first), _M_last(__x._M_last), _M_node(__x._M_node) {}

		reference operator*() const
		{
			return *_M_cur;
		}

		pointer operator->() const
		{
			return _M_cur;
		}

		_Self &operator++()
		{
			++_M_cur;
			if (_M_cur == _M_last)
			{
				_M_set_node(_M_node + 1);
				_M_cur = _M_first;
			}
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			++*this;
			return __tmp;
		}

		_Self &operator--()
		{
			if (_M_cur == _M_first)
			{
				_M_set_node(_M_node - 1);
				_M_cur = _M_last;
			}
			--_M_cur;
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			--*this;
			return __tmp;
		}

		_Self &operator+=(difference_type __n)
		{
			const difference_type __offset = __n + (_M_cur - _M_first);
			if (__offset >= 0 && __offset < difference_type(_S_buffer_size()))
				_M_cur += __n;
			else
			{
				const difference_type __node_offset = __offset > 0 ? __offset / difference_type(_S_buffer_size()) : -difference_type((-__offset - 1) / _S_buffer_size()) - 1;
				_M_set_node(_M_node + __node_offset);
				_M_cur = _M_first + (__offset - __node_offset * difference_type(_S_buffer_size()));
			}
			return *this;
		}

		_Self operator+(difference_type __n) const
		{
			_Self __tmp = *this;
			return __tmp += __n;
		}

		_Self &operator-=(difference_type __n)
		{
			return *this += -__n;
		}

		_Self operator-(difference_type __n) const
		{
			_Self __tmp = *this;
			return __tmp -= __n;
		}

		reference operator[](difference_type __n) const
		{
			return *(*this + __n);
		}

		void _M_set_node(_Map_pointer __new_node)
		{
			_M_node = __new_node;
			_M_first = *__new_node;
			_M_last = _M_first + difference_type(_S_buffer_size());
		}
	};

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator==(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return __x._M_cur == __y._M_cur;
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator==(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return __x._M_cur == __y._M_cur;
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator!=(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator!=(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator<(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return (__x._M_node == __y._M_node) ? (__x._M_cur < __y._M_cur) : (__x._M_node < __y._M_node);
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator<(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return (__x._M_node == __y._M_node) ? (__x._M_cur < __y._M_cur) : (__x._M_node < __y._M_node);
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator>(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator>(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator<=(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _RefL, typename _PtrL,
			  typename _RefR, typename _PtrR>
	inline bool operator<=(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline bool operator>=(const _Deque_iterator<_Tp, _Ref, _Ptr> &__x, const _Deque_iterator<_Tp, _Ref, _Ptr> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline bool operator>=(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
	inline typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
	operator-(const _Deque_iterator<_Tp, _RefL, _PtrL> &__x, const _Deque_iterator<_Tp, _RefR, _PtrR> &__y)
	{
		return typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type(_Deque_iterator<_Tp, _RefL, _PtrL>::_S_buffer_size()) * (__x._M_node - __y._M_node - 1) + (__x._M_cur - __x._M_first) + (__y._M_last - __y._M_cur);
	}

	template <typename _Tp, typename _Ref, typename _Ptr>
	inline _Deque_iterator<_Tp, _Ref, _Ptr> operator+(ptrdiff_t __n, const _Deque_iterator<_Tp, _Ref, _Ptr> &__x)
	{
		return __x + __n;
	}

	template <typename _Tp, typename _Alloc>
	class _Deque_base
	{
	public:
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const
		{
			return *static_cast<const _Alloc *>(&this->_M_impl);
		}

		typedef _Deque_iterator<_Tp, _Tp &, _Tp *> iterator;
		typedef _Deque_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;

		_Deque_base(const allocator_type &__a, size_t __num_elements) : _M_impl(__a)
		{
			_M_initialize_map(__num_elements);
		}

		_Deque_base(const allocator_type &__a) : _M_impl(__a)
		{
		}

		~_Deque_base();

	protected:
		struct _Deque_impl : public _Alloc
		{
			_Tp **_M_map;
			size_t _M_map_size;
			iterator _M_start;
			iterator _M_finish;

			_Deque_impl(const _Alloc &__a) : _Alloc(__a), _M_map(0), _M_map_size(0), _M_start(), _M_finish()
			{
			}
		};

		typedef typename _Alloc::template rebind<_Tp *>::other _Map_alloc_type;
		_Map_alloc_type _M_get_map_allocator() const
		{
			return _Map_alloc_type(this->get_allocator());
		}

		_Tp *_M_allocate_node()
		{
			return _M_impl._Alloc::allocate(__deque_buf_size(sizeof(_Tp)));
		}

		void _M_deallocate_node(_Tp *__p)
		{
			_M_impl._Alloc::deallocate(__p, __deque_buf_size(sizeof(_Tp)));
		}

		_Tp **_M_allocate_map(size_t __n)
		{
			return _M_get_map_allocator().allocate(__n);
		}

		void _M_deallocate_map(_Tp **__p, size_t __n)
		{
			_M_get_map_allocator().deallocate(__p, __n);
		}

	protected:
		void _M_initialize_map(size_t);
		void _M_create_nodes(_Tp **__nstart, _Tp **__nfinish);
		void _M_destroy_nodes(_Tp **__nstart, _Tp **__nfinish);
		enum
		{
			_S_initial_map_size = 8
		};

		_Deque_impl _M_impl;
	};

	template <typename _Tp, typename _Alloc>
	_Deque_base<_Tp, _Alloc>::~_Deque_base()
	{
		if (this->_M_impl._M_map)
		{
			_M_destroy_nodes(this->_M_impl._M_start._M_node, this->_M_impl._M_finish._M_node + 1);
			_M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
		}
	}

	template <typename _Tp, typename _Alloc>
	void _Deque_base<_Tp, _Alloc>::_M_initialize_map(size_t __num_elements)
	{
		const size_t __num_nodes = (__num_elements / __deque_buf_size(sizeof(_Tp)) + 1);

		this->_M_impl._M_map_size = max((size_t)_S_initial_map_size, size_t(__num_nodes + 2));
		this->_M_impl._M_map = _M_allocate_map(this->_M_impl._M_map_size);

		_Tp **__nstart = (this->_M_impl._M_map + (this->_M_impl._M_map_size - __num_nodes) / 2);
		_Tp **__nfinish = __nstart + __num_nodes;

		try
		{
			_M_create_nodes(__nstart, __nfinish);
		}
		catch (...)
		{
			_M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
			this->_M_impl._M_map = 0;
			this->_M_impl._M_map_size = 0;
			__throw_exception_again;
		}

		this->_M_impl._M_start._M_set_node(__nstart);
		this->_M_impl._M_finish._M_set_node(__nfinish - 1);
		this->_M_impl._M_start._M_cur = _M_impl._M_start._M_first;
		this->_M_impl._M_finish._M_cur = (this->_M_impl._M_finish._M_first + __num_elements % __deque_buf_size(sizeof(_Tp)));
	}

	template <typename _Tp, typename _Alloc>
	void _Deque_base<_Tp, _Alloc>::_M_create_nodes(_Tp **__nstart, _Tp **__nfinish)
	{
		_Tp **__cur;
		try
		{
			for (__cur = __nstart; __cur < __nfinish; ++__cur)
				*__cur = this->_M_allocate_node();
		}
		catch (...)
		{
			_M_destroy_nodes(__nstart, __cur);
			__throw_exception_again;
		}
	}

	template <typename _Tp, typename _Alloc>
	void _Deque_base<_Tp, _Alloc>::
		_M_destroy_nodes(_Tp **__nstart, _Tp **__nfinish)
	{
		for (_Tp **__n = __nstart; __n < __nfinish; ++__n)
			_M_deallocate_node(*__n);
	}

	template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
	class deque : protected _Deque_base<_Tp, _Alloc>
	{

		typedef _Deque_base<_Tp, _Alloc> _Base;

	public:
		typedef _Tp value_type;
		typedef typename _Alloc::pointer pointer;
		typedef typename _Alloc::const_pointer const_pointer;
		typedef typename _Alloc::reference reference;
		typedef typename _Alloc::const_reference const_reference;
		typedef typename _Base::iterator iterator;
		typedef typename _Base::const_iterator const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename _Base::allocator_type allocator_type;

	protected:
		typedef pointer *_Map_pointer;

		static size_t _S_buffer_size()
		{
			return __deque_buf_size(sizeof(_Tp));
		}

		using _Base::_M_allocate_map;
		using _Base::_M_allocate_node;
		using _Base::_M_create_nodes;
		using _Base::_M_deallocate_map;
		using _Base::_M_deallocate_node;
		using _Base::_M_destroy_nodes;
		using _Base::_M_initialize_map;

		using _Base::_M_impl;

	public:
		explicit deque(const allocator_type &__a = allocator_type()) : _Base(__a, 0) {}

		deque(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type()) : _Base(__a, __n)
		{
			_M_fill_initialize(__value);
		}

		explicit deque(size_type __n) : _Base(allocator_type(), __n)
		{
			_M_fill_initialize(value_type());
		}

		deque(const deque &__x) : _Base(__x.get_allocator(), __x.size())
		{
			ft::__uninitialized_copy_a(__x.begin(), __x.end(), this->_M_impl._M_start, this->get_allocator());
		}

		template <typename _InputIterator>
		deque(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) : _Base(__a)
		{
			typedef typename __is_integer<_InputIterator>::__type _Integral;
			_M_initialize_dispatch(__first, __last, _Integral());
		}

		~deque()
		{
			ft::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
					 this->get_allocator());
		}

		deque &operator=(const deque &__x)
		{
			const size_type __len = size();
			if (&__x != this)
			{
				if (__len >= __x.size())
					erase(copy(__x.begin(), __x.end(), this->_M_impl._M_start),
						  this->_M_impl._M_finish);
				else
				{
					const_iterator __mid = __x.begin() + difference_type(__len);
					copy(__x.begin(), __mid, this->_M_impl._M_start);
					insert(this->_M_impl._M_finish, __mid, __x.end());
				}
			}
			return *this;
		}

		void
		assign(size_type __n, const value_type &__val)
		{
			_M_fill_assign(__n, __val);
		}

		template <typename _InputIterator>
		void
		assign(_InputIterator __first, _InputIterator __last)
		{
			typedef typename __is_integer<_InputIterator>::__type _Integral;
			_M_assign_dispatch(__first, __last, _Integral());
		}

		allocator_type get_allocator() const
		{
			return _Base::get_allocator();
		}

		iterator begin()
		{
			return this->_M_impl._M_start;
		}

		const_iterator begin() const
		{
			return this->_M_impl._M_start;
		}

		iterator end()
		{
			return this->_M_impl._M_finish;
		}

		const_iterator end() const
		{
			return this->_M_impl._M_finish;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->_M_impl._M_finish);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->_M_impl._M_finish);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this->_M_impl._M_start);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this->_M_impl._M_start);
		}

		size_type size() const
		{
			return this->_M_impl._M_finish - this->_M_impl._M_start;
		}

		size_type max_size() const
		{
			return size_type(-1);
		}

		void resize(size_type __new_size, const value_type &__x)
		{
			const size_type __len = size();
			if (__new_size < __len)
				erase(this->_M_impl._M_start + __new_size, this->_M_impl._M_finish);
			else
				insert(this->_M_impl._M_finish, __new_size - __len, __x);
		}

		void resize(size_type new_size)
		{
			resize(new_size, value_type());
		}

		bool empty() const
		{
			return this->_M_impl._M_finish == this->_M_impl._M_start;
		}

		reference operator[](size_type __n)
		{
			return this->_M_impl._M_start[difference_type(__n)];
		}

		const_reference operator[](size_type __n) const
		{
			return this->_M_impl._M_start[difference_type(__n)];
		}

	protected:
		void _M_range_check(size_type __n) const
		{
			if (__n >= this->size())
				std::__throw_out_of_range(__N("deque::_M_range_check"));
		}

	public:
		reference at(size_type __n)
		{
			_M_range_check(__n);
			return (*this)[__n];
		}

		const_reference at(size_type __n) const
		{
			_M_range_check(__n);
			return (*this)[__n];
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

		void
		push_front(const value_type &__x)
		{
			if (this->_M_impl._M_start._M_cur != this->_M_impl._M_start._M_first)
			{
				this->_M_impl.construct(this->_M_impl._M_start._M_cur - 1, __x);
				--this->_M_impl._M_start._M_cur;
			}
			else
				_M_push_front_aux(__x);
		}

		void push_back(const value_type &__x)
		{
			if (this->_M_impl._M_finish._M_cur != this->_M_impl._M_finish._M_last - 1)
			{
				this->_M_impl.construct(this->_M_impl._M_finish._M_cur, __x);
				++this->_M_impl._M_finish._M_cur;
			}
			else
				_M_push_back_aux(__x);
		}

		void pop_front()
		{
			if (this->_M_impl._M_start._M_cur != this->_M_impl._M_start._M_last - 1)
			{
				this->_M_impl.destroy(this->_M_impl._M_start._M_cur);
				++this->_M_impl._M_start._M_cur;
			}
			else
				_M_pop_front_aux();
		}

		void pop_back()
		{
			if (this->_M_impl._M_finish._M_cur != this->_M_impl._M_finish._M_first)
			{
				--this->_M_impl._M_finish._M_cur;
				this->_M_impl.destroy(this->_M_impl._M_finish._M_cur);
			}
			else
				_M_pop_back_aux();
		}

		iterator insert(iterator position, const value_type &__x)
		{
			if (position._M_cur == this->_M_impl._M_start._M_cur)
			{
				push_front(__x);
				return this->_M_impl._M_start;
			}
			else if (position._M_cur == this->_M_impl._M_finish._M_cur)
			{
				push_back(__x);
				iterator __tmp = this->_M_impl._M_finish;
				--__tmp;
				return __tmp;
			}
			else
				return _M_insert_aux(position, __x);
		}

		void insert(iterator __position, size_type __n, const value_type &__x)
		{
			_M_fill_insert(__position, __n, __x);
		}

		template <typename _InputIterator>
		void insert(iterator __position, _InputIterator __first, _InputIterator __last)
		{
			typedef typename __is_integer<_InputIterator>::__type _Integral;
			_M_insert_dispatch(__position, __first, __last, _Integral());
		}

		iterator erase(iterator __position)
		{
			iterator __next = __position;
			++__next;
			const size_type __index = __position - this->_M_impl._M_start;
			if (__index < (size() >> 1))
			{
				copy_backward(this->_M_impl._M_start, __position, __next);
				pop_front();
			}
			else
			{
				copy(__next, this->_M_impl._M_finish, __position);
				pop_back();
			}
			return this->_M_impl._M_start + __index;
		}

		iterator erase(iterator __first, iterator __last)
		{
			if (__first == this->_M_impl._M_start && __last == this->_M_impl._M_finish)
			{
				clear();
				return this->_M_impl._M_finish;
			}
			else
			{
				const difference_type __n = __last - __first;
				const difference_type __elems_before = (__first - this->_M_impl._M_start);
				if (static_cast<size_type>(__elems_before) < (size() - __n) / 2)
				{
					copy_backward(this->_M_impl._M_start, __first, __last);
					iterator __new_start = this->_M_impl._M_start + __n;
					_Destroy(this->_M_impl._M_start, __new_start, this->get_allocator());
					_M_destroy_nodes(this->_M_impl._M_start._M_node, __new_start._M_node);
					this->_M_impl._M_start = __new_start;
				}
				else
				{
					copy(__last, this->_M_impl._M_finish, __first);
					iterator __new_finish = this->_M_impl._M_finish - __n;
					_Destroy(__new_finish, this->_M_impl._M_finish, this->get_allocator());
					_M_destroy_nodes(__new_finish._M_node + 1, this->_M_impl._M_finish._M_node + 1);
					this->_M_impl._M_finish = __new_finish;
				}
				return this->_M_impl._M_start + __elems_before;
			}
		}

		void swap(deque &__x)
		{
			ft::swap(this->_M_impl._M_start, __x._M_impl._M_start);
			ft::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
			ft::swap(this->_M_impl._M_map, __x._M_impl._M_map);
			ft::swap(this->_M_impl._M_map_size, __x._M_impl._M_map_size);
		}

		void clear()
		{
			for (_Map_pointer __node = this->_M_impl._M_start._M_node + 1;
				 __node < this->_M_impl._M_finish._M_node;
				 ++__node)
			{
				_Destroy(*__node, *__node + _S_buffer_size(), this->get_allocator());
				_M_deallocate_node(*__node);
			}

			if (this->_M_impl._M_start._M_node != this->_M_impl._M_finish._M_node)
			{
				_Destroy(this->_M_impl._M_start._M_cur, this->_M_impl._M_start._M_last, this->get_allocator());
				_Destroy(this->_M_impl._M_finish._M_first, this->_M_impl._M_finish._M_cur, this->get_allocator());
				_M_deallocate_node(this->_M_impl._M_finish._M_first);
			}
			else
				_Destroy(this->_M_impl._M_start._M_cur, this->_M_impl._M_finish._M_cur, this->get_allocator());

			this->_M_impl._M_finish = this->_M_impl._M_start;
		}

	protected:
		template <typename _Integer>
		void _M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
		{
			_M_initialize_map(__n);
			_M_fill_initialize(__x);
		}

		template <typename _InputIterator>
		void
		_M_initialize_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
		{
			typedef typename iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_initialize(__first, __last, _IterCategory());
		}

		template <typename _InputIterator>
		void _M_range_initialize(_InputIterator __first, _InputIterator __last, input_iterator_tag)
		{
			this->_M_initialize_map(0);
			try
			{
				for (; __first != __last; ++__first)
					push_back(*__first);
			}
			catch (...)
			{
				clear();
				__throw_exception_again;
			}
		}

		template <typename _ForwardIterator>
		void _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
		{
			const size_type __n = distance(__first, __last);
			this->_M_initialize_map(__n);

			_Map_pointer __cur_node;
			try
			{
				for (__cur_node = this->_M_impl._M_start._M_node; __cur_node < this->_M_impl._M_finish._M_node; ++__cur_node)
				{
					_ForwardIterator __mid = __first;
					advance(__mid, _S_buffer_size());
					__uninitialized_copy_a(__first, __mid, *__cur_node, this->get_allocator());
					__first = __mid;
				}
				__uninitialized_copy_a(__first, __last, this->_M_impl._M_finish._M_first, this->get_allocator());
			}
			catch (...)
			{
				_Destroy(this->_M_impl._M_start, iterator(*__cur_node, __cur_node), this->get_allocator());
				__throw_exception_again;
			}
		}

		void _M_fill_initialize(const value_type &__value)
		{
			_Map_pointer __cur;
			try
			{
				for (__cur = this->_M_impl._M_start._M_node; __cur < this->_M_impl._M_finish._M_node; ++__cur)
					__uninitialized_fill_a(*__cur, *__cur + _S_buffer_size(), __value, this->get_allocator());
				__uninitialized_fill_a(this->_M_impl._M_finish._M_first, this->_M_impl._M_finish._M_cur, __value, this->get_allocator());
			}
			catch (...)
			{
				_Destroy(this->_M_impl._M_start, iterator(*__cur, __cur), this->get_allocator());
				__throw_exception_again;
			}
		}

		template <typename _Integer>
		void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
		{
			_M_fill_assign(static_cast<size_type>(__n), static_cast<value_type>(__val));
		}

		template <typename _InputIterator>
		void _M_assign_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
		{
			typedef typename iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_assign_aux(__first, __last, _IterCategory());
		}

		template <typename _InputIterator>
		void _M_assign_aux(_InputIterator __first, _InputIterator __last, input_iterator_tag)
		{
			iterator __cur = begin();
			for (; __first != __last && __cur != end(); ++__cur, ++__first)
				*__cur = *__first;
			if (__first == __last)
				erase(__cur, end());
			else
				insert(end(), __first, __last);
		}

		template <typename _ForwardIterator>
		void _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
		{
			const size_type __len = distance(__first, __last);
			if (__len > size())
			{
				_ForwardIterator __mid = __first;
				advance(__mid, size());
				copy(__first, __mid, begin());
				insert(end(), __mid, __last);
			}
			else
				erase(copy(__first, __last, begin()), end());
		}

		void _M_fill_assign(size_type __n, const value_type &__val)
		{
			if (__n > size())
			{
				fill(begin(), end(), __val);
				insert(end(), __n - size(), __val);
			}
			else
			{
				erase(begin() + __n, end());
				fill(begin(), end(), __val);
			}
		}

		void _M_push_back_aux(const value_type &__t)
		{
			value_type __t_copy = __t;
			_M_reserve_map_at_back();
			*(this->_M_impl._M_finish._M_node + 1) = this->_M_allocate_node();
			try
			{
				this->_M_impl.construct(this->_M_impl._M_finish._M_cur, __t_copy);
				this->_M_impl._M_finish._M_set_node(this->_M_impl._M_finish._M_node + 1);
				this->_M_impl._M_finish._M_cur = this->_M_impl._M_finish._M_first;
			}
			catch (...)
			{
				_M_deallocate_node(*(this->_M_impl._M_finish._M_node + 1));
				__throw_exception_again;
			}
		}
		void _M_push_front_aux(const value_type &__t)
		{
			value_type __t_copy = __t;
			_M_reserve_map_at_front();
			*(this->_M_impl._M_start._M_node - 1) = this->_M_allocate_node();
			try
			{
				this->_M_impl._M_start._M_set_node(this->_M_impl._M_start._M_node - 1);
				this->_M_impl._M_start._M_cur = this->_M_impl._M_start._M_last - 1;
				this->_M_impl.construct(this->_M_impl._M_start._M_cur, __t_copy);
			}
			catch (...)
			{
				++this->_M_impl._M_start;
				_M_deallocate_node(*(this->_M_impl._M_start._M_node - 1));
				__throw_exception_again;
			}
		}
		void _M_pop_back_aux()
		{
			_M_deallocate_node(this->_M_impl._M_finish._M_first);
			this->_M_impl._M_finish._M_set_node(this->_M_impl._M_finish._M_node - 1);
			this->_M_impl._M_finish._M_cur = this->_M_impl._M_finish._M_last - 1;
			this->_M_impl.destroy(this->_M_impl._M_finish._M_cur);
		}
		void _M_pop_front_aux()
		{

			this->_M_impl.destroy(this->_M_impl._M_start._M_cur);
			_M_deallocate_node(this->_M_impl._M_start._M_first);
			this->_M_impl._M_start._M_set_node(this->_M_impl._M_start._M_node + 1);
			this->_M_impl._M_start._M_cur = this->_M_impl._M_start._M_first;
		}

		template <typename _Integer>
		void
		_M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x, __true_type)
		{
			_M_fill_insert(__pos, static_cast<size_type>(__n), static_cast<value_type>(__x));
		}

		template <typename _InputIterator>
		void
		_M_insert_dispatch(iterator __pos, _InputIterator __first, _InputIterator __last, __false_type)
		{
			typedef typename iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_insert_aux(__pos, __first, __last, _IterCategory());
		}
		template <typename _InputIterator>
		void _M_range_insert_aux(iterator __pos, _InputIterator __first, _InputIterator __last, input_iterator_tag)
		{
			copy(__first, __last, inserter(*this, __pos));
		}

		template <typename _ForwardIterator>
		void _M_range_insert_aux(iterator __pos, _ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
		{
			const size_type __n = distance(__first, __last);
			if (__pos._M_cur == this->_M_impl._M_start._M_cur)
			{
				iterator __new_start = _M_reserve_elements_at_front(__n);
				try
				{
					__uninitialized_copy_a(__first, __last, __new_start,
										   this->get_allocator());
					this->_M_impl._M_start = __new_start;
				}
				catch (...)
				{
					_M_destroy_nodes(__new_start._M_node,
									 this->_M_impl._M_start._M_node);
					__throw_exception_again;
				}
			}
			else if (__pos._M_cur == this->_M_impl._M_finish._M_cur)
			{
				iterator __new_finish = _M_reserve_elements_at_back(__n);
				try
				{
					__uninitialized_copy_a(__first, __last, this->_M_impl._M_finish, this->get_allocator());
					this->_M_impl._M_finish = __new_finish;
				}
				catch (...)
				{
					_M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
									 __new_finish._M_node + 1);
					__throw_exception_again;
				}
			}
			else
				_M_insert_aux(__pos, __first, __last, __n);
		}

		void _M_fill_insert(iterator __pos, size_type __n, const value_type &__x)
		{
			if (__pos._M_cur == this->_M_impl._M_start._M_cur)
			{
				iterator __new_start = _M_reserve_elements_at_front(__n);
				try
				{
					__uninitialized_fill_a(__new_start, this->_M_impl._M_start,
										   __x,
										   this->get_allocator());
					this->_M_impl._M_start = __new_start;
				}
				catch (...)
				{
					_M_destroy_nodes(__new_start._M_node,
									 this->_M_impl._M_start._M_node);
					__throw_exception_again;
				}
			}
			else if (__pos._M_cur == this->_M_impl._M_finish._M_cur)
			{
				iterator __new_finish = _M_reserve_elements_at_back(__n);
				try
				{
					__uninitialized_fill_a(this->_M_impl._M_finish,
										   __new_finish, __x,
										   this->get_allocator());
					this->_M_impl._M_finish = __new_finish;
				}
				catch (...)
				{
					_M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
									 __new_finish._M_node + 1);
					__throw_exception_again;
				}
			}
			else
				_M_insert_aux(__pos, __n, __x);
		}

		iterator _M_insert_aux(iterator __pos, const value_type &__x)
		{
			difference_type __index = __pos - this->_M_impl._M_start;
			value_type __x_copy = __x;
			if (static_cast<size_type>(__index) < size() / 2)
			{
				push_front(front());
				iterator __front1 = this->_M_impl._M_start;
				++__front1;
				iterator __front2 = __front1;
				++__front2;
				__pos = this->_M_impl._M_start + __index;
				iterator __pos1 = __pos;
				++__pos1;
				copy(__front2, __pos1, __front1);
			}
			else
			{
				push_back(back());
				iterator __back1 = this->_M_impl._M_finish;
				--__back1;
				iterator __back2 = __back1;
				--__back2;
				__pos = this->_M_impl._M_start + __index;
				copy_backward(__pos, __back2, __back1);
			}
			*__pos = __x_copy;
			return __pos;
		}

		void _M_insert_aux(iterator __pos, size_type __n, const value_type &__x)
		{
			const difference_type __elems_before = __pos - this->_M_impl._M_start;
			const size_type __length = this->size();
			value_type __x_copy = __x;
			if (__elems_before < difference_type(__length / 2))
			{
				iterator __new_start = _M_reserve_elements_at_front(__n);
				iterator __old_start = this->_M_impl._M_start;
				__pos = this->_M_impl._M_start + __elems_before;
				try
				{
					if (__elems_before >= difference_type(__n))
					{
						iterator __start_n = (this->_M_impl._M_start + difference_type(__n));
						__uninitialized_copy_a(this->_M_impl._M_start, __start_n, __new_start, this->get_allocator());
						this->_M_impl._M_start = __new_start;
						copy(__start_n, __pos, __old_start);
						fill(__pos - difference_type(__n), __pos, __x_copy);
					}
					else
					{
						__uninitialized_copy_fill(this->_M_impl._M_start, __pos, __new_start, this->_M_impl._M_start, __x_copy, this->get_allocator());
						this->_M_impl._M_start = __new_start;
						fill(__old_start, __pos, __x_copy);
					}
				}
				catch (...)
				{
					_M_destroy_nodes(__new_start._M_node, this->_M_impl._M_start._M_node);
					__throw_exception_again;
				}
			}
			else
			{
				iterator __new_finish = _M_reserve_elements_at_back(__n);
				iterator __old_finish = this->_M_impl._M_finish;
				const difference_type __elems_after = difference_type(__length) - __elems_before;
				__pos = this->_M_impl._M_finish - __elems_after;
				try
				{
					if (__elems_after > difference_type(__n))
					{
						iterator __finish_n = (this->_M_impl._M_finish - difference_type(__n));
						__uninitialized_copy_a(__finish_n, this->_M_impl._M_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish = __new_finish;
						copy_backward(__pos, __finish_n, __old_finish);
						fill(__pos, __pos + difference_type(__n), __x_copy);
					}
					else
					{
						__uninitialized_fill_copy(this->_M_impl._M_finish, __pos + difference_type(__n), __x_copy, __pos, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish = __new_finish;
						fill(__pos, __old_finish, __x_copy);
					}
				}
				catch (...)
				{
					_M_destroy_nodes(this->_M_impl._M_finish._M_node + 1, __new_finish._M_node + 1);
					__throw_exception_again;
				}
			}
		}

		template <typename _ForwardIterator>
		void
		_M_insert_aux(iterator __pos, _ForwardIterator __first, _ForwardIterator __last, size_type __n)
		{
			const difference_type __elemsbefore = __pos - this->_M_impl._M_start;
			const size_type __length = size();
			if (static_cast<size_type>(__elemsbefore) < __length / 2)
			{
				iterator __new_start = _M_reserve_elements_at_front(__n);
				iterator __old_start = this->_M_impl._M_start;
				__pos = this->_M_impl._M_start + __elemsbefore;
				try
				{
					if (__elemsbefore >= difference_type(__n))
					{
						iterator __start_n = (this->_M_impl._M_start + difference_type(__n));
						__uninitialized_copy_a(this->_M_impl._M_start, __start_n, __new_start, this->get_allocator());
						this->_M_impl._M_start = __new_start;
						copy(__start_n, __pos, __old_start);
						copy(__first, __last, __pos - difference_type(__n));
					}
					else
					{
						_ForwardIterator __mid = __first;
						advance(__mid, difference_type(__n) - __elemsbefore);
						__uninitialized_copy_copy(this->_M_impl._M_start, __pos, __first, __mid, __new_start, this->get_allocator());
						this->_M_impl._M_start = __new_start;
						copy(__mid, __last, __old_start);
					}
				}
				catch (...)
				{
					_M_destroy_nodes(__new_start._M_node, this->_M_impl._M_start._M_node);
					__throw_exception_again;
				}
			}
			else
			{
				iterator __new_finish = _M_reserve_elements_at_back(__n);
				iterator __old_finish = this->_M_impl._M_finish;
				const difference_type __elemsafter = difference_type(__length) - __elemsbefore;
				__pos = this->_M_impl._M_finish - __elemsafter;
				try
				{
					if (__elemsafter > difference_type(__n))
					{
						iterator __finish_n = (this->_M_impl._M_finish - difference_type(__n));
						__uninitialized_copy_a(__finish_n, this->_M_impl._M_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish = __new_finish;
						copy_backward(__pos, __finish_n, __old_finish);
						copy(__first, __last, __pos);
					}
					else
					{
						_ForwardIterator __mid = __first;
						advance(__mid, __elemsafter);
						__uninitialized_copy_copy(__mid, __last, __pos, this->_M_impl._M_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish = __new_finish;
						copy(__first, __mid, __pos);
					}
				}
				catch (...)
				{
					_M_destroy_nodes(this->_M_impl._M_finish._M_node + 1, __new_finish._M_node + 1);
					__throw_exception_again;
				}
			}
		}

		iterator _M_reserve_elements_at_front(size_type __n)
		{
			const size_type __vacancies = this->_M_impl._M_start._M_cur - this->_M_impl._M_start._M_first;
			if (__n > __vacancies)
				_M_new_elements_at_front(__n - __vacancies);
			return this->_M_impl._M_start - difference_type(__n);
		}

		iterator _M_reserve_elements_at_back(size_type __n)
		{
			const size_type __vacancies = (this->_M_impl._M_finish._M_last - this->_M_impl._M_finish._M_cur) - 1;
			if (__n > __vacancies)
				_M_new_elements_at_back(__n - __vacancies);
			return this->_M_impl._M_finish + difference_type(__n);
		}

		void _M_new_elements_at_front(size_type __new_elems)
		{
			const size_type __new_nodes = (__new_elems + _S_buffer_size() - 1) / _S_buffer_size();
			_M_reserve_map_at_front(__new_nodes);
			size_type __i;
			try
			{
				for (__i = 1; __i <= __new_nodes; ++__i)
					*(this->_M_impl._M_start._M_node - __i) = this->_M_allocate_node();
			}
			catch (...)
			{
				for (size_type __j = 1; __j < __i; ++__j)
					_M_deallocate_node(*(this->_M_impl._M_start._M_node - __j));
				__throw_exception_again;
			}
		}

		void _M_new_elements_at_back(size_type __new_elems)
		{
			const size_type __new_nodes = (__new_elems + _S_buffer_size() - 1) / _S_buffer_size();
			_M_reserve_map_at_back(__new_nodes);
			size_type __i;
			try
			{
				for (__i = 1; __i <= __new_nodes; ++__i)
					*(this->_M_impl._M_finish._M_node + __i) = this->_M_allocate_node();
			}
			catch (...)
			{
				for (size_type __j = 1; __j < __i; ++__j)
					_M_deallocate_node(*(this->_M_impl._M_finish._M_node + __j));
				__throw_exception_again;
			}
		}
		void _M_reserve_map_at_back(size_type __nodes_to_add = 1)
		{
			if (__nodes_to_add + 1 > this->_M_impl._M_map_size - (this->_M_impl._M_finish._M_node - this->_M_impl._M_map))
				_M_reallocate_map(__nodes_to_add, false);
		}

		void _M_reserve_map_at_front(size_type __nodes_to_add = 1)
		{
			if (__nodes_to_add > size_type(this->_M_impl._M_start._M_node - this->_M_impl._M_map))
				_M_reallocate_map(__nodes_to_add, true);
		}

		void _M_reallocate_map(size_type __nodes_to_add, bool __add_at_front)
		{
			const size_type __old_num_nodes = this->_M_impl._M_finish._M_node - this->_M_impl._M_start._M_node + 1;
			const size_type __new_num_nodes = __old_num_nodes + __nodes_to_add;

			_Map_pointer __new_nstart;
			if (this->_M_impl._M_map_size > 2 * __new_num_nodes)
			{
				__new_nstart = this->_M_impl._M_map + (this->_M_impl._M_map_size - __new_num_nodes) / 2 + (__add_at_front ? __nodes_to_add : 0);
				if (__new_nstart < this->_M_impl._M_start._M_node)
					copy(this->_M_impl._M_start._M_node, this->_M_impl._M_finish._M_node + 1, __new_nstart);
				else
					copy_backward(this->_M_impl._M_start._M_node, this->_M_impl._M_finish._M_node + 1, __new_nstart + __old_num_nodes);
			}
			else
			{
				size_type __new_map_size = this->_M_impl._M_map_size + max(this->_M_impl._M_map_size, __nodes_to_add) + 2;

				_Map_pointer __new_map = this->_M_allocate_map(__new_map_size);
				__new_nstart = __new_map + (__new_map_size - __new_num_nodes) / 2 + (__add_at_front ? __nodes_to_add : 0);
				copy(this->_M_impl._M_start._M_node, this->_M_impl._M_finish._M_node + 1, __new_nstart);
				_M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);

				this->_M_impl._M_map = __new_map;
				this->_M_impl._M_map_size = __new_map_size;
			}

			this->_M_impl._M_start._M_set_node(__new_nstart);
			this->_M_impl._M_finish._M_set_node(__new_nstart + __old_num_nodes - 1);
		}
	};

	template <typename _Tp, typename _Alloc>
	inline bool operator==(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return __x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin());
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator!=(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<=(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>=(const deque<_Tp, _Alloc> &__x, const deque<_Tp, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _Alloc>
	inline void swap(deque<_Tp, _Alloc> &__x, deque<_Tp, _Alloc> &__y)
	{
		__x.swap(__y);
	}
}

#endif
