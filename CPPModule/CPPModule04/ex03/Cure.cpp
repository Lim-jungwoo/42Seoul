/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:24:04 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 13:24:05 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure() : AMateria("cure")
{
	std::cout << PINK;
	std::cout << "[ Cure default constructor ]" << std::endl;
	std::cout << RESET;
}

Cure::~Cure()
{
	std::cout << RED;
	std::cout << "[ Cure destructor ]" << std::endl;
	std::cout << RESET;
}

Cure::Cure(Cure const &cure) : AMateria(cure)
{
	std::cout << PINK;
	std::cout << "[ Cure copy constructor ]" << std::endl;
	std::cout << RESET;
}

Cure	&Cure::operator=(Cure const &cure)
{
	if (this == &cure)
		return (*this);
	AMateria::operator=(cure);
	std::cout << PINK;
	std::cout << "[ Cure assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

AMateria* Cure::clone() const
{
	return (new Cure());
}

void	Cure::use(ICharacter &target)
{
	std::cout << YELLOW;
	std::cout << "[ use ]" << std::endl;
	std::cout << " * heals " << target.getName() << "'s wounds *" << std::endl;
	std::cout << RESET;
}




