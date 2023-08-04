#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

# include "../utils/utils.hpp"
# include "reverse_iterator.hpp"
# include <iostream>

namespace ft
{
	template <class T, class const_node>
	class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename T::value_type	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
		
		private:
			T*	_node;
			T*	_last_node;
		
		public:
			bst_iterator() : _node(NULL), _last_node(NULL) {}
			bst_iterator(T* node, T* last_node) : _node(node), _last_node(last_node) {}
			bst_iterator(const bst_iterator& bst_it) : _node(bst_it.base()), _last_node(bst_it.last_base()) {}
			~bst_iterator() {}

			T*	base() const { return (this->_node); }
			T*	last_base() const { return (this->_last_node); }
			bst_iterator&	operator=(const bst_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_node = bst_it.base();
				this->_last_node = bst_it.last_base();
				return (*this);
			}

			reference	operator*() const
			{ return *(this->_node->value); }
			pointer	operator->() const
			{ return (this->_node->value); }
			bst_iterator&	operator++()
			{
				T*	temp = this->_node;
				if (this->_node == this->_last_node)
					std::cout << this->_last_node->value->first;
				if (temp->right == NULL || temp->right == this->_last_node)
				{
					if (temp->parent == NULL)
					{
						this->_node = this->_last_node;
						return (*this);
					}
					else
					{
						if (temp->right == this->_last_node)
						{
							this->_node = this->_last_node;
							return (*this);
						}
						if (temp->parent->right == temp)
						{
							while (temp->parent && temp == temp->parent->right)
								temp = temp->parent;
							if (temp == temp->parent->left)
								temp = temp->parent;
						}
						else
							temp = temp->parent;
					}
				}
				else
				{
					temp = temp->right;
					while (temp->left)
						temp = temp->left;
				}
				this->_node = temp;
				return (*this);
			}
			bst_iterator	operator++(int)
			{
				bst_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			bst_iterator&	operator--()
			{
				T*	temp = this->_node;
				if (temp->left == NULL)
				{
					if (temp->parent == NULL)
						std::cout << this->_node->left->value->first;
					else
					{
						if (temp == temp->parent->right)
							temp = temp->parent;
						else
						{
							while (temp->parent && temp == temp->parent->left)
								temp = temp->parent;
							if (temp->parent == NULL)
								std::cout << this->_node->left->value->first;
							if (temp == temp->parent->right)
								temp = temp->parent;
						}
					}
				}
				else
				{
					temp = temp->left;
					while (temp->right && temp->right != this->_last_node)
						temp = temp->right;
				}
				this->_node = temp;
				return (*this);
			}
			bst_iterator	operator--(int)
			{
				bst_iterator	temp(*this);
				--(*this);
				return (temp);
			}
	};

	template <class T, class const_node>
	class bst_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename T::value_type																	value_type;
			typedef typename const_node::value_type															const_value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, const_value_type>::pointer		const_pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, const_value_type>::reference		const_reference;
		
		private:
			T*	_cnode;
			T*	_last_cnode;
		
		public:
			bst_const_iterator() : _cnode(NULL), _last_cnode(NULL) {}
			bst_const_iterator(const_node* node, const_node* last_node) :
				_cnode(reinterpret_cast<T*>(node)), _last_cnode(reinterpret_cast<T*>(last_node)) {}
			bst_const_iterator(T* node, T* last_node) :
				_cnode(node), _last_cnode(last_node) {}
			bst_const_iterator(const bst_const_iterator& bst_it) : _cnode(bst_it.base()), _last_cnode(bst_it.last_base()) {}
			bst_const_iterator(const bst_iterator<T, const_node>& bst_it) :
				_cnode(bst_it.base()), _last_cnode(bst_it.last_base()) {}
			~bst_const_iterator() {}

			T*	base() const { return (this->_cnode); }
			T*	last_base() const { return (this->_last_cnode); }
			bst_const_iterator&	operator=(const bst_const_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_cnode = bst_it.base();
				this->_last_cnode = bst_it.last_base();
				return (*this);
			}
			bst_const_iterator&	operator=(const bst_iterator<T, const_node>& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_cnode = bst_it.base();
				this->_last_cnode = bst_it.last_base();
				return (*this);
			}

			reference	operator*() const { return (*this->_cnode->value); }
			const_pointer	operator->() const
			{
				const_node*	ret = reinterpret_cast<const_node*>(this->_cnode);
				return (ret->value);
			}
			
			bst_const_iterator&	operator++()
			{
				T*	temp = this->_cnode;
				if (this->_cnode == this->_last_cnode)
					std::cout << this->_last_cnode->value->first;
				if (temp->right == NULL || temp->right == this->_last_cnode)
				{
					if (temp->parent == NULL)
					{
						this->_cnode = this->_last_cnode;
						return (*this);
					}
					else
					{
						if (temp->right == this->_last_cnode)
						{
							this->_cnode = this->_last_cnode;
							return (*this);
						}
						if (temp->parent->right == temp)
						{
							while (temp->parent && temp == temp->parent->right)
								temp = temp->parent;
							if (temp == temp->parent->left)
								temp = temp->parent;
						}
						else
							temp = temp->parent;
					}
				}
				else
				{
					temp = temp->right;
					while (temp->left)
						temp = temp->left;
				}
				this->_cnode = temp;
				return (*this);
			}
			bst_const_iterator	operator++(int)
			{
				bst_const_iterator	temp(*this);
				++(*this);
				return (temp);
			}

			bst_const_iterator&	operator--()
			{
				T*	temp = this->_cnode;
				if (temp->left == NULL)
				{
					if (temp->parent == NULL)
						std::cout << this->_cnode->left->value->first;
					else
					{
						if (temp == temp->parent->right)
							temp = temp->parent;
						else
						{
							while (temp->parent && temp == temp->parent->left)
								temp = temp->parent;
							if (temp->parent == NULL)
								std::cout << this->_cnode->left->value->first;
							if (temp == temp->parent->right)
								temp = temp->parent;
						}
					}
				}
				else
				{
					temp = temp->left;
					while (temp->right && temp->right != this->_last_cnode)
						temp = temp->right;
				}
				this->_cnode = temp;
				return (*this);
			}
			bst_const_iterator	operator--(int)
			{
				bst_const_iterator	temp(*this);
				--(*this);
				return (temp);
			}
	};

	template<class Node, class const_node>
	bool	operator==(const ft::bst_iterator<Node, const_node>& lhs, const ft::bst_iterator<Node, const_node>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Node, class const_node>
	bool	operator==(const ft::bst_iterator<Node, const_node>& lhs, const ft::bst_const_iterator<Node, const_node>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Node, class const_node>
	bool	operator==(const ft::bst_const_iterator<Node, const_node>& lhs, const ft::bst_iterator<Node, const_node>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Node, class const_node>
	bool	operator==(const ft::bst_const_iterator<Node, const_node>& lhs, const ft::bst_const_iterator<Node, const_node>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Node, class const_node>
	bool	operator!=(const ft::bst_iterator<Node, const_node>& lhs, const ft::bst_iterator<Node, const_node>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<class Node, class const_node>
	bool	operator!=(const ft::bst_iterator<Node, const_node>& lhs, const ft::bst_const_iterator<Node, const_node>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<class Node, class const_node>
	bool	operator!=(const ft::bst_const_iterator<Node, const_node>& lhs, const ft::bst_iterator<Node, const_node>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<class Node, class const_node>
	bool	operator!=(const ft::bst_const_iterator<Node, const_node>& lhs, const ft::bst_const_iterator<Node, const_node>& rhs)
	{ return (lhs.base() != rhs.base()); }
}

#endif