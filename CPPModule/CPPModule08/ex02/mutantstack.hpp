/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:39:43 by jlim              #+#    #+#             */
/*   Updated: 2022/03/01 09:39:44 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

template <typename T, class Container = std::deque<T> >
class MutantStack : public std::stack<T>
{
public:
	MutantStack(void) {}
	~MutantStack(void) {}
	MutantStack(const MutantStack& m)
	{
		*this = m;
	}

	MutantStack&	operator=(const MutantStack& m)
	{
		if (this == &m)
			return (*this);
		std::stack<T>::operator=(m);
		return (*this);
	}
	
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator	reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

	iterator	begin(void)
	{
		return (this->c.begin());
	}

	iterator	end(void)
	{
		return (this->c.end());
	}

	const_iterator	cbegin(void) const
	{
		return (this->c.cbegin());
	}

	const_iterator	cend(void) const
	{
		return (this->c.cend());
	}

	reverse_iterator	rbegin(void)
	{
		return (this->c.rbegin());
	}

	reverse_iterator	rend(void)
	{
		return (this->c.rend());
	}

	const_reverse_iterator	crbegin(void) const
	{
		return (this->c.crbegin());
	}

	const_reverse_iterator	crend(void) const
	{
		return (this->c.crend());
	}
};

#endif
