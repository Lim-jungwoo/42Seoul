/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:06:35 by jlim              #+#    #+#             */
/*   Updated: 2022/03/03 10:34:16 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutantstack.hpp"

int	main(void)
{
	//default test
	std::cout << GREEN;
	MutantStack<int>	mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << "top : " << mstack.top() << std::endl;
	std::cout << "pop!!" << std::endl;
	mstack.pop();

	std::cout << "size : " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//...
	mstack.push(0);

	MutantStack<int>::iterator	it = mstack.begin();
	MutantStack<int>::iterator	ite = mstack.end();

	++it;
	--it;
	std::cout << "iterator==================" << std::endl;
	while (it != ite)
	{
		if (it == ite-1)
			*it = 9;
		std::cout << *it << " ";
		++it;
	}
	std::stack<int>	s(mstack);
	std::cout << "top : " << s.top() << std::endl;

	std::cout << PINK;
	MutantStack<int>::reverse_iterator	r_it = mstack.rbegin();
	MutantStack<int>::reverse_iterator	r_ite = mstack.rend();

	std::cout << "reverse_iterator==================" << std::endl;
	while (r_it != r_ite)
	{
		std::cout << *r_it << " ";
		++r_it;
	}
	std::cout << std::endl;

	std::cout << RED;
	MutantStack<int>::const_iterator	c_it = mstack.cbegin();
	MutantStack<int>::const_iterator	c_ite = mstack.cend();

	std::cout << "const_iterator==================" << std::endl;
	while (c_it != c_ite)
	{
		//if (c_it == c_ite - 1)
		//	*c_it = 10;
		std::cout << *c_it << " ";
		++c_it;
	}
	std::cout << std::endl;

	std::cout << BLUE;
	MutantStack<int>::const_reverse_iterator	cr_it = mstack.crbegin();
	MutantStack<int>::const_reverse_iterator	cr_ite = mstack.crend();

	std::cout << "const_reverse_iterator==================" << std::endl;
	while (cr_it != cr_ite)
	{
		std::cout << *cr_it << " ";
		++cr_it;
	}
	std::cout << std::endl;

	return (0);
}
