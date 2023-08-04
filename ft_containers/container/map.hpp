#ifndef MAP_HPP
# define MAP_HPP

# include "avl.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator==(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);

		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator!=(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);
		
		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator<(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);

		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator<=(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);
		
		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator>(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);

		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator>=(const map<_Key, _T, _Compare, _Alloc>& lhs,
			const map<_Key, _T, _Compare, _Alloc>& rhs);
		
		public:
			typedef Key																									key_type;
			typedef T																									mapped_type;
			typedef ft::pair<const key_type, mapped_type>																value_type;
			typedef Compare																								key_compare;
			typedef Alloc																								allocator_type;
			typedef typename allocator_type::reference																	reference;
			typedef typename allocator_type::const_reference															const_reference;
			typedef typename allocator_type::pointer																	pointer;
			typedef typename allocator_type::const_pointer																const_pointer;
			typedef typename ft::bst<value_type, key_type, mapped_type, key_compare, allocator_type>::iterator			iterator;
			typedef typename ft::bst<value_type, key_type, mapped_type, key_compare, allocator_type>::const_iterator	const_iterator;
			typedef typename ft::reverse_iterator<iterator>																reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>														const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type												difference_type;
			typedef size_t																								size_type;
		
		private:
			allocator_type														_alloc;
			key_compare															_comp;
			bst<value_type, key_type, mapped_type, key_compare, allocator_type>	_bst;
		
		public:
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, allocator_type>;

				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				
				public:
					bool	operator()(const value_type& x, const value_type& y) const
					{ return (this->comp(x.first, y.first)); }
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _bst() {}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(), typename InputIterator::iterator_category* = NULL) :
				_alloc(alloc), _comp(comp), _bst()
			{
				this->insert(first, last);
			}

			map(const map& x) : _alloc(x._alloc), _comp(x._comp), _bst()
			{
				this->insert(x.begin(), x.end());
			}

			~map()
			{
				this->clear();
				this->_bst.node_alloc.destroy(this->_bst.last_node);
				this->_bst.node_alloc.deallocate(this->_bst.last_node, 1);
			}

			iterator	begin()
			{ return (iterator(this->_bst.begin())); }
			const_iterator	begin() const
			{ return (const_iterator(this->_bst.begin())); }

			void	clear()
			{ this->_bst.clear(); }
			size_type	count(const key_type& k) const
			{
				if (this->find(k) == this->end())
					return (0);
				return (1);
			}

			bool	empty() const
			{ return (this->_bst.count_node == 0); }
			iterator	end()
			{ return (iterator(this->_bst.end())); }
			const_iterator	end() const
			{ return (const_iterator(this->_bst.end())); }

			ft::pair<iterator, iterator>	equal_range(const key_type& k)
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			void	erase(iterator position)
			{ this->erase((*position).first); }
			size_type	erase(const key_type& k)
			{ return (this->_bst.erase(k)); }
			void	erase(iterator first, iterator last)
			{ this->_bst.erase(first, last); }

			iterator	find(const key_type& k)
			{ return (this->_bst.find(k)); }
			const_iterator	find(const key_type& k) const
			{ return (this->_bst.find(k)); }

			allocator_type	get_allocator() const { return (this->_alloc); }

			ft::pair<iterator, bool>	insert(const value_type& val)
			{ return (this->_bst.insert(val)); }
			iterator	insert(iterator position, const value_type& val)
			{
				position++; position--;
				return (this->insert(val).first);
			}
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last,
				typename InputIterator::iterator_category* = NULL)
			{
				size_type	n = ft::distance(first, last);
				while (n--)
					this->insert(*(first++));
			}

			key_compare key_comp() const
			{ return (key_compare()); }

			iterator	lower_bound(const key_type& k)
			{
				iterator	begin = this->begin();
				iterator	end = this->end();
				while (begin != end)
				{
					if (this->_bst.comp((*begin).first, k) == false)
						break ;
					begin++;
				}
				return (begin);
			}
			const_iterator	lower_bound(const key_type& k) const
			{
				const_iterator	begin = this->begin();
				const_iterator	end = this->end();
				while (begin != end)
				{
					if (this->_bst.comp((*begin).first, k) == false)
						break ;
					begin++;
				}
				return (begin);
			}

			size_type	max_size() const
			{ return (allocator_type().max_size()); }

			map&	operator=(const map& x)
			{
				if (*this == x)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}
			mapped_type&	operator[](const key_type& k)
			{
				iterator	temp = this->find(k);
				if (temp == this->end())
				{
					this->insert(ft::make_pair(k, mapped_type()));
					temp = this->find(k);
					return ((*temp).second);
				}	
				return ((*temp).second);
			}

			reverse_iterator	rbegin()
			{ return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin() const
			{ return (const_reverse_iterator(this->end())); }
			reverse_iterator	rend()
			{ return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend() const
			{ return (const_reverse_iterator(this->begin())); }

			size_type	size() const
			{ return (this->_bst.count_node); }

			void	swap(map& x)
			{ this->_bst.swap(x._bst); }

			iterator	upper_bound(const key_type& k)
			{
				iterator	begin = this->begin();
				iterator	end = this->end();
				while (begin != end)
				{
					if (this->_bst.comp(k, (*begin).first))
						break ;
					begin++;
				}
				return (begin);
			}
			const_iterator	upper_bound(const key_type& k) const
			{
				const_iterator	begin = this->begin();
				const_iterator	end = this->end();
				while (begin != end)
				{
					if (this->_bst.comp(k, (*begin).first))
						break ;
					begin++;
				}
				return (begin);
			}

			value_compare	value_comp() const
			{ return (value_compare(key_compare())); }
	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs._bst.count_node != rhs._bst.count_node)
			return (false);
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	l_itb = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	l_ite = lhs.end();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	r_itb = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	r_ite = rhs.end();
		while (l_itb != l_ite)
		{
			if (l_itb->first != r_itb->first)
				return (false);
			if (l_itb->second != r_itb->second)
				return (false);
			l_itb++; r_itb++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	l_itb = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	l_ite = lhs.end();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	r_itb = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator	r_ite = rhs.end();
		while (l_itb != l_ite)
		{
			if (r_itb == r_ite)
				return (false);
			if (l_itb->first < r_itb->first)
				return (true);
			else if (l_itb->first > r_itb->first)
				return (false);
			if (l_itb->second < r_itb->second)
				return (true);
			else if (l_itb->second > r_itb->second)
				return (false);
			l_itb++; r_itb++;
		}
		return (r_itb != r_ite);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{ return (rhs < lhs); }
	
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }
	
	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{ x.swap(y); }
}

#endif