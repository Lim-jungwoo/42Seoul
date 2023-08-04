/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:19:32 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:19:34 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
	type = D_T;
	std::cout << BLUE;
	std::cout << "[ Dog default constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Dog::~Dog()
{
	std::cout << BLUE;
	std::cout << "[ Dog destructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Dog::Dog(Dog const &dog) : Animal(dog)
{
	type = dog.type;
	std::cout << BLUE;
	std::cout << "[ Dog copy constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Dog::Dog(std::string name) : Animal(name)
{
	type = name;
	std::cout << BLUE;
	std::cout << "[ Dog string constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Dog	&Dog::operator=(Dog const &dog)
{
	if (this == &dog)
		return (*this);
	Animal::operator=(dog);
	type = dog.type;
	std::cout << BLUE;
	std::cout << "[ Dog assignment operator ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
	return (*this);
}

void	Dog::makeSound() const
{
	std::cout << BLUE;
	std::cout << type << " : Bow-wow" << std::endl;
	std::cout << RESET;
}
