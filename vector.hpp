#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "uninitialized.hpp"

namespace ft
{
	template <typename _Tp, typename _Alloc>
	struct _Vector_base
	{
		struct _Vector_impl : public _Alloc
		{
			_Tp *_M_start;
			_Tp *_M_finish;
			_Tp *_M_end_of_storage;
			_Vector_impl(_Alloc const &__a) : _Alloc(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0)
			{
			}
		};

	public:
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const
		{
			return *static_cast<const _Alloc *>(&this->_M_impl);
		}

		_Vector_base(const allocator_type &__a) : _M_impl(__a) {}

		_Vector_base(size_t __n, const allocator_type &__a) : _M_impl(__a)
		{
			this->_M_impl._M_start = this->_M_allocate(__n);
			this->_M_impl._M_finish = this->_M_impl._M_start;
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
		}

		~_Vector_base()
		{
			_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
		}

	public:
		_Vector_impl _M_impl;

		_Tp *_M_allocate(size_t __n)
		{
			return _M_impl.allocate(__n);
		}

		void _M_deallocate(_Tp *__p, size_t __n)
		{
			if (__p)
				_M_impl.deallocate(__p, __n);
		}
	};

	template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
	class vector : protected _Vector_base<_Tp, _Alloc>
	{
		typedef _Vector_base<_Tp, _Alloc> _Base;
		typedef vector<_Tp, _Alloc> vector_type;

	public:
		typedef _Tp value_type;
		typedef typename _Alloc::pointer pointer;
		typedef typename _Alloc::const_pointer const_pointer;
		typedef typename _Alloc::reference reference;
		typedef typename _Alloc::const_reference const_reference;
		typedef __normal_iterator<pointer, vector_type> iterator;
		typedef __normal_iterator<const_pointer, vector_type> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename _Base::allocator_type allocator_type;

	protected:
		using _Base::_M_allocate;
		using _Base::_M_deallocate;
		using _Base::_M_impl;

	public:
		explicit vector(const allocator_type &__a = allocator_type()) : _Base(__a) {}

		vector(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type()) : _Base(__n, __a)
		{
			__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, this->get_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_start + __n;
		}

		explicit vector(size_type __n) : _Base(__n, allocator_type())
		{
			__uninitialized_fill_n_a(this->_M_impl._M_start, __n, value_type(), this->get_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_start + __n;
		}

		vector(const vector &__x) : _Base(__x.size(), __x.get_allocator())
		{
			this->_M_impl._M_finish = __uninitialized_copy_a(__x.begin(), __x.end(), this->_M_impl._M_start, this->get_allocator());
		}

		template <typename _InputIterator>
		vector(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) : _Base(__a)
		{
			typedef typename __is_integer<_InputIterator>::__type _Integral;
			_M_initialize_dispatch(__first, __last, _Integral());
		}

		~vector()
		{
			_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, this->get_allocator());
		}

