#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../iterator/random_access_iterator.hpp"
# include <memory>
# include <stdexcept>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T																value_type;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::size_type								size_type;
			typedef typename allocator_type::difference_type						difference_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ft::random_access_iterator<value_type>							iterator;
			typedef ft::random_access_const_iterator<value_type, const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_size;
			pointer			_capacity;
		
		public:
			explicit vector(const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _start(NULL), _size(NULL), _capacity(NULL) {}
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				if (n < 0 || n > this->max_size())
					throw (std::length_error("vector"));
				else
				{
					this->_start = this->_alloc.allocate(n);
					this->_size = this->_start;
					this->_capacity = this->_start + n;
					while (n--)
					{
						this->_alloc.construct(this->_size, val);
						this->_size++;
					}
				}
			}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename InputIterator::iterator_category* = NULL) :
				_alloc(alloc)
			{
				size_type	tmp = last - first;
				if (tmp < 0 || tmp > this->max_size())
					throw (std::length_error("vector"));
				else
				{
					this->_start = this->_alloc.allocate(tmp);
					this->_size = this->_start;
					this->_capacity = this->_start + tmp;
					while (tmp--)
					{
						this->_alloc.construct(this->_size, *first);
						this->_size++; first++;
					}
				}
			};

			vector(const vector& x) : _alloc(x._alloc)
			{
				difference_type	tmp = x._size - x._start;
				pointer			val = x._start;
				this->_start = this->_alloc.allocate(tmp);
				this->_size = this->_start;
				this->_capacity = this->_start + tmp;
				while (tmp--)
				{
					this->_alloc.construct(this->_size, *val);
					this->_size++; val++;
				}
			}

			~vector()
			{
				this->clear();
				if (this->_start)
					this->_alloc.deallocate(this->_start, this->capacity());
			}

			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename InputIterator::iterator_category* = NULL)
			{
				size_type	copy_size = last - first;
				if (copy_size > this->max_size() || copy_size < 0)
					throw (std::length_error("vector"));
				this->clear();
				if (copy_size == 0)
					return ;
				if (copy_size <= this->capacity())
				{
					for (size_type i = 0; i < copy_size; i++)
						this->_alloc.construct(this->_size++, *(first + i));
				}
				else
				{
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = this->_alloc.allocate(copy_size);
					this->_size = this->_start;
					this->_capacity = this->_start + copy_size;
					for (size_type i = 0; i < copy_size; i++)
						this->_alloc.construct(this->_size++, *(first + i));
				}
			}

			void	assign(size_type n, const value_type& val)
			{
				this->clear();
				if (n == 0)
					return ;
				if (n <= this->capacity())
				{
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_size++, val);
				}
				else
				{
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = this->_alloc.allocate(n);
					this->_size = this->_start;
					this->_capacity = this->_start + n;
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_size++, val);
				}
			}

			reference	at(size_type n)
			{
				if (n < 0 || this->size() <= n)
					throw (std::out_of_range("vector"));
				return (*this)[n];
			}
			const_reference	at(size_type n) const
			{
				if (n < 0 || this->size() <= n)
					throw (std::out_of_range("vector"));
				return (*this)[n];
			}

			reference		back() { return (*(this->_size - 1)); }
			const_reference	back() const { return (*(this->_size - 1)); }
			iterator		begin() { return (this->_start); }
			const_iterator	begin() const { return (this->_start); }
			size_type		capacity() const { return (this->_capacity - this->_start); }
			void	clear()
			{
				for (size_type i = 0; i < this->size(); i++)
					this->_alloc.destroy(this->_start + i);
				this->_size = this->_start;
			}

			bool	empty() const { return (this->size() == 0 ? true : false); }
			iterator		end() { return (this->_size); }
			const_iterator	end() const { return (this->_size); }

			iterator	erase(iterator position)
			{
				pointer	pos = &(*position);
				size_type	back_part = this->_size - pos - 1;
				this->_alloc.destroy(pos);
				for (size_type i = 0; i < back_part; i++)
				{
					this->_alloc.construct(pos + i, *(pos + i + 1));
					this->_alloc.destroy(pos + i + 1);
				}
				this->_size -= 1;
				return (pos);
			}
			iterator	erase(iterator first, iterator last)
			{
				pointer	pos = &(*first);
				size_type	back_part = this->_size - &(*last);
				for (size_type i = 0; pos + i != &(*last); i++)
					this->_alloc.destroy(pos + i);
				for (size_type i = 0; i < back_part; i++)
				{
					this->_alloc.construct(pos + i , *(&(*last) + i));
					this->_alloc.destroy(&(*last) + i);
				}
				this->_size -= (&(*last) - &(*first));
				return (pos);
			}

			reference		front() { return (*this->_start); }
			const_reference	front() const { return (*this->_start); }
			allocator_type	get_allocator() const { return (this->_alloc); }

			iterator	insert(iterator position, const value_type& val)
			{
				size_type	front_part = &(*position) - this->_start;
				size_type	back_part = this->_size - &(*position);
				if (this->capacity() >= this->size() + 1)
				{
					for (size_type i = 0; i < back_part; i++)
					{
						this->_alloc.construct(this->_size - i, *(this->_size - i - 1));
						this->_alloc.destroy(&(*this->_size) - i - 1);	
					}
					this->_alloc.construct(&(*position), val);
					this->_size++;
				}
				else
				{
					pointer	new_start;
					size_type	capacity_size = (this->capacity() > 0) ? this->capacity() * 2 : 1;
					size_type	insert_position;

					new_start = this->_alloc.allocate(capacity_size);
					for (insert_position = 0; insert_position < front_part; insert_position++)
						this->_alloc.construct(new_start + insert_position, *(this->_start + insert_position));
					this->_alloc.construct(new_start + insert_position++, val);
					
					for ( ; insert_position < this->size() + 1; insert_position++)
						this->_alloc.construct(new_start + insert_position, *(this->_start + insert_position - 1));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_start + i);
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = new_start;
					this->_size = new_start + insert_position;
					this->_capacity = new_start + capacity_size;
				}
				return (this->_start + front_part);
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n < 0 || n + this->size() > this->max_size())
					throw (std::length_error("vector"));
				size_type	front_part = &(*position) - this->_start;
				size_type	back_part = this->_size - &(*position);
				if (this->capacity() >= this->size() + n)
				{
					for (size_type i = 0; i < back_part; i++)
						this->_alloc.construct(this->_size - i + (n - 1), *(this->_size - i - 1));
					this->_size += n;
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(&(*position) + i, val);
				}
				else
				{
					pointer	new_start;
					size_type	capacity_size = (this->capacity() > 0) ? this->capacity() * 2 : 1;
					size_type	insert_position;
					if (capacity_size < this->size() + n)
						capacity_size = this->size() + n;
					new_start = this->_alloc.allocate(capacity_size);
					for (insert_position = 0; insert_position < front_part; insert_position++)
						this->_alloc.construct(new_start + insert_position, *(this->_start + insert_position));
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(new_start + insert_position + i, val);
					for (; insert_position < this->size(); insert_position++)
						this->_alloc.construct(new_start + insert_position + n, *(this->_start + insert_position));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_start + i);
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = new_start;
					this->_size = new_start + insert_position + n;
					this->_capacity = new_start + capacity_size;
				}
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
				typename InputIterator::iterator_category* = NULL)
			{
				size_type	insert_size = last - first;
				if (insert_size <= 0)
					return ;
				size_type	front_part = &(*position) - this->_start;
				size_type	back_part = this->_size - &(*position);
				if (this->capacity() - this->size() >= insert_size)
				{
					for (size_type i = 0; i < back_part; i++)
						this->_alloc.construct(this->_size - i + (insert_size - 1), *(this->_size - i - 1));
					this->_size += insert_size;
					for (size_type i = 0; &(*first) + i != &(*last); i++)
						this->_alloc.construct(&(*position) + i, *(first + i));
				}
				else
				{
					pointer	new_start;
					size_type	capacity_size = (this->capacity() > 0) ? this->capacity() * 2 : 1;
					size_type	insert_position;
					if (capacity_size < this->size() + insert_size)
						capacity_size = this->size() + insert_size;
					new_start = this->_alloc.allocate(capacity_size);
					for (insert_position = 0; insert_position < front_part; insert_position++)
						this->_alloc.construct(new_start + insert_position, *(this->_start + insert_position));
					for (size_type i = 0; i < insert_size; i++)
						this->_alloc.construct(new_start + insert_position + i, *(first + i));
					for (; insert_position < this->size(); insert_position++)
						this->_alloc.construct(new_start + insert_position + insert_size, *(this->_start + insert_position));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_start + i);
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = new_start;
					this->_size = new_start + insert_position + insert_size;
					this->_capacity = new_start + capacity_size;
				}
			}

			size_type	max_size() const { return (allocator_type().max_size()); }
			vector&	operator=(const vector& x)
			{
				if (*this == x)
					return (*this);
				this->assign(x.begin(), x.end());
				return (*this);
			}
			reference		operator[](size_type n) { return *(this->_start + n); }
			const_reference	operator[](size_type n) const { return *(this->_start + n); }

			void	pop_back()
			{
				if (this->_size)
				{
					this->_alloc.destroy(this->_size - 1);
					this->_size--;
				}
			}

			void	push_back(const value_type& val)
			{
				if (this->_size == this->_capacity)
				{
					pointer	new_start;
					size_type	capacity_size = (this->_size == NULL) ? 1 : this->capacity() * 2;
					size_type	insert_position;
					new_start = this->_alloc.allocate(capacity_size);
					for (insert_position = 0; insert_position < this->size(); insert_position++)
						this->_alloc.construct(new_start + insert_position, *(this->_start + insert_position));
					this->_alloc.construct(new_start + insert_position++, val);
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_start + i);
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = new_start;
					this->_size = new_start + insert_position;
					this->_capacity = new_start + capacity_size;
				}
				else
				{
					this->_alloc.construct(this->_size, val);
					this->_size++;
				}
			}

			reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(this->end())); }
			reverse_iterator		rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(this->begin())); }

			void	reserve(size_type n)
			{
				if (n < 0 || n > this->max_size())
					throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
				if (n <= this->capacity())
					return ;
				else
				{
					pointer	new_start;
					size_type	origin_size  = this->size();
					new_start = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.construct(new_start + i, *(this->_start + i));
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_start + i);
					if (this->_start)
						this->_alloc.deallocate(this->_start, this->capacity());
					this->_start = new_start;
					this->_size = new_start + origin_size;
					this->_capacity = new_start + n;
				}
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < 0 || n > this->max_size())
					throw (std::length_error("vector"));
				if (n < this->size())
				{
					while (this->size() > n)
					{
						this->_size--;
						this->_alloc.destroy(this->_size);
					}
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}

			size_type	size() const { return (this->_size - this->_start); }
			void	swap(vector& x)
			{
				if (*this == x)
					return ;
				allocator_type	tmp_alloc = x._alloc;
				pointer			tmp_start = x._start;
				pointer			tmp_size = x._size;
				pointer			tmp_capacity = x._capacity;

				x._alloc = this->_alloc;
				x._start = this->_start;
				x._size = this->_size;
				x._capacity = this->_capacity;
				this->_alloc = tmp_alloc;
				this->_start = tmp_start;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
			}	
	};

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return (!(lhs < rhs)); }

	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{ x.swap(y); }
}

#endif