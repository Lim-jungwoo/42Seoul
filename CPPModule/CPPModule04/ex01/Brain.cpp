/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:35:26 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 16:35:27 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::stringstream	num;
	std::string			idea;
	for (int i = 0; i < 100; i++)
	{
		idea = "idea";
		num << (i + 1);
		idea += num.str();
		num.str("");
		_ideas[i] = idea;
	}
	std::cout << WHITE;
	std::cout << "[ Brain default constructor ]" << std::endl;
	std::cout << RESET;
}

Brain::~Brain()
{
	std::cout << WHITE;
	std::cout << "[ Brain destructor ]" << std::endl;
	std::cout << RESET;
}

Brain::Brain(Brain const &brain)
{
	for (int i = 0; i < 100; i++)
		_ideas[i] = brain._ideas[i];
	std::cout << WHITE;
	std::cout << "[ Brain copy constructor ]" << std::endl;
	std::cout << RESET;
}

Brain	&Brain::operator=(Brain const &brain)
{
	if (this == &brain)
		return (*this);
	for (int i = 0; i < 100; i++)
		_ideas[i] = brain._ideas[i];
	std::cout << WHITE;
	std::cout << "[ Brain assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

std::string	*Brain::get_ideas()
{
	return (_ideas);
}

void		Brain::set_ideas(std::string *ideas)
{
	for (int i = 0; i < 100; i++)
		_ideas[i] = ideas[i];
}

void		Brain::change_ideas(std::string ideas)
{
	std::stringstream	num;
	std::string			idea;
	for (int i = 0; i < 100; i++)
	{
		idea = ideas;
		num << (i + 1);
		idea += num.str();
		num.str("");
		_ideas[i] = idea;
	}
}