/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:39:40 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 20:39:41 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

# define f_value1 0
# define f_value2 4
# define f_value3 10
# define index 10

int	main(void)
{
	std::vector<int>	v;
	std::deque<int>	d;
	std::list<int>	l;

	for (int i = 0; i < index; i++)
	{
		d.push_back(i);
		l.push_back(i);
		v.push_back(i);
	}
	
	std::cout << GREEN;
	try
	{
		std::vector<int>::iterator	iter = easyfind(&v, f_value1);
		std::cout << "vector[" << std::distance(std::begin(v), iter) << "]";
		std::cout << " is " << f_value1 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "vector" << std::endl;
	}
	std::cout << YELLOW;
	try
	{
		std::deque<int>::iterator	iter = easyfind(&d, f_value2);
		std::cout << "deque[" << std::distance(std::begin(d), iter) << "]";
		std::cout << " is " << f_value2 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "deque" << std::endl;
	}
	std::cout << PINK;
	try
	{
		std::list<int>::iterator	iter = easyfind(&l, f_value3);
		std::cout << "list[" << std::distance(std::begin(l), iter) << "]";
		std::cout << " is " << f_value3 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "list" << std::endl;
	}
	std::cout << RESET;
	return (0);
}
