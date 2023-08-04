#ifndef AVL_HPP
# define AVL_HPP

# include "../iterator/bst_iterator.hpp"
# include <memory>

namespace ft
{
	template <class T>
	struct bst_node
	{
		public:
			typedef T	value_type;
			
			value_type*	value;
			bst_node*	parent;
			bst_node*	left;
			bst_node*	right;
			size_t		height;

			bst_node() :
				value(NULL), parent(NULL), left(NULL), right(NULL), height(0) {}
			bst_node(const bst_node& bst) :
				value(bst.value), parent(bst.parent), left(bst.left), right(bst.right), height(bst.height) {}
			
			~bst_node() {}

			bst_node&	operator=(const bst_node& bst)
			{
				if (bst == *this)
					return (*this);
				this->value = bst.value; this->parent = bst.parent;
				this->left = bst.left; this->right = bst.right;
				this->height = bst.height;
				return (*this);
			}
			bool	operator==(const bst_node& bst)
			{
				if (this->value == bst.value)
					return (true);
				return (false);
			}
	};

	template <class T, class Key, class Map, class Compare = ft::less<Key>, class Alloc = std::allocator<T>,
		class Node = ft::bst_node<T> >
	class bst
	{
		public:
			typedef T																	value_type;
			typedef Key																	key_type;
			typedef Node																node_type;
			typedef ft::bst_node<ft::pair<const Key, const Map> >						const_node;
			typedef Compare																key_compare;
			typedef Alloc																allocator_type;
			typedef ft::bst<value_type, key_type, key_compare, allocator_type, Node>	bst_type;
			typedef ft::bst_iterator<Node, const_node>									iterator;
			typedef ft::bst_const_iterator<Node, const_node>							const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef size_t																size_type;
			typedef typename Alloc::template rebind<ft::bst_node<value_type> >::other	node_allocator;

			node_type*		root_node;
			node_type*		last_node;
			size_type		count_node;
			allocator_type	value_alloc;
			node_allocator	node_alloc;
			key_compare		comp;

			bst(const allocator_type& va = allocator_type(), const node_allocator& na = node_allocator(),
				const key_compare& comp = key_compare()) :
				value_alloc(va), node_alloc(na), comp(comp)
			{
				this->last_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(this->last_node, Node());
				this->root_node = NULL;
				this->count_node = 0;
			}

			bst(value_type& val, const allocator_type& va = allocator_type(),
				const node_allocator& na = node_allocator(), const key_compare& comp = key_compare()) :
				value_alloc(va), node_alloc(na), comp(comp)
			{
				this->root_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(this->root_node, Node());
				this->root_node->height = 1;
				this->root_node->value = this->value_alloc.allocate(1);
				this->value_alloc.construct(this->root_node->value, val);
				this->last_node = this->node_alloc.allocate(1);
				this->node_alloc.construct(this->last_node, Node());
				this->last_node->left = this->root_node;
				this->root_node->right = this->last_node;
				this->count_node = 1;
			}

			~bst() {}
			
			iterator	begin()
			{
				node_type*	ret = this->find_min();
				if (ret == NULL)
					return (this->end());
				return (iterator(ret, this->last_node));
			}
			const_iterator	begin() const
			{
				node_type*	ret = this->find_min();
				if (ret == NULL)
					return (this->end());
				return (const_iterator(ret, this->last_node));
			}

			void	clear()
			{
				this->erase(this->begin(), this->end());
			}

			iterator	end()
			{
				node_type*	temp = this->last_node;
				return (iterator(temp, this->last_node));
			}
			const_iterator	end() const
			{
				node_type*	temp = this->last_node;
				return (const_iterator(temp, this->last_node));
			}

			size_type	erase(const key_type& k)
			{
				iterator	erase_pos = this->find(k);
				if (erase_pos == this->end())
					return (0);
				this->count_node--;
				this->free_node(erase_pos.base());
				if (this->count_node == 0)
					this->root_node = NULL;
				return (1);
			}
			void	erase(iterator first, iterator last)
			{
				if (this->root_node == NULL)
					return ;
				while (first != last)
					this->erase((*(first++)).first);
			}

