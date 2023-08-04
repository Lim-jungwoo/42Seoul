/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:38:34 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 15:38:35 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	type = A_T;
	std::cout << CYAN;
	std::cout << "[ WrongAnimal default constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << CYAN;
	std::cout << "[ WrongAnimal destructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongAnimal::WrongAnimal(WrongAnimal const &w_a)
{
	type = w_a.type;
	std::cout << CYAN;
	std::cout << "[ WrongAnimal copy constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongAnimal::WrongAnimal(std::string name)
{
	type = name;
	std::cout << CYAN;
	std::cout << "[ WrongAnimal string constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongAnimal	&WrongAnimal::operator=(WrongAnimal const &w_a)
{
	if (this == &w_a)
		return (*this);
	type = w_a.type;
	std::cout << CYAN;
	std::cout << "[ WrongAnimal assignment operator ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
	return (*this);
}

void	WrongAnimal::makeSound() const
{
	std::cout << CYAN;
	std::cout << "It has no type" << std::endl;
	std::cout << RESET;
}

void	WrongAnimal::setType(std::string type)
{
	std::cout << CYAN;
	std::cout << this->type << " changes to " << type << std::endl;
	std::cout << RESET;
	this->type = type;
}

std::string	WrongAnimal::getType() const
{
	return (type);
}
