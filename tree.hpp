#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include "algorithm.hpp"
#include "construct.hpp"
#include "functional.hpp"
#include "type_traits.hpp"

namespace ft
{
	enum _Rb_tree_color
	{
		_S_red = false,
		_S_black = true
	};

	struct _Rb_tree_node_base
	{
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

		_Rb_tree_color _M_color;
		_Base_ptr _M_parent;
		_Base_ptr _M_left;
		_Base_ptr _M_right;

		static _Base_ptr _S_minimum(_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}

		static _Base_ptr _S_maximum(_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}

		static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}
	};

	template <typename _Val>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
		typedef _Rb_tree_node<_Val> *_Link_type;
		_Val _M_value_field;
	};

	_Rb_tree_node_base *_Rb_tree_increment(_Rb_tree_node_base *__x)
	{
		if (__x->_M_right != 0)
		{
			__x = __x->_M_right;
			while (__x->_M_left != 0)
				__x = __x->_M_left;
		}
		else
		{
			_Rb_tree_node_base *__y = __x->_M_parent;
			while (__x == __y->_M_right)
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			if (__x->_M_right != __y)
				__x = __y;
		}
		return __x;
	}

	const _Rb_tree_node_base *_Rb_tree_increment(const _Rb_tree_node_base *__x)
	{
		return _Rb_tree_increment(const_cast<_Rb_tree_node_base *>(__x));
	}

	_Rb_tree_node_base *_Rb_tree_decrement(_Rb_tree_node_base *__x)
	{
		if (__x->_M_color == _S_red && __x->_M_parent->_M_parent == __x)
			__x = __x->_M_right;
		else if (__x->_M_left != 0)
		{
			_Rb_tree_node_base *__y = __x->_M_left;
			while (__y->_M_right != 0)
				__y = __y->_M_right;
			__x = __y;
		}
		else
		{
			_Rb_tree_node_base *__y = __x->_M_parent;
			while (__x == __y->_M_left)
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			__x = __y;
		}
		return __x;
	}

	const _Rb_tree_node_base *_Rb_tree_decrement(const _Rb_tree_node_base *__x)
	{
		return _Rb_tree_decrement(const_cast<_Rb_tree_node_base *>(__x));
	}

	template <typename _Tp>
	struct _Rb_tree_iterator
	{
		typedef _Tp value_type;
		typedef _Tp &reference;
		typedef _Tp *pointer;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _Rb_tree_iterator<_Tp> _Self;
		typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
		typedef _Rb_tree_node<_Tp> *_Link_type;

		_Rb_tree_iterator() : _M_node() {}

		_Rb_tree_iterator(_Link_type __x) : _M_node(__x) {}

		reference operator*() const
		{
			return static_cast<_Link_type>(_M_node)->_M_value_field;
		}

		pointer operator->() const
		{
			return &static_cast<_Link_type>(_M_node)->_M_value_field;
		}

		_Self &operator++()
		{
			_M_node = _Rb_tree_increment(_M_node);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self &operator--()
		{
			_M_node = _Rb_tree_decrement(_M_node);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_decrement(_M_node);
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

		_Base_ptr _M_node;
	};

	template <typename _Tp>
	struct _Rb_tree_const_iterator
	{
		typedef _Tp value_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;

		typedef _Rb_tree_iterator<_Tp> iterator;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _Rb_tree_const_iterator<_Tp> _Self;
		typedef _Rb_tree_node_base::_Const_Base_ptr _Base_ptr;
		typedef const _Rb_tree_node<_Tp> *_Link_type;

		_Rb_tree_const_iterator() : _M_node() {}

		_Rb_tree_const_iterator(_Link_type __x) : _M_node(__x) {}

		_Rb_tree_const_iterator(const iterator &__it) : _M_node(__it._M_node) {}

		reference operator*() const
		{
			return static_cast<_Link_type>(_M_node)->_M_value_field;
		}

		pointer operator->() const
		{
			return &static_cast<_Link_type>(_M_node)->_M_value_field;
		}

		_Self &operator++()
		{
			_M_node = _Rb_tree_increment(_M_node);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self &operator--()
		{
			_M_node = _Rb_tree_decrement(_M_node);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_decrement(_M_node);
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

		_Base_ptr _M_node;
	};

	template <typename _Val>
	inline bool operator==(const _Rb_tree_iterator<_Val> &__x, const _Rb_tree_const_iterator<_Val> &__y)
	{
		return __x._M_node == __y._M_node;
	}

	template <typename _Val>
	inline bool operator!=(const _Rb_tree_iterator<_Val> &__x, const _Rb_tree_const_iterator<_Val> &__y)
	{
		return __x._M_node != __y._M_node;
	}

	void _Rb_tree_rotate_left(_Rb_tree_node_base *const __x, _Rb_tree_node_base *&__root)
	{
		_Rb_tree_node_base *const __y = __x->_M_right;

		__x->_M_right = __y->_M_left;
		if (__y->_M_left != 0)
			__y->_M_left->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_left)
			__x->_M_parent->_M_left = __y;
		else
			__x->_M_parent->_M_right = __y;
		__y->_M_left = __x;
		__x->_M_parent = __y;
	}

	void _Rb_tree_rotate_right(_Rb_tree_node_base *const __x, _Rb_tree_node_base *&__root)
	{
		_Rb_tree_node_base *const __y = __x->_M_left;

		__x->_M_left = __y->_M_right;
		if (__y->_M_right != 0)
			__y->_M_right->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_right)
			__x->_M_parent->_M_right = __y;
		else
			__x->_M_parent->_M_left = __y;
		__y->_M_right = __x;
		__x->_M_parent = __y;
	}

	void _Rb_tree_insert_and_rebalance(const bool __insert_left, _Rb_tree_node_base *__x, _Rb_tree_node_base *__p, _Rb_tree_node_base &__header)
	{
		_Rb_tree_node_base *&__root = __header._M_parent;

		// Initialize fields in new node to insert.
		__x->_M_parent = __p;
		__x->_M_left = 0;
		__x->_M_right = 0;
		__x->_M_color = _S_red;

		// Insert.
		// Make new node child of parent and maintain root, leftmost and
		// rightmost nodes.
		// N.B. First node is always inserted left.
		if (__insert_left)
		{
			__p->_M_left = __x; // also makes leftmost = __x when __p == &__header

			if (__p == &__header)
			{
				__header._M_parent = __x;
				__header._M_right = __x;
			}
			else if (__p == __header._M_left)
				__header._M_left = __x; // maintain leftmost pointing to min node
		}
		else
		{
			__p->_M_right = __x;

			if (__p == __header._M_right)
				__header._M_right = __x; // maintain rightmost pointing to max node
		}
		// Rebalance.
		while (__x != __root && __x->_M_parent->_M_color == _S_red)
		{
			_Rb_tree_node_base *const __xpp = __x->_M_parent->_M_parent;

			if (__x->_M_parent == __xpp->_M_left)
			{
				_Rb_tree_node_base *const __y = __xpp->_M_right;
				if (__y && __y->_M_color == _S_red)
				{
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->_M_parent->_M_right)
					{
						__x = __x->_M_parent;
						_Rb_tree_rotate_left(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					_Rb_tree_rotate_right(__xpp, __root);
				}
			}
			else
			{
				_Rb_tree_node_base *const __y = __xpp->_M_left;
				if (__y && __y->_M_color == _S_red)
				{
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->_M_parent->_M_left)
					{
						__x = __x->_M_parent;
						_Rb_tree_rotate_right(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					_Rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->_M_color = _S_black;
	}

	_Rb_tree_node_base *_Rb_tree_rebalance_for_erase(_Rb_tree_node_base *const __z, _Rb_tree_node_base &__header)
	{
		_Rb_tree_node_base *&__root = __header._M_parent;
		_Rb_tree_node_base *&__leftmost = __header._M_left;
		_Rb_tree_node_base *&__rightmost = __header._M_right;
		_Rb_tree_node_base *__y = __z;
		_Rb_tree_node_base *__x = 0;
		_Rb_tree_node_base *__x_parent = 0;

		if (__y->_M_left == 0)
			__x = __y->_M_right;
		else if (__y->_M_right == 0)
			__x = __y->_M_left;
		else
		{
			__y = __y->_M_right;
			while (__y->_M_left != 0)
				__y = __y->_M_left;
			__x = __y->_M_right;
		}
		if (__y != __z)
		{
			__z->_M_left->_M_parent = __y;
			__y->_M_left = __z->_M_left;
			if (__y != __z->_M_right)
			{
				__x_parent = __y->_M_parent;
				if (__x)
					__x->_M_parent = __y->_M_parent;
				__y->_M_parent->_M_left = __x;
				__y->_M_right = __z->_M_right;
				__z->_M_right->_M_parent = __y;
			}
			else
				__x_parent = __y;
			if (__root == __z)
				__root = __y;
			else if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __y;
			else
				__z->_M_parent->_M_right = __y;
			__y->_M_parent = __z->_M_parent;
			ft::swap(__y->_M_color, __z->_M_color);
			__y = __z;
		}
		else
		{ // __y == __z
			__x_parent = __y->_M_parent;
			if (__x)
				__x->_M_parent = __y->_M_parent;
			if (__root == __z)
				__root = __x;
			else if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __x;
			else
				__z->_M_parent->_M_right = __x;
			if (__leftmost == __z)
			{
				if (__z->_M_right == 0)
					__leftmost = __z->_M_parent;
				else
					__leftmost = _Rb_tree_node_base::_S_minimum(__x);
			}
			if (__rightmost == __z)
			{
				if (__z->_M_left == 0)
					__rightmost = __z->_M_parent;
				else
					__rightmost = _Rb_tree_node_base::_S_maximum(__x);
			}
		}
		if (__y->_M_color != _S_red)
		{
			while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
				if (__x == __x_parent->_M_left)
				{
					_Rb_tree_node_base *__w = __x_parent->_M_right;
					if (__w->_M_color == _S_red)
					{
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						_Rb_tree_rotate_left(__x_parent, __root);
						__w = __x_parent->_M_right;
					}
					if ((__w->_M_left == 0 ||
						 __w->_M_left->_M_color == _S_black) &&
						(__w->_M_right == 0 ||
						 __w->_M_right->_M_color == _S_black))
					{
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					}
					else
					{
						if (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)
						{
							__w->_M_left->_M_color = _S_black;
							__w->_M_color = _S_red;
							_Rb_tree_rotate_right(__w, __root);
							__w = __x_parent->_M_right;
						}
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_right)
							__w->_M_right->_M_color = _S_black;
						_Rb_tree_rotate_left(__x_parent, __root);
						break;
					}
				}
				else
				{
					_Rb_tree_node_base *__w = __x_parent->_M_left;
					if (__w->_M_color == _S_red)
					{
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						_Rb_tree_rotate_right(__x_parent, __root);
						__w = __x_parent->_M_left;
					}
					if ((__w->_M_right == 0 ||
						 __w->_M_right->_M_color == _S_black) &&
						(__w->_M_left == 0 ||
						 __w->_M_left->_M_color == _S_black))
					{
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					}
					else
					{
						if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
						{
							__w->_M_right->_M_color = _S_black;
							__w->_M_color = _S_red;
							_Rb_tree_rotate_left(__w, __root);
							__w = __x_parent->_M_left;
						}
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_left)
							__w->_M_left->_M_color = _S_black;
						_Rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
			if (__x)
				__x->_M_color = _S_black;
		}
		return __y;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = allocator<_Val> >
	class _Rb_tree
	{
		typedef typename _Alloc::template rebind<_Rb_tree_node<_Val> >::other _Node_allocator;

	protected:
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;
		typedef _Rb_tree_node<_Val> _Rb_tree_node;

	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef _Rb_tree_node *_Link_type;
		typedef const _Rb_tree_node *_Const_Link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const
		{
			return *static_cast<const _Node_allocator *>(&this->_M_impl);
		}

	protected:
		_Rb_tree_node *_M_get_node()
		{
			return _M_impl._Node_allocator::allocate(1);
		}

		void _M_put_node(_Rb_tree_node *__p)
		{
			_M_impl._Node_allocator::deallocate(__p, 1);
		}

		_Link_type _M_create_node(const value_type &__x)
		{
			_Link_type __tmp = _M_get_node();
			try
			{
				get_allocator().construct(&__tmp->_M_value_field, __x);
			}
			catch (...)
			{
				_M_put_node(__tmp);
				__throw_exception_again;
			}
			return __tmp;
		}

		_Link_type _M_clone_node(_Const_Link_type __x)
		{
			_Link_type __tmp = _M_create_node(__x->_M_value_field);
			__tmp->_M_color = __x->_M_color;
			__tmp->_M_left = 0;
			__tmp->_M_right = 0;
			return __tmp;
		}

		void destroy_node(_Link_type __p)
		{
			get_allocator().destroy(&__p->_M_value_field);
			_M_put_node(__p);
		}

	protected:
		template <typename _Key_compare, bool _Is_pod_comparator = __is_pod<_Key_compare>::__value>
		struct _Rb_tree_impl : public _Node_allocator
		{
			_Key_compare _M_key_compare;
			_Rb_tree_node_base _M_header;
			size_type _M_node_count;

			_Rb_tree_impl(const _Node_allocator &__a = _Node_allocator(), const _Key_compare &__comp = _Key_compare()) : _Node_allocator(__a), _M_key_compare(__comp), _M_node_count(0)
			{
				this->_M_header._M_color = _S_red;
				this->_M_header._M_parent = 0;
				this->_M_header._M_left = &this->_M_header;
				this->_M_header._M_right = &this->_M_header;
			}
		};

		template <typename _Key_compare>
		struct _Rb_tree_impl<_Key_compare, true> : public _Node_allocator
		{
			_Key_compare _M_key_compare;
			_Rb_tree_node_base _M_header;
			size_type _M_node_count;

			_Rb_tree_impl(const _Node_allocator &__a = _Node_allocator(), const _Key_compare &__comp = _Key_compare()) : _Node_allocator(__a), _M_key_compare(__comp), _M_node_count(0)
			{
				this->_M_header._M_color = _S_red;
				this->_M_header._M_parent = 0;
				this->_M_header._M_left = &this->_M_header;
				this->_M_header._M_right = &this->_M_header;
			}
		};

		_Rb_tree_impl<_Compare> _M_impl;

	protected:
		_Base_ptr &_M_root()
		{
			return this->_M_impl._M_header._M_parent;
		}

		_Const_Base_ptr _M_root() const
		{
			return this->_M_impl._M_header._M_parent;
		}

		_Base_ptr &_M_leftmost()
		{
			return this->_M_impl._M_header._M_left;
		}

		_Const_Base_ptr _M_leftmost() const
		{
			return this->_M_impl._M_header._M_left;
		}

		_Base_ptr &_M_rightmost()
		{
			return this->_M_impl._M_header._M_right;
		}

		_Const_Base_ptr _M_rightmost() const
		{
			return this->_M_impl._M_header._M_right;
		}

		_Link_type _M_begin()
		{
			return static_cast<_Link_type>(this->_M_impl._M_header._M_parent);
		}

		_Const_Link_type _M_begin() const
		{
			return static_cast<_Const_Link_type>(this->_M_impl._M_header._M_parent);
		}

		_Link_type _M_end()
		{
			return static_cast<_Link_type>(&this->_M_impl._M_header);
		}

		_Const_Link_type _M_end() const
		{
			return static_cast<_Const_Link_type>(&this->_M_impl._M_header);
		}

		static const_reference _S_value(_Const_Link_type __x)
		{
			return __x->_M_value_field;
		}

		static const _Key &_S_key(_Const_Link_type __x)
		{
			return _KeyOfValue()(_S_value(__x));
		}

		static _Link_type _S_left(_Base_ptr __x)
		{
			return static_cast<_Link_type>(__x->_M_left);
		}

		static _Const_Link_type _S_left(_Const_Base_ptr __x)
		{
			return static_cast<_Const_Link_type>(__x->_M_left);
		}

		static _Link_type _S_right(_Base_ptr __x)
		{
			return static_cast<_Link_type>(__x->_M_right);
		}

		static _Const_Link_type _S_right(_Const_Base_ptr __x)
		{
			return static_cast<_Const_Link_type>(__x->_M_right);
		}

		static const_reference _S_value(_Const_Base_ptr __x)
		{
			return static_cast<_Const_Link_type>(__x)->_M_value_field;
		}

		static const _Key &_S_key(_Const_Base_ptr __x)
		{
			return _KeyOfValue()(_S_value(__x));
		}

		static _Base_ptr _S_minimum(_Base_ptr __x)
		{
			return _Rb_tree_node_base::_S_minimum(__x);
		}

		static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x)
		{
			return _Rb_tree_node_base::_S_minimum(__x);
		}

		static _Base_ptr _S_maximum(_Base_ptr __x)
		{
			return _Rb_tree_node_base::_S_maximum(__x);
		}

		static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x)
		{
			return _Rb_tree_node_base::_S_maximum(__x);
		}

	public:
		typedef _Rb_tree_iterator<value_type> iterator;
		typedef _Rb_tree_const_iterator<value_type> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

		typedef reverse_iterator<iterator> reverse_iterator;

	private:
		iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type &__v);

		_Link_type _M_copy(_Const_Link_type __x, _Link_type __p);

		void _M_erase(_Link_type __x);

	public:
		_Rb_tree()
		{
		}

		_Rb_tree(const _Compare &__comp) : _M_impl(allocator_type(), __comp)
		{
		}

		_Rb_tree(const _Compare &__comp, const allocator_type &__a) : _M_impl(__a, __comp)
		{
		}

		_Rb_tree(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x) : _M_impl(__x.get_allocator(), __x._M_impl._M_key_compare)
		{
			if (__x._M_root() != 0)
			{
				_M_root() = _M_copy(__x._M_begin(), _M_end());
				_M_leftmost() = _S_minimum(_M_root());
				_M_rightmost() = _S_maximum(_M_root());
				_M_impl._M_node_count = __x._M_impl._M_node_count;
			}
		}

		~_Rb_tree()
		{
			_M_erase(_M_begin());
		}

		_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &operator=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x);

		_Compare key_comp() const
		{
			return _M_impl._M_key_compare;
		}

		iterator begin()
		{
			return static_cast<_Link_type>(this->_M_impl._M_header._M_left);
		}

		const_iterator begin() const
		{
			return static_cast<_Const_Link_type>(this->_M_impl._M_header._M_left);
		}

		iterator end()
		{
			return static_cast<_Link_type>(&this->_M_impl._M_header);
		}

		const_iterator end() const
		{
			return static_cast<_Const_Link_type>(&this->_M_impl._M_header);
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
			return _M_impl._M_node_count == 0;
		}

		size_type size() const
		{
			return _M_impl._M_node_count;
		}

		size_type max_size() const
		{
			return size_type(-1);
		}

		void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__t);

		pair<iterator, bool> insert_unique(const value_type &__x);

		iterator insert_equal(const value_type &__x);

		iterator insert_unique(iterator __position, const value_type &__x);

		iterator insert_equal(iterator __position, const value_type &__x);

		template <typename _InputIterator>
		void insert_unique(_InputIterator __first, _InputIterator __last);

		template <typename _InputIterator>
		void insert_equal(_InputIterator __first, _InputIterator __last);

		void erase(iterator __position);

		size_type erase(const key_type &__x);

		void erase(iterator __first, iterator __last);

		void erase(const key_type *__first, const key_type *__last);

		void clear()
		{
			_M_erase(_M_begin());
			_M_leftmost() = _M_end();
			_M_root() = 0;
			_M_rightmost() = _M_end();
			_M_impl._M_node_count = 0;
		}

		iterator find(const key_type &__x);

		const_iterator find(const key_type &__x) const;

		size_type count(const key_type &__x) const;

		iterator lower_bound(const key_type &__x);

		const_iterator lower_bound(const key_type &__x) const;

		iterator upper_bound(const key_type &__x);

		const_iterator upper_bound(const key_type &__x) const;

		pair<iterator, iterator> equal_range(const key_type &__x);

		pair<const_iterator, const_iterator> equal_range(const key_type &__x) const;

		bool
		__rb_verify() const;
	};

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator==(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return __x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin());
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator<(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator!=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator>(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator<=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool operator>=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x, _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
	{
		__x.swap(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::operator=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x)
	{
		if (this != &__x)
		{
			clear();
			_M_impl._M_key_compare = __x._M_impl._M_key_compare;
			if (__x._M_root() != 0)
			{
				_M_root() = _M_copy(__x._M_begin(), _M_end());
				_M_leftmost() = _S_minimum(_M_root());
				_M_rightmost() = _S_maximum(_M_root());
				_M_impl._M_node_count = __x._M_impl._M_node_count;
			}
		}
		return *this;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_insert(_Base_ptr __x, _Base_ptr __p, const _Val &__v)
	{
		_Link_type __z = _M_create_node(__v);
		bool __insert_left;

		__insert_left = (__x != 0 || __p == _M_end() || _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

		_Rb_tree_insert_and_rebalance(__insert_left, __z, __p, this->_M_impl._M_header);
		++_M_impl._M_node_count;
		return iterator(__z);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_equal(const _Val &__v)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ? _S_left(__x) : _S_right(__x);
		}
		return _M_insert(__x, __y, __v);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__t)
	{
		if (_M_root() == 0)
		{
			if (__t._M_root() != 0)
			{
				_M_root() = __t._M_root();
				_M_leftmost() = __t._M_leftmost();
				_M_rightmost() = __t._M_rightmost();
				_M_root()->_M_parent = _M_end();

				__t._M_root() = 0;
				__t._M_leftmost() = __t._M_end();
				__t._M_rightmost() = __t._M_end();
			}
		}
		else if (__t._M_root() == 0)
		{
			__t._M_root() = _M_root();
			__t._M_leftmost() = _M_leftmost();
			__t._M_rightmost() = _M_rightmost();
			__t._M_root()->_M_parent = __t._M_end();

			_M_root() = 0;
			_M_leftmost() = _M_end();
			_M_rightmost() = _M_end();
		}
		else
		{
			ft::swap(_M_root(), __t._M_root());
			ft::swap(_M_leftmost(), __t._M_leftmost());
			ft::swap(_M_rightmost(), __t._M_rightmost());

			_M_root()->_M_parent = _M_end();
			__t._M_root()->_M_parent = __t._M_end();
		}
		ft::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
		ft::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_unique(const _Val &__v)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();
		bool __comp = true;
		while (__x != 0)
		{
			__y = __x;
			__comp = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x));
			__x = __comp ? _S_left(__x) : _S_right(__x);
		}
		iterator __j = iterator(__y);
		if (__comp)
		{
			if (__j == begin())
				return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
			else
				--__j;
		}
		if (_M_impl._M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
			return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
		return pair<iterator, bool>(__j, false);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_unique(iterator __position, const _Val &__v)
	{
		if (__position._M_node == _M_end() || __position._M_node == _M_rightmost())
		{
			if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()),
													 _KeyOfValue()(__v)))
				return _M_insert(0, _M_rightmost(), __v);
			else
				return insert_unique(__v).first;
		}
		else
		{
			iterator __after = __position;
			++__after;
			if (_M_impl._M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)) && _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__after._M_node)))
			{
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			}
			else
				return insert_unique(__v).first;
		}
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_equal(iterator __position, const _Val &__v)
	{
		if (__position._M_node == _M_end() || __position._M_node == _M_rightmost())
		{
			if (size() > 0 && !_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))
				return _M_insert(0, _M_rightmost(), __v);
			else
				return insert_equal(__v);
		}
		else
		{
			iterator __after = __position;
			++__after;
			if (!_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)) && !_M_impl._M_key_compare(_S_key(__after._M_node), _KeyOfValue()(__v)))
			{
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			}
			else
				return insert_equal(__v);
		}
	}

	template <typename _Key, typename _Val, typename _KoV, typename _Cmp, typename _Alloc>
	template <class _II>
	void _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::insert_equal(_II __first, _II __last)
	{
		for (; __first != __last; ++__first)
			insert_equal(end(), *__first);
	}

	template <typename _Key, typename _Val, typename _KoV, typename _Cmp, typename _Alloc>
	template <class _II>
	void _Rb_tree<_Key, _Val, _KoV, _Cmp, _Alloc>::insert_unique(_II __first, _II __last)
	{
		for (; __first != __last; ++__first)
			insert_unique(end(), *__first);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(iterator __position)
	{
		_Link_type __y = static_cast<_Link_type>(_Rb_tree_rebalance_for_erase(__position._M_node, this->_M_impl._M_header));
		destroy_node(__y);
		--_M_impl._M_node_count;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(const _Key &__x)
	{
		pair<iterator, iterator> __p = equal_range(__x);
		size_type __n = distance(__p.first, __p.second);
		erase(__p.first, __p.second);
		return __n;
	}

	template <typename _Key, typename _Val, typename _KoV, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_M_copy(_Const_Link_type __x, _Link_type __p)
	{
		_Link_type __top = _M_clone_node(__x);
		__top->_M_parent = __p;

		try
		{
			if (__x->_M_right)
				__top->_M_right = _M_copy(_S_right(__x), __top);
			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
				_Link_type __y = _M_clone_node(__x);
				__p->_M_left = __y;
				__y->_M_parent = __p;
				if (__x->_M_right)
					__y->_M_right = _M_copy(_S_right(__x), __y);
				__p = __y;
				__x = _S_left(__x);
			}
		}
		catch (...)
		{
			_M_erase(__top);
			__throw_exception_again;
		}
		return __top;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_erase(_Link_type __x)
	{
		while (__x != 0)
		{
			_M_erase(_S_right(__x));
			_Link_type __y = _S_left(__x);
			destroy_node(__x);
			__x = __y;
		}
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(iterator __first, iterator __last)
	{
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				erase(__first++);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(const _Key *__first, const _Key *__last)
	{
		while (__first != __last)
			erase(*__first++);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::find(const _Key &__k)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		iterator __j = iterator(__y);
		return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::find(const _Key &__k) const
	{
		_Const_Link_type __x = _M_begin();
		_Const_Link_type __y = _M_end();

		while (__x != 0)
		{
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		}
		const_iterator __j = const_iterator(__y);
		return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::count(const _Key &__k) const
	{
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = distance(__p.first, __p.second);
		return __n;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::lower_bound(const _Key &__k)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::lower_bound(const _Key &__k) const
	{
		_Const_Link_type __x = _M_begin();
		_Const_Link_type __y = _M_end();

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return const_iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::upper_bound(const _Key &__k)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();

		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::upper_bound(const _Key &__k) const
	{
		_Const_Link_type __x = _M_begin();
		_Const_Link_type __y = _M_end();

		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return const_iterator(__y);
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
	_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::equal_range(const _Key &__k)
	{
		return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
	}

	template <typename _Key, typename _Val, typename _KoV, typename _Compare, typename _Alloc>
	inline pair<typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::const_iterator, typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::const_iterator>
	_Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::equal_range(const _Key &__k) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
	}

	unsigned int _Rb_tree_black_count(const _Rb_tree_node_base *__node, const _Rb_tree_node_base *__root)
	{
		if (__node == 0)
			return 0;
		unsigned int __sum = 0;
		do
		{
			if (__node->_M_color == _S_black)
				++__sum;
			if (__node == __root)
				break;
			__node = __node->_M_parent;
		} while (1);
		return __sum;
	}

	template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	bool _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::__rb_verify() const
	{
		if (_M_impl._M_node_count == 0 || begin() == end())
			return _M_impl._M_node_count == 0 && begin() == end() && this->_M_impl._M_header._M_left == _M_end() && this->_M_impl._M_header._M_right == _M_end();

		unsigned int __len = _Rb_tree_black_count(_M_leftmost(), _M_root());
		for (const_iterator __it = begin(); __it != end(); ++__it)
		{
			_Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
			_Const_Link_type __L = _S_left(__x);
			_Const_Link_type __R = _S_right(__x);

			if (__x->_M_color == _S_red)
				if ((__L && __L->_M_color == _S_red) || (__R && __R->_M_color == _S_red))
					return false;

			if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
				return false;
			if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
				return false;

			if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
				return false;
		}

		if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
			return false;
		if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
			return false;
		return true;
	}
}

#endif