			void	free_height(node_type* nod)
			{
				node_type*	parent_node = nod;
				while (parent_node)
				{
					if (get_height(parent_node->left) + 1 != get_height(parent_node) &&
						get_height(parent_node->right) + 1 != get_height(parent_node))
						parent_node->height -= 1;
					parent_node = parent_node->parent;
				}
			}

			void	free_height_rotatation(node_type* nod)
			{
				node_type	*parent_node = nod;
				while (parent_node)
				{
					if (get_bf(parent_node) > 1)
					{
						if (get_bf(parent_node->left) == -1)
						{
							parent_node->height -= 2;
							parent_node->left->height--;
							parent_node->left->right->height++;
							left_rotation(parent_node->left);
							right_rotation(parent_node);
							free_height(parent_node);
						}
						else if (get_bf(parent_node->left) == 1)
						{
							parent_node->height -= 2;
							right_rotation(parent_node);
							free_height(parent_node);
						}
						else if (get_bf(parent_node->left) == 0)
						{
							parent_node->height -= 1;
							parent_node->left->height += 1;
							right_rotation(parent_node);
							free_height(parent_node);
						}
					}
					else if (get_bf(parent_node) < -1)
					{
						if (get_bf(parent_node->right) == -1)
						{
							parent_node->height -= 2;
							left_rotation(parent_node);
							free_height(parent_node);
						}
						else if (get_bf(parent_node->right) == 1)
						{
							parent_node->height -= 2;
							parent_node->right->height -= 1;
							parent_node->right->left->height++;
							right_rotation(parent_node->right);
							left_rotation(parent_node);
							free_height(parent_node);
						}
						else if (get_bf(parent_node->right) == 0)
						{
							parent_node->height -= 1;
							parent_node->right->height += 1;
							left_rotation(parent_node);
							free_height(parent_node);
						}
					}
					parent_node = parent_node->parent;
				}
			}

			void	free_node(node_type* nod)
			{
				node_type*	change_node = nod;
				node_type*	free_pos = nod;
				node_type*	rotate;
				if (this->last_node->left == nod)
				{
					nod->right = NULL;
					this->last_node->left = NULL;
				}
				
				if (change_node->left == NULL && change_node->right == NULL)
				{
					if (change_node == this->root_node)
						this->root_node = NULL;
					if (change_node->parent)
					{
						if (change_node->parent->left == change_node)
							change_node->parent->left = NULL;
						else if (change_node->parent->right == change_node)
							change_node->parent->right = NULL;
					}
					
					free_height(change_node->parent);
					free_height_rotatation(change_node->parent);
					if (this->last_node->left == NULL && this->root_node != NULL)
					{
						free_pos->parent->right = this->last_node;
						this->last_node->left = free_pos->parent;
					}
				}
				else if (change_node->left != NULL)
				{
					change_node = change_node->left;
					while (change_node->right)
						change_node = change_node->right;
					if (change_node->parent->left == change_node)
						change_node->parent->left = change_node->left;
					else if (change_node->parent->right == change_node)
						change_node->parent->right = change_node->left;
					if (change_node->left)
						change_node->left->parent = change_node->parent;

					free_height(change_node->parent);
					if (change_node->parent != free_pos)
						rotate = change_node->parent; 
					else
						rotate = change_node;
					change_node->parent = free_pos->parent;
					if (free_pos->parent)
					{
						if (free_pos->parent->left == free_pos)
							free_pos->parent->left = change_node;
						else if (free_pos->parent->right == free_pos)
							free_pos->parent->right = change_node;
					}
					change_node->left = free_pos->left;
					if (free_pos->left)
						free_pos->left->parent = change_node;
					change_node->right = free_pos->right;
					if (free_pos->right)
						free_pos->right->parent = change_node;
					change_node->height = free_pos->height;

					if (free_pos == this->root_node)
						this->root_node = change_node;

					free_height_rotatation(rotate);
					if (this->last_node->left == NULL)
					{
						this->last_node->left = change_node;
						change_node->right = this->last_node;
					}
				}
				else if (change_node->left == NULL && change_node->right != NULL)
				{
					change_node = change_node->right;
					change_node->parent->right = change_node->right;
	
					if (change_node->right && change_node->right != this->last_node)
						change_node->right->parent = change_node->parent;
					else if (change_node->right == this->last_node)
						change_node->right->left = change_node->parent;

					free_height(change_node->parent);
					
					change_node->parent = free_pos->parent;
					if (free_pos->parent)
					{
						if (free_pos->parent->left == free_pos)
							free_pos->parent->left = change_node;
						else if (free_pos->parent->right == free_pos)
							free_pos->parent->right = change_node;
					}
					change_node->left = NULL;
					change_node->right = free_pos->right;
					if (free_pos->right && free_pos->right != this->last_node)
						free_pos->right->parent = change_node;
					else if (free_pos->right == this->last_node)
						free_pos->right->left = change_node;

					if (free_pos == this->root_node)
						this->root_node = change_node;
					free_height_rotatation(change_node);
				}
				this->value_alloc.destroy(free_pos->value);
				this->value_alloc.deallocate(free_pos->value, 1);
				this->node_alloc.destroy(free_pos);
				this->node_alloc.deallocate(free_pos, 1);
			}