		vector &operator=(const vector &__x)
		{
			if (&__x != this)
			{
				const size_type __xlen = __x.size();
				if (__xlen > capacity())
				{
					pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, this->get_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __tmp;
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
				}
				else if (size() >= __xlen)
				{
					iterator __i(copy(__x.begin(), __x.end(), begin()));
					_Destroy(__i, end(), this->get_allocator());
				}
				else
				{
					copy(__x.begin(), __x.begin() + size(),
							  this->_M_impl._M_start);
					__uninitialized_copy_a(__x.begin() + size(), __x.end(), this->_M_impl._M_finish, this->get_allocator());
				}
				this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
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
			typedef typename __is_integer<_InputIterator>::__type _Integral;
			_M_assign_dispatch(__first, __last, _Integral());
		}

		using _Base::get_allocator;

		iterator begin()
		{
			return iterator(this->_M_impl._M_start);
		}

		const_iterator begin() const
		{
			return const_iterator(this->_M_impl._M_start);
		}

		iterator end()
		{
			return iterator(this->_M_impl._M_finish);
		}

		const_iterator end() const
		{
			return const_iterator(this->_M_impl._M_finish);
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

		size_type size() const
		{
			return size_type(end() - begin());
		}

		size_type max_size() const
		{
			return size_type(-1) / sizeof(value_type);
		}

		void resize(size_type __new_size, const value_type &__x)
		{
			if (__new_size < size())
				erase(begin() + __new_size, end());
			else
				insert(end(), __new_size - size(), __x);
		}

		void resize(size_type __new_size)
		{
			resize(__new_size, value_type());
		}

		size_type capacity() const
		{
			return size_type(const_iterator(this->_M_impl._M_end_of_storage) - begin());
		}

		bool empty() const
		{
			return begin() == end();
		}

		void reserve(size_type __n)
		{
			if (__n > this->max_size())
				std::__throw_length_error(__N("vector::reserve"));
			if (this->capacity() < __n)
			{
				const size_type __old_size = size();
				pointer __tmp = _M_allocate_and_copy(__n, this->_M_impl._M_start, this->_M_impl._M_finish);
				_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
							  this->get_allocator());
				_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				this->_M_impl._M_start = __tmp;
				this->_M_impl._M_finish = __tmp + __old_size;
				this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
			}
		}

		reference operator[](size_type __n)
		{
			return *(begin() + __n);
		}

		const_reference operator[](size_type __n) const
		{
			return *(begin() + __n);
		}

	protected:
		void _M_range_check(size_type __n) const
		{
			if (__n >= this->size())
				std::__throw_out_of_range(__N("vector::_M_range_check"));
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
			return *(end() - 1);
		}

		const_reference back() const
		{
			return *(end() - 1);
		}

		void push_back(const value_type &__x)
		{
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
			{
				this->_M_impl.construct(this->_M_impl._M_finish, __x);
				++this->_M_impl._M_finish;
			}
			else
				_M_insert_aux(end(), __x);
		}

		void pop_back()
		{
			--this->_M_impl._M_finish;
			this->_M_impl.destroy(this->_M_impl._M_finish);
		}

		iterator insert(iterator __position, const value_type &__x)
		{
			const size_type __n = __position - begin();
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage && __position == end())
			{
				this->_M_impl.construct(this->_M_impl._M_finish, __x);
				++this->_M_impl._M_finish;
			}
			else
				_M_insert_aux(__position, __x);
			return begin() + __n;
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
			if (__position + 1 != end())
				copy(__position + 1, end(), __position);
			--this->_M_impl._M_finish;
			this->_M_impl.destroy(this->_M_impl._M_finish);
			return __position;
		}

		iterator erase(iterator __first, iterator __last)
		{
			iterator __i(copy(__last, end(), __first));
			_Destroy(__i, end(), this->get_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_finish - (__last - __first);
			return __first;
		}

		void swap(vector &__x)
		{
			swap(this->_M_impl._M_start, __x._M_impl._M_start);
			swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
			swap(this->_M_impl._M_end_of_storage, __x._M_impl._M_end_of_storage);
		}

		void clear()
		{
			erase(begin(), end());
		}

	protected:
		template <typename _ForwardIterator>
		pointer _M_allocate_and_copy(size_type __n, _ForwardIterator __first, _ForwardIterator __last)
		{
			pointer __result = this->_M_allocate(__n);
			try
			{
				__uninitialized_copy_a(__first, __last, __result, this->get_allocator());
				return __result;
			}
			catch (...)
			{
				_M_deallocate(__result, __n);
				__throw_exception_again;
			}
		}

		template <typename _Integer>
		void _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
		{
			this->_M_impl._M_start = _M_allocate(__n);
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
			__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, this->get_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
		}

		template <typename _InputIterator>
		void _M_initialize_dispatch(_InputIterator __first, _InputIterator __last, __false_type)
		{
			typedef typename iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_initialize(__first, __last, _IterCategory());
		}

		template <typename _InputIterator>
		void _M_range_initialize(_InputIterator __first, _InputIterator __last, input_iterator_tag)
		{
			for (; __first != __last; ++__first)
				push_back(*__first);
		}

		template <typename _ForwardIterator>
		void _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
		{
			const size_type __n = distance(__first, __last);
			this->_M_impl._M_start = this->_M_allocate(__n);
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
			this->_M_impl._M_finish = __uninitialized_copy_a(__first, __last, this->_M_impl._M_start, this->get_allocator());
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
			iterator __cur(begin());
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

			if (__len > capacity())
			{
				pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
				_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, this->get_allocator());
				_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				this->_M_impl._M_start = __tmp;
				this->_M_impl._M_finish = this->_M_impl._M_start + __len;
				this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
			}
			else if (size() >= __len)
			{
				iterator __new_finish(copy(__first, __last, this->_M_impl._M_start));
				_Destroy(__new_finish, end(), this->get_allocator());
				this->_M_impl._M_finish = __new_finish.base();
			}
			else
			{
				_ForwardIterator __mid = __first;
				advance(__mid, size());
				copy(__first, __mid, this->_M_impl._M_start);
				this->_M_impl._M_finish = __uninitialized_copy_a(__mid, __last, this->_M_impl._M_finish, this->get_allocator());
			}
		}

