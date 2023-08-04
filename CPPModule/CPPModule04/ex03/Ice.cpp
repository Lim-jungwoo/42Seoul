/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:59:15 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:59:16 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "ICharacter.hpp"

Ice::Ice() : AMateria("ice")
{
	std::cout << BLUE;
	std::cout << "[ Ice default constructor ]" << std::endl;
	std::cout << RESET;
}

Ice::~Ice()
{
	std::cout << RED;
	std::cout << "[ Ice destructor ]" << std::endl;
	std::cout << RESET;
}

Ice::Ice(Ice const &ice) : AMateria(ice)
{
	std::cout << BLUE;
	std::cout << "[ Ice copy constructor ]" << std::endl;
	std::cout << RESET;
}

Ice	&Ice::operator=(Ice const &ice)
{
	if (this == &ice)
		return (*this);
	AMateria::operator=(ice);
	std::cout << BLUE;
	std::cout << "[ Ice assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

AMateria* Ice::clone() const
{
	return (new Ice());
}

void	Ice::use(ICharacter &target)
{
	std::cout << YELLOW;
	std::cout << "[ use ]" << std::endl;
	std::cout << " * shoots an ice bolt at " << target.getName() << " *" << std::endl;
	std::cout << RESET;
}



