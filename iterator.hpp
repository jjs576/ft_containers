#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t, typename _Pointer = _Tp *, typename _Reference = _Tp &>
	struct iterator
	{
		typedef _Category iterator_category;
		typedef _Tp value_type;
		typedef _Distance difference_type;
		typedef _Pointer pointer;
		typedef _Reference reference;
	};

	template <typename _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type value_type;
		typedef typename _Iterator::difference_type difference_type;
		typedef typename _Iterator::pointer pointer;
		typedef typename _Iterator::reference reference;
	};

	template <typename _Tp>
	struct iterator_traits<_Tp *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef _Tp *pointer;
		typedef _Tp &reference;
	};

	template <typename _Tp>
	struct iterator_traits<const _Tp *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef const _Tp *pointer;
		typedef const _Tp &reference;
	};

	template <typename _Iter>
	inline typename iterator_traits<_Iter>::iterator_category __iterator_category(const _Iter &)
	{
		return typename iterator_traits<_Iter>::iterator_category();
	}

	template <typename _InputIterator>
	inline typename iterator_traits<_InputIterator>::difference_type __distance(_InputIterator __first, _InputIterator __last, input_iterator_tag)
	{
		typename iterator_traits<_InputIterator>::difference_type __n = 0;
		while (__first != __last)
		{
			++__first;
			++__n;
		}
		return __n;
	}

	template <typename _RandomAccessIterator>
	inline typename iterator_traits<_RandomAccessIterator>::difference_type __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, random_access_iterator_tag)
	{
		return __last - __first;
	}

	template <typename _InputIterator>
	inline typename iterator_traits<_InputIterator>::difference_type distance(_InputIterator __first, _InputIterator __last)
	{
		return __distance(__first, __last, __iterator_category(__first));
	}

	template <typename _InputIterator, typename _Distance>
	inline void __advance(_InputIterator &__i, _Distance __n, input_iterator_tag)
	{
		while (__n--)
			++__i;
	}

	template <typename _BidirectionalIterator, typename _Distance>
	inline void __advance(_BidirectionalIterator &__i, _Distance __n, bidirectional_iterator_tag)
	{
		if (__n > 0)
			while (__n--)
				++__i;
		else
			while (__n++)
				--__i;
	}

	template <typename _RandomAccessIterator, typename _Distance>
	inline void __advance(_RandomAccessIterator &__i, _Distance __n, random_access_iterator_tag)
	{
		__i += __n;
	}

	template <typename _InputIterator, typename _Distance>
	inline void advance(_InputIterator &__i, _Distance __n)
	{
		__advance(__i, __n, __iterator_category(__i));
	}

	// reverse iterator

	template <typename _Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<_Iterator>::iterator_category,
						  typename iterator_traits<_Iterator>::value_type,
						  typename iterator_traits<_Iterator>::difference_type,
						  typename iterator_traits<_Iterator>::pointer,
						  typename iterator_traits<_Iterator>::reference>
	{
	protected:
		_Iterator current;

	public:
		typedef _Iterator iterator_type;
		typedef typename iterator_traits<_Iterator>::difference_type difference_type;
		typedef typename iterator_traits<_Iterator>::reference reference;
		typedef typename iterator_traits<_Iterator>::pointer pointer;

	public:
		reverse_iterator() : current() {}

		explicit reverse_iterator(iterator_type __x) : current(__x) {}

		reverse_iterator(const reverse_iterator &__x) : current(__x.current) {}

		template <typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter> &__x) : current(__x.base()) {}

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			_Iterator __tmp = current;
			return *--__tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator __tmp = *this;
			--current;
			return __tmp;
		}

		reverse_iterator &
		operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator __tmp = *this;
			++current;
			return __tmp;
		}

		reverse_iterator operator+(difference_type __n) const
		{
			return reverse_iterator(current - __n);
		}

		reverse_iterator &operator+=(difference_type __n)
		{
			current -= __n;
			return *this;
		}

		reverse_iterator operator-(difference_type __n) const
		{
			return reverse_iterator(current + __n);
		}

		reverse_iterator &operator-=(difference_type __n)
		{
			current += __n;
			return *this;
		}

		reference operator[](difference_type __n) const
		{
			return *(*this + __n);
		}
	};

	template <typename _Iterator>
	inline bool operator==(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return __x.base() == __y.base();
	}

	template <typename _Iterator>
	inline bool operator<(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return __y.base() < __x.base();
	}

	template <typename _Iterator>
	inline bool operator!=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Iterator>
	inline bool operator>(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return __y < __x;
	}

	template <typename _Iterator>
	inline bool operator<=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Iterator>
	inline bool operator>=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Iterator>
	inline typename reverse_iterator<_Iterator>::difference_type operator-(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y)
	{
		return __y.base() - __x.base();
	}

	template <typename _Iterator>
	inline reverse_iterator<_Iterator> operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator> &__x)
	{
		return reverse_iterator<_Iterator>(__x.base() - __n);
	}

	// inserter

	template <typename _Container>
	class back_insert_iterator
		: public iterator<output_iterator_tag, void, void, void, void>
	{
	protected:
		_Container *container;

	public:
		typedef _Container container_type;

		explicit back_insert_iterator(_Container &__x) : container(&__x) {}

		back_insert_iterator &operator=(typename _Container::const_reference __value)
		{
			container->push_back(__value);
			return *this;
		}

		back_insert_iterator &operator*()
		{
			return *this;
		}

		back_insert_iterator &operator++()
		{
			return *this;
		}

		back_insert_iterator operator++(int)
		{
			return *this;
		}
	};

	template <typename _Container>
	inline back_insert_iterator<_Container> back_inserter(_Container &__x)
	{
		return back_insert_iterator<_Container>(__x);
	}

	template <typename _Container>
	class front_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{
	protected:
		_Container *container;

	public:
		typedef _Container container_type;

		explicit front_insert_iterator(_Container &__x) : container(&__x) {}

		front_insert_iterator &operator=(typename _Container::const_reference __value)
		{
			container->push_front(__value);
			return *this;
		}

		front_insert_iterator &operator*()
		{
			return *this;
		}

		front_insert_iterator &operator++()
		{
			return *this;
		}

		front_insert_iterator operator++(int)
		{
			return *this;
		}
	};

	template <typename _Container>
	inline front_insert_iterator<_Container>
	front_inserter(_Container &__x)
	{
		return front_insert_iterator<_Container>(__x);
	}

	template <typename _Container>
	class insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
	{
	protected:
		_Container *container;
		typename _Container::iterator iter;

	public:
		typedef _Container container_type;

		insert_iterator(_Container &__x, typename _Container::iterator __i) : container(&__x), iter(__i) {}

		insert_iterator &
		operator=(const typename _Container::const_reference __value)
		{
			iter = container->insert(iter, __value);
			++iter;
			return *this;
		}

		insert_iterator &operator*()
		{
			return *this;
		}

		insert_iterator &operator++()
		{
			return *this;
		}

		insert_iterator &operator++(int)
		{
			return *this;
		}
	};

	template <typename _Container, typename _Iterator>
	inline insert_iterator<_Container> inserter(_Container &__x, _Iterator __i)
	{
		return insert_iterator<_Container>(__x, typename _Container::iterator(__i));
	}

	// normal iterator

	template <typename _Iterator, typename _Container>
	class __normal_iterator
	{
	protected:
		_Iterator _M_current;


	public:
		typedef typename iterator_traits<_Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<_Iterator>::value_type value_type;
		typedef typename iterator_traits<_Iterator>::difference_type difference_type;
		typedef typename iterator_traits<_Iterator>::reference reference;
		typedef typename iterator_traits<_Iterator>::pointer pointer;

		__normal_iterator() : _M_current(_Iterator()) {}

		explicit __normal_iterator(const _Iterator &__i) : _M_current(__i) {}

		template <typename _Iter>
		inline __normal_iterator(const __normal_iterator<_Iter, _Container> &__i) : _M_current(__i.base()) {}

		reference operator*() const
		{
			return *_M_current;
		}

		pointer operator->() const
		{
			return _M_current;
		}

		__normal_iterator &operator++()
		{
			++_M_current;
			return *this;
		}

		__normal_iterator operator++(int)
		{
			return __normal_iterator(_M_current++);
		}

		__normal_iterator &operator--()
		{
			--_M_current;
			return *this;
		}

		__normal_iterator operator--(int)
		{
			return __normal_iterator(_M_current--);
		}

		reference operator[](const difference_type &__n) const
		{
			return _M_current[__n];
		}

		__normal_iterator &operator+=(const difference_type &__n)
		{
			_M_current += __n;
			return *this;
		}

		__normal_iterator operator+(const difference_type &__n) const
		{
			return __normal_iterator(_M_current + __n);
		}

		__normal_iterator &operator-=(const difference_type &__n)
		{
			_M_current -= __n;
			return *this;
		}

		__normal_iterator operator-(const difference_type &__n) const
		{
			return __normal_iterator(_M_current - __n);
		}

		const _Iterator &base() const
		{
			return _M_current;
		}
	};

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator==(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() == __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator==(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() == __rhs.base();
	}

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator!=(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() != __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator!=(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() != __rhs.base();
	}

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator<(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() < __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator<(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() < __rhs.base();
	}

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator>(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() > __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator>(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() > __rhs.base();
	}

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator<=(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() <= __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator<=(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() <= __rhs.base();
	}

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator>=(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() >= __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline bool operator>=(const __normal_iterator<_Iterator, _Container> &__lhs, const __normal_iterator<_Iterator, _Container> &__rhs)
	{
		return __lhs.base() >= __rhs.base();
	}
	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline typename __normal_iterator<_IteratorL, _Container>::difference_type operator-(const __normal_iterator<_IteratorL, _Container> &__lhs, const __normal_iterator<_IteratorR, _Container> &__rhs)
	{
		return __lhs.base() - __rhs.base();
	}

	template <typename _Iterator, typename _Container>
	inline __normal_iterator<_Iterator, _Container> operator+(typename __normal_iterator<_Iterator, _Container>::difference_type __n, const __normal_iterator<_Iterator, _Container> &__i)
	{
		return __normal_iterator<_Iterator, _Container>(__i.base() + __n);
	}
}

#endif