			iterator	find(const key_type& k)
			{
				node_type*	temp = this->root_node;
				while (temp)
				{
					if (temp->value->first == k)
						return (iterator(temp, this->last_node));
					else if (comp(temp->value->first, k))
					{
						if (temp->right && temp->right != this->last_node)
							temp = temp->right;
						else
							return (this->end());
					}
					else
					{
						if (temp->left)
							temp = temp->left;
						else
							return (this->end());
					}
				}
				return (this->end());
			}
			const_iterator	find(const key_type& k) const
			{
				node_type*	temp = this->root_node;
				while (temp)
				{
					if (temp->value->first == k)
						return (const_iterator(temp, this->last_node));
					else if (comp(temp->value->first, k))
					{
						if (temp->right && temp->right != this->last_node)
							temp = temp->right;
						else
							return (this->end());
					}
					else
					{
						if (temp->left)
							temp = temp->left;
						else
							return (this->end());
					}
				}
				return (this->end());
			}

			node_type*	find_min() const
			{
				node_type*	ret = this->root_node;
				while (ret)
				{
					if (ret->left)
						ret = ret->left;
					else
						break ;
				}
				return (ret);
			}

			void	left_rotation(node_type* nod)
			{
				node_type*	right = nod->right;
				if (nod->right == NULL || nod->right == this->last_node)
					return ;
				right->parent = nod->parent;
				if (nod->parent)
				{
					if (nod->parent->right == nod)
						nod->parent->right = right;
					else if (nod->parent->left == nod)
						nod->parent->left = right;
				}
				nod->parent = right;
				nod->right = right->left;
				if (right->left)
					right->left->parent = nod;
				right->left = nod;

				if (nod == this->root_node)
					this->root_node = right;
			}

			void	right_rotation(node_type* nod)
			{
				node_type*	left = nod->left;
				if (left == NULL)
					return ;
				left->parent = nod->parent;
				if (nod->parent)
				{
					if (nod->parent->right == nod)
						nod->parent->right = left;
					else if (nod->parent->left == nod)
						nod->parent->left = left;
				}
				nod->parent = left;
				nod->left = left->right;
				if (left->right)
					left->right->parent = nod;
				left->right = nod;
				
				if (nod == this->root_node)
					this->root_node = left;
			}

			size_t	get_height(node_type* nod)
			{
				if (nod == NULL || nod == this->last_node)
					return (0);
				return (nod->height);
			}

			int	get_bf(node_type* nod)
			{
				int	ret = get_height(nod->left) - get_height(nod->right);
				return (ret);
			}

