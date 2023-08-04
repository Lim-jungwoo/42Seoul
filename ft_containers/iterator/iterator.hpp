#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class InputIterator>
	void	_advance(InputIterator& it, typename ft::iterator_traits<InputIterator>::difference_type n,
		ft::input_iterator_tag)
	{
		for (typename ft::iterator_traits<InputIterator>::difference_type i = 0; i < n; i++)
			++it;
	}

	template <class InputIterator>
	void	_advance(InputIterator& it, typename ft::iterator_traits<InputIterator>::difference_type n,
		ft::output_iterator_tag)
	{
		for (typename ft::iterator_traits<InputIterator>::difference_type i = 0; i < n; i++)
			++it;
	}

	template <class InputIterator>
	void	_advance(InputIterator& it, typename ft::iterator_traits<InputIterator>::difference_type n,
		ft::forward_iterator_tag)
	{
		for (typename ft::iterator_traits<InputIterator>::difference_type i = 0; i < n; i++)
			++it;
	}

	template <class InputIterator>
	void	_advance(InputIterator& it, typename ft::iterator_traits<InputIterator>::difference_type n,
		ft::bidirectional_iterator_tag)
	{
		for (typename ft::iterator_traits<InputIterator>::difference_type i = 0; i < n; i++)
			++it;
	}

	template <class InputIterator>
	void	_advance(InputIterator& it, typename ft::iterator_traits<InputIterator>::difference_type n,
		ft::random_access_iterator_tag)
	{
		it += n;
	}

	template <class InputIterator, class Distance>
	void	advance(InputIterator& it, Distance n,
		typename InputIterator::iterator_category* = NULL)
	{
		ft::_advance(it, n, typename ft::iterator_traits<InputIterator>::iterator_category());
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last,
		ft::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	tmp = 0;
		while (first != last)
		{
			++first; ++tmp;
		}
		return (tmp);
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last,
		ft::output_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	tmp = 0;
		while (first != last)
		{
			++first; ++tmp;
		}
		return (tmp);
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last,
		ft::forward_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	tmp = 0;
		while (first != last)
		{
			++first; ++tmp;
		}
		return (tmp);
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last,
		ft::bidirectional_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	tmp = 0;
		while (first != last)
		{
			++first; ++tmp;
		}
		return (tmp);
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last,
		ft::random_access_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	tmp = 0;
		while (first != last)
		{
			++first; ++tmp;
		}
		return (tmp);
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	distance(
			InputIterator first, InputIterator last,
			typename InputIterator::iterator_category* = NULL)
	{
		return (ft::_distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category()));
	}
}

#endif