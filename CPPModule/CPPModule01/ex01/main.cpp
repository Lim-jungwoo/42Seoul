/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:05:10 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:05:11 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	std::string	input;
	int			num;
	Zombie		*zom;

	while (1)
	{
		std::cout << "please input the zombie number : ";
		std::getline(std::cin, input);
		if (input == "" || is_number(input) == 0)
			continue ;
		else
			break ;
	}
	num = std::stoi(input);
	std::cout << "please input the zombie name : ";
	std::getline(std::cin, input);
	zom = zombieHorde(num, input);
	for (int i = 0; i < num; i++)
	{
		std::cout << "zombie : ";
		zom[i].announce();
	}
	delete [] zom;
	return (0);
}
