/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:39:52 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 20:39:52 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <deque>
# include <iostream>
# include <list>
# include <string>
# include <vector>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

class NoValueException : public std::exception {
	const char* what(void) const throw() {
		return ("There is no value in ");
	}
};

template <typename T>
typename T::iterator easyfind(T* container, int value)
{
	typename T::iterator	iter = std::find(std::begin(*container), std::end(*container), value);
	if (iter == std::end(*container))
		throw NoValueException();
	return (iter);
}

#endif