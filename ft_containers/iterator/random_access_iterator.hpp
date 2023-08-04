#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "../utils/utils.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, Iterator>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, Iterator>::reference			reference;
		
		private:
			pointer	_random_it;
		
		public:
			random_access_iterator() : _random_it(NULL) {}
			random_access_iterator(pointer ptr) : _random_it(ptr) {}
			random_access_iterator(const random_access_iterator& it) : _random_it(it.base()) {}

			pointer	base() const { return (this->_random_it); }
			random_access_iterator&	operator=(const random_access_iterator& it)
			{
				if (*this == it)
					return (*this);
				this->_random_it = it.base();
				return (*this);
			}
			reference	operator*() const { return (*this->_random_it); }
			random_access_iterator	operator+(difference_type n) const
			{ return (random_access_iterator(this->_random_it + n)); }
			random_access_iterator&	operator++()
			{
				++this->_random_it;
				return (*this);
			}
			random_access_iterator	operator++(int)
			{
				random_access_iterator	temp = *this;
				++(*this);
				return (temp);
			}
			random_access_iterator&	operator+=(difference_type n)
			{
				this->_random_it += n;
				return (*this);
			}
			random_access_iterator	operator-(difference_type n) const
			{ return (random_access_iterator(this->_random_it - n)); }
			random_access_iterator&	operator--()
			{
				--this->_random_it;
				return (*this);
			}
			random_access_iterator	operator--(int)
			{
				random_access_iterator	temp = *this;
				--(*this);
				return (temp);
			}
			random_access_iterator&	operator-=(difference_type n)
			{
				this->_random_it -= n;
				return (*this);
			}
			pointer	operator->() { return &(operator*()); }
			reference	operator[](difference_type n) { return (this->base()[n]); }
	};

	template <class Iterator, class const_Iterator = const Iterator>
	class random_access_const_iterator : ft::iterator<ft::random_access_iterator_tag, Iterator>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, const_Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, const_Iterator>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, const_Iterator>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, const_Iterator>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, const_Iterator>::reference			reference;
		
		private:
			pointer	_random_const_it;
		
		public:
			random_access_const_iterator() : _random_const_it(NULL) {}
			random_access_const_iterator(pointer ptr) : _random_const_it(ptr) {}
			random_access_const_iterator(const random_access_const_iterator& cit) : _random_const_it(cit.base()) {}
			random_access_const_iterator(const random_access_iterator<Iterator>& it) :
				_random_const_it(it.base()) {}

			pointer	base() const { return (this->_random_const_it); }
			random_access_const_iterator&	operator=(const random_access_const_iterator& cit)
			{
				if (*this == cit)
					return (*this);
				this->_random_const_it = cit.base();
				return (*this);
			}
			random_access_const_iterator&	operator=(const random_access_iterator<Iterator>& it)
			{
				if (*this == it)
					return (*this);
				this->_random_const_it = it.base();
				return (*this);
			}
			reference	operator*() const { return (*this->_random_const_it); }
			random_access_const_iterator	operator+(difference_type n) const
			{ return (random_access_const_iterator(this->_random_const_it + n)); }
			random_access_const_iterator&	operator++()
			{
				++this->_random_const_it;
				return (*this);
			}
			random_access_const_iterator	operator++(int)
			{
				random_access_const_iterator	temp = *this;
				++(*this);
				return (temp);
			}
			random_access_const_iterator&	operator+=(difference_type n)
			{
				this->_random_const_it += n;
				return (*this);
			}
			random_access_const_iterator	operator-(difference_type n) const
			{ return (random_access_const_iterator(this->_random_const_it - n)); }
			random_access_const_iterator&	operator--()
			{
				--this->_random_const_it;
				return (*this);
			}
			random_access_const_iterator	operator--(int)
			{
				random_access_const_iterator	temp = *this;
				--(*this);
				return (temp);
			}
			random_access_const_iterator&	operator-=(difference_type n)
			{
				this->_random_const_it -= n;
				return (*this);
			}
			pointer	operator->() { return &(operator*()); }
			reference	operator[](difference_type n) { return (this->base()[n]); }
	};

	template <class Iterator>
	bool	operator==(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator1>
	bool	operator==(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator1>
	bool	operator==(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator1>
	bool	operator==(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <class Iterator>
	bool	operator!=(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator1>
	bool	operator!=(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator1>
	bool	operator!=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator1>
	bool	operator!=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <class Iterator>
	bool	operator<(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Iterator1>
	bool	operator<(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Iterator1>
	bool	operator<(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Iterator1>
	bool	operator<(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <class Iterator>
	bool	operator<=(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator1>
	bool	operator<=(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator1>
	bool	operator<=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator1>
	bool	operator<=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <class Iterator>
	bool	operator>(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator1>
	bool	operator>(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator1>
	bool	operator>(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator1>
	bool	operator>(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <class Iterator>
	bool	operator>=(const ft::random_access_iterator<Iterator>& lhs,
		const ft::random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Iterator1>
	bool	operator>=(const ft::random_access_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Iterator1>
	bool	operator>=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_iterator<Iterator1>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class Iterator1>
	bool	operator>=(const ft::random_access_const_iterator<Iterator1>& lhs,
		const ft::random_access_const_iterator<Iterator1>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <class T>
	ft::random_access_iterator<T>	operator+(
		typename ft::random_access_iterator<T>::difference_type n,
		typename ft::random_access_iterator<T>& random_it)
	{ return (&(*random_it) + n); }

	template <class T>
	ft::random_access_const_iterator<T>	operator+(
		typename ft::random_access_const_iterator<T>::difference_type n,
		typename ft::random_access_const_iterator<T>& random_it)
	{ return (&(*random_it) + n); }

	template <class T>
	typename ft::random_access_iterator<T>::difference_type	operator-(
		const ft::random_access_iterator<T>& lhs, const ft::random_access_iterator<T>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class T>
	typename ft::random_access_iterator<T>::difference_type	operator-(
		const ft::random_access_iterator<T>& lhs, const ft::random_access_const_iterator<T>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class T>
	typename ft::random_access_iterator<T>::difference_type	operator-(
		const ft::random_access_const_iterator<T>& lhs, const ft::random_access_iterator<T>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template <class T>
	typename ft::random_access_const_iterator<T>::difference_type	operator-(
		const ft::random_access_const_iterator<T>& lhs, const ft::random_access_const_iterator<T>& rhs)
	{ return (lhs.base() - rhs.base()); }
}

#endif