/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:19:05 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:19:06 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const & type)
{
	_type = type;
	std::cout << GREEN;
	std::cout << "[ AMateria type constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

std::string const & AMateria::getType() const
{
	return (_type);
}

void	AMateria::use(ICharacter& target)
{
	std::cout << YELLOW;
	std::cout << "[ use ]" << target.getName() << std::endl;
	std::cout << RESET;
}

AMateria::AMateria()
{
	_type = "";
	std::cout << GREEN;
	std::cout << "[ AMateria default constructor ]" << std::endl;
	std::cout << RESET;
}

AMateria::~AMateria()
{
	std::cout << RED;
	std::cout << "[ AMateria destructor ]" << std::endl;
	std::cout << RESET;
}

AMateria::AMateria(AMateria const &am)
{
	_type = am.getType();
	std::cout << GREEN;
	std::cout << "[ AMateria copy constructor ]" << std::endl;
	std::cout << RESET;
}

AMateria	&AMateria::operator=(AMateria const &am)
{
	if (this == &am)
		return (*this);
	_type = am.getType();
	std::cout << BLUE;
	std::cout << "[ AMateria assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}