/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:17:26 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:17:27 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	type = A_T;
	std::cout << GREEN;
	std::cout << "[ Animal default constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Animal::~Animal()
{
	std::cout << GREEN;
	std::cout << "[ Animal destructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Animal::Animal(Animal const &animal)
{
	type = animal.type;
	std::cout << GREEN;
	std::cout << "[ Animal copy constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Animal::Animal(std::string name)
{
	type = name;
	std::cout << GREEN;
	std::cout << "[ Animal string constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Animal	&Animal::operator=(Animal const &animal)
{
	if (this == &animal)
		return (*this);
	type = animal.type;
	std::cout << GREEN;
	std::cout << "[ Animal assignment operator ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
	return (*this);
}

void	Animal::makeSound() const
{
	std::cout << GREEN;
	std::cout << "It has no type" << std::endl;
	std::cout << RESET;
}

void	Animal::setType(std::string type)
{
	std::cout << GREEN;
	std::cout << this->type << " changes to " << type << std::endl;
	std::cout << RESET;
	this->type = type;
}

std::string	Animal::getType() const
{
	return (type);
}