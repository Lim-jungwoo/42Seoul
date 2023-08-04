#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T					value_type;
		typedef Distance			difference_type;
		typedef Pointer				pointer;
		typedef Reference			reference;
		typedef Category			iterator_category;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <bool is_iter, class T>
	struct iterator_tag
	{
		typedef T			type;
		static const bool	value = is_iter;
	};

	template <class T>
	struct is_iterator_tag : public iterator_tag<false, T> {};

	template <>
	struct is_iterator_tag<ft::input_iterator_tag> :
		public iterator_tag<true, ft::input_iterator_tag> {};

	template <>
	struct is_iterator_tag<ft::output_iterator_tag> :
		public iterator_tag<true, ft::output_iterator_tag> {};

	template <>
	struct is_iterator_tag<ft::forward_iterator_tag> :
		public iterator_tag<true, ft::forward_iterator_tag> {};

	template <>
	struct is_iterator_tag<ft::bidirectional_iterator_tag> :
		public iterator_tag<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct is_iterator_tag<ft::random_access_iterator_tag> :
		public iterator_tag<true, ft::random_access_iterator_tag> {};
}

# endif