			void	insert_rotation(node_type* nod, node_type* insert_node)
			{
				node_type*	parent_node = nod;
				while (parent_node)
				{
					if (get_height(parent_node->left) == get_height(parent_node) ||
						get_height(parent_node->right) == get_height(parent_node))
						parent_node->height++;
					
					if (get_bf(parent_node) > 1)
					{
						if (comp(parent_node->left->value->first, insert_node->value->first))
						{
							parent_node->height -= 2;
							parent_node->left->height--;
							if (insert_node->parent == parent_node->left)
								insert_node->height++;
							else
								parent_node->left->right->height++;
							left_rotation(parent_node->left);
							right_rotation(parent_node);
						}
						else if (!comp(parent_node->left->value->first, insert_node->value->first))
						{
							parent_node->height -=2;
							right_rotation(parent_node);
						}
						break ;
					}
					else if (get_bf(parent_node) < -1)
					{
						if (comp(parent_node->right->value->first, insert_node->value->first))
						{
							parent_node->height -= 2;
							left_rotation(parent_node);
						}
						else if (!comp(parent_node->right->value->first, insert_node->value->first))
						{
							parent_node->height -= 2;
							parent_node->right->height--;
							if (insert_node->parent == parent_node->right)
								insert_node->height++;
							else
								parent_node->right->left->height++;
							right_rotation(parent_node->right);
							left_rotation(parent_node);
						}
						break ;
					}
					parent_node = parent_node->parent;
				}
			}

			ft::pair<iterator, bool>	insert(const value_type& val)
			{
				iterator	k_position = this->find(val.first);
				node_type*	insert_node = this->last_node;
				node_type*	insert_pos = this->root_node;
				node_type*	max = NULL;
				if (k_position == this->end())
				{
					insert_node->value = this->value_alloc.allocate(1);
					this->value_alloc.construct(insert_node->value, val);
					insert_node->height = 1;
					if (this->root_node)
					{
						max = this->last_node->left;
						if (comp(max->value->first, val.first))
							max = insert_node;
						this->last_node->left->right = NULL;
					}
					else if (this->root_node == NULL)
					{
						this->root_node = insert_node;
						insert_pos = NULL;
					}

					this->last_node->left = NULL;
					this->last_node->right = NULL;
					this->last_node->parent = NULL;
					this->last_node = NULL;

					while (insert_pos)
					{
						if (comp(insert_pos->value->first, val.first))
						{
							if (insert_pos->right)
								insert_pos = insert_pos->right;
							else
							{
								insert_pos->right = insert_node;
								insert_node->parent = insert_pos;
								insert_rotation(insert_pos, insert_node);
								break ;
							}
						}
						else if (!comp(insert_pos->value->first, val.first))
						{
							if (insert_pos->left)
								insert_pos = insert_pos->left;
							else
							{
								insert_pos->left = insert_node;
								insert_node->parent = insert_pos;
								insert_rotation(insert_pos, insert_node);
								break ;
							}
						}
					}
					
					this->last_node = this->node_alloc.allocate(1);
					this->node_alloc.construct(this->last_node, Node());
					if (max != NULL)
					{
						max->right = this->last_node;
						this->last_node->left = max;
					}
					else if (max == NULL)
					{
						this->root_node->right = this->last_node;
						this->last_node->left = this->root_node;
					}
					this->count_node++;
					return (ft::pair<iterator, bool>(iterator(insert_node, this->last_node), true));
				}
				return (ft::pair<iterator, bool>(k_position, false));
			}

			void	swap(bst<T, Key, Map, Compare, Alloc, Node>& x)
			{
				node_type*	tmp_root = x.root_node;
				node_type*	tmp_last = x.last_node;
				size_type	tmp_count = x.count_node;
				allocator_type	tmp_value_alloc = x.value_alloc;
				node_allocator	tmp_node_alloc = x.node_alloc;
				key_compare	tmp_compare = x.comp;
				x.root_node = this->root_node;
				x.last_node = this->last_node;
				x.count_node = this->count_node;
				x.value_alloc = this->value_alloc;
				x.node_alloc = this->node_alloc;
				x.comp = this->comp;
				this->root_node = tmp_root;
				this->last_node = tmp_last;
				this->count_node = tmp_count;
				this->value_alloc = tmp_value_alloc;
				this->node_alloc = tmp_node_alloc;
				this->comp = tmp_compare;
			}
	};
}

#endif