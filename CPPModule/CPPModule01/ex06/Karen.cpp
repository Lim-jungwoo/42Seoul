/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:49:35 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 15:49:36 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

void	Karen::debug(void)
{
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger.\nI just love it!" << std::endl;
}

void	Karen::info(void)
{
	std::cout << "I cannot believe adding extra bacon cost more money.\nYou don't put enough! If you did I would not have to ask for it!" << std::endl;
}

void	Karen::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free.\nI've been coming here for years and you just started working here last month." << std::endl;
}

void	Karen::error(void)
{
	std::cout << "This is unacceptable, I want to speak to the manager now." << std::endl;
}

void	Karen::complain(std::string level)
{
	std::string	msg[4] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
	void		(Karen::*f[4])() = {
		&Karen::debug,
		&Karen::info,
		&Karen::warning,
		&Karen::error
	};
	int	i;
	for (i = 0; i < 4; i++)
	{
		if (msg[i] == level)
			break ;
	}
	switch (i) {
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break ;
		case 0:
			std::cout << "[ DEBUG ]" << std::endl;
			(this->*(f[i]))();
			i++;
		case 1:
			std::cout << "[ INFO ]" << std::endl;
			(this->*(f[i]))();
			i++;
		case 2:
			std::cout << "[ WARNING ]" << std::endl;
			(this->*(f[i]))();
			i++;
		case 3:
			std::cout << "[ ERROR ]" << std::endl;
			(this->*(f[i]))();
		
	}
}

Karen::Karen(void)
{
}

Karen::~Karen(void)
{
}