		void _M_fill_assign(size_type __n, const value_type &__val)
		{
			if (__n > capacity())
			{
				vector __tmp(__n, __val, get_allocator());
				__tmp.swap(*this);
			}
			else if (__n > size())
			{
				fill(begin(), end(), __val);
				__uninitialized_fill_n_a(this->_M_impl._M_finish, __n - size(), __val, this->get_allocator());
				this->_M_impl._M_finish += __n - size();
			}
			else
				erase(fill_n(begin(), __n, __val), end());
		}

		template <typename _Integer>
		void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val, __true_type)
		{
			_M_fill_insert(__pos, static_cast<size_type>(__n), static_cast<value_type>(__val));
		}

		template <typename _InputIterator>
		void _M_insert_dispatch(iterator __pos, _InputIterator __first, _InputIterator __last, __false_type)
		{
			typedef typename iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_insert(__pos, __first, __last, _IterCategory());
		}

		template <typename _InputIterator>
		void _M_range_insert(iterator __pos, _InputIterator __first, _InputIterator __last, input_iterator_tag)
		{
			for (; __first != __last; ++__first)
			{
				__pos = insert(__pos, *__first);
				++__pos;
			}
		}

		template <typename _ForwardIterator>
		void _M_range_insert(iterator __position, _ForwardIterator __first, _ForwardIterator __last, forward_iterator_tag)
		{
			if (__first != __last)
			{
				const size_type __n = distance(__first, __last);
				if (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_finish) >= __n)
				{
					const size_type __elems_after = end() - __position;
					iterator __old_finish(this->_M_impl._M_finish);
					if (__elems_after > __n)
					{
						__uninitialized_copy_a(this->_M_impl._M_finish - __n, this->_M_impl._M_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish += __n;
						copy_backward(__position, __old_finish - __n, __old_finish);
						copy(__first, __last, __position);
					}
					else
					{
						_ForwardIterator __mid = __first;
						advance(__mid, __elems_after);
						__uninitialized_copy_a(__mid, __last, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish += __n - __elems_after;
						__uninitialized_copy_a(__position, __old_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish += __elems_after;
						copy(__first, __mid, __position);
					}
				}
				else
				{
					const size_type __old_size = size();
					if (this->max_size() - __old_size < __n)
						std::__throw_length_error(__N("vector::_M_range_insert"));

					size_type __len = __old_size + max(__old_size, __n);
					if (__len < __old_size)
						__len = this->max_size();

					iterator __new_start(this->_M_allocate(__len));
					iterator __new_finish(__new_start);
					try
					{
						__new_finish = __uninitialized_copy_a(iterator(this->_M_impl._M_start), __position, __new_start, this->get_allocator());
						__new_finish = __uninitialized_copy_a(__first, __last, __new_finish, this->get_allocator());
						__new_finish = __uninitialized_copy_a(__position, iterator(this->_M_impl._M_finish), __new_finish, this->get_allocator());
					}
					catch (...)
					{
						_Destroy(__new_start, __new_finish, this->get_allocator());
						_M_deallocate(__new_start.base(), __len);
						__throw_exception_again;
					}
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, this->get_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __new_start.base();
					this->_M_impl._M_finish = __new_finish.base();
					this->_M_impl._M_end_of_storage = __new_start.base() + __len;
				}
			}
		}

		void _M_fill_insert(iterator __position, size_type __n, const value_type &__x)
		{
			if (__n != 0)
			{
				if (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_finish) >= __n)
				{
					value_type __x_copy = __x;
					const size_type __elems_after = end() - __position;
					iterator __old_finish(this->_M_impl._M_finish);
					if (__elems_after > __n)
					{
						__uninitialized_copy_a(this->_M_impl._M_finish - __n, this->_M_impl._M_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish += __n;
						copy_backward(__position, __old_finish - __n, __old_finish);
						fill(__position, __position + __n, __x_copy);
					}
					else
					{
						__uninitialized_fill_n_a(this->_M_impl._M_finish, __n - __elems_after, __x_copy, this->get_allocator());
						this->_M_impl._M_finish += __n - __elems_after;
						__uninitialized_copy_a(__position, __old_finish, this->_M_impl._M_finish, this->get_allocator());
						this->_M_impl._M_finish += __elems_after;
						fill(__position, __old_finish, __x_copy);
					}
				}
				else
				{
					const size_type __old_size = size();
					if (this->max_size() - __old_size < __n)
						std::__throw_length_error(__N("vector::_M_fill_insert"));

					size_type __len = __old_size + max(__old_size, __n);
					if (__len < __old_size)
						__len = this->max_size();

					iterator __new_start(this->_M_allocate(__len));
					iterator __new_finish(__new_start);
					try
					{
						__new_finish = __uninitialized_copy_a(begin(), __position, __new_start, this->get_allocator());
						__uninitialized_fill_n_a(__new_finish, __n, __x, this->get_allocator());
						__new_finish += __n;
						__new_finish = __uninitialized_copy_a(__position, end(), __new_finish, this->get_allocator());
					}
					catch (...)
					{
						_Destroy(__new_start, __new_finish, this->get_allocator());
						_M_deallocate(__new_start.base(), __len);
						__throw_exception_again;
					}
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, this->get_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __new_start.base();
					this->_M_impl._M_finish = __new_finish.base();
					this->_M_impl._M_end_of_storage = __new_start.base() + __len;
				}
			}
		}

		void _M_insert_aux(iterator __position, const value_type &__x)
		{
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
			{
				this->_M_impl.construct(this->_M_impl._M_finish,
										*(this->_M_impl._M_finish - 1));
				++this->_M_impl._M_finish;
				_Tp __x_copy = __x;
				copy_backward(__position, iterator(this->_M_impl._M_finish - 2), iterator(this->_M_impl._M_finish - 1));
				*__position = __x_copy;
			}
			else
			{
				const size_type __old_size = size();
				if (__old_size == this->max_size())
					std::__throw_length_error(__N("vector::_M_insert_aux"));

				size_type __len = __old_size != 0 ? 2 * __old_size : 1;
				if (__len < __old_size)
					__len = this->max_size();

				iterator __new_start(this->_M_allocate(__len));
				iterator __new_finish(__new_start);
				try
				{
					__new_finish =
						__uninitialized_copy_a(iterator(this->_M_impl._M_start), __position, __new_start, this->get_allocator());
					this->_M_impl.construct(__new_finish.base(), __x);
					++__new_finish;
					__new_finish =
						__uninitialized_copy_a(__position, iterator(this->_M_impl._M_finish), __new_finish, this->get_allocator());
				}
				catch (...)
				{
					_Destroy(__new_start, __new_finish, this->get_allocator());
					_M_deallocate(__new_start.base(), __len);
					__throw_exception_again;
				}
				_Destroy(begin(), end(), this->get_allocator());
				_M_deallocate(this->_M_impl._M_start,
							  this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				this->_M_impl._M_start = __new_start.base();
				this->_M_impl._M_finish = __new_finish.base();
				this->_M_impl._M_end_of_storage = __new_start.base() + __len;
			}
		}
	};

	template <typename _Tp, typename _Alloc>
	inline bool operator==(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return (__x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin()));
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator!=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator<=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Alloc>
	inline bool operator>=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _Alloc>
	inline void swap(vector<_Tp, _Alloc> &__x, vector<_Tp, _Alloc> &__y)
	{
		__x.swap(__y);
	}

}

#endif
