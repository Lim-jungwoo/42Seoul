/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:42:12 by jlim              #+#    #+#             */
/*   Updated: 2022/03/01 17:42:12 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

#define MAX 10000

int	main(void)
{
	//default test
	std::cout << GREEN;
	Span	sp = Span(5);

	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "sp's shortestSpan : " << sp.shortestSpan() << std::endl;
	std::cout << "sp's longestSpan : " << sp.longestSpan() << std::endl;
	

	//max test
	std::cout << YELLOW;
	Span	sp_max = Span(MAX);
	int		i_max[MAX];

	for (int i = 0; i < MAX; i++)
		i_max[i] = i;
	try
	{
		sp_max.addRange(std::begin(i_max), std::end(i_max));
		std::cout << "sp_max's shortestSpan : " << sp_max.shortestSpan() << std::endl;
		std::cout << "sp_max's shortestSpan : " << sp_max.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	//no_space test
	std::cout << PINK;
	try
	{
		Span	no_space = Span(MAX);
		std::vector<int>	v_no_space;

		for (int i = 0; i < MAX; i++)
			v_no_space.push_back(i);
		no_space.addRange(std::begin(v_no_space), std::end(v_no_space));
		//no_space.addNumber(1);
		std::cout << "no_space's shortestSpan : " << no_space.shortestSpan() << std::endl;
		std::cout << "no_space's shortestSpan : " << no_space.longestSpan() << std::endl;
		std::cout << "no_space success!!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	//no_span test
	std::cout << CYAN;
	try
	{
		Span	no_span = Span(1);
		
		no_span.addNumber(1);
		std::cout << "no_span's shortestSpan : " << no_span.shortestSpan() << std::endl;
		std::cout << "no_span's longestSpan : " << no_span.longestSpan() << std::endl;
		std::cout << "no_span success!!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << RESET;

	return (0);
}
