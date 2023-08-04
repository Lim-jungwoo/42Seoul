/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:19:25 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:19:26 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
	type = C_T;
	_brain = new Brain();
	std::cout << YELLOW;
	std::cout << "[ Cat default constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Cat::~Cat()
{
	delete	_brain;
	std::cout << YELLOW;
	std::cout << "[ Cat destructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Cat::Cat(Cat const &cat) : Animal(cat)
{
	type = cat.type;
	_brain = new Brain();
	_brain->set_ideas(cat._brain->get_ideas());
	std::cout << YELLOW;
	std::cout << "[ Cat copy constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Cat::Cat(std::string name) : Animal(name)
{
	type = name;
	_brain = new Brain();
	std::cout << YELLOW;
	std::cout << "[ Cat string constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

Cat	&Cat::operator=(Cat const &cat)
{
	if (this == &cat)
		return (*this);
	Animal::operator=(cat);
	type = cat.type;
	_brain->set_ideas(cat._brain->get_ideas());
	std::cout << YELLOW;
	std::cout << "[ Cat assignment operator ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
	return (*this);
}

void	Cat::makeSound() const
{
	std::cout << YELLOW;
	std::cout << type << " : meow!!!!!" << std::endl;
	std::cout << RESET;
}

std::string	*Cat::getBrain() const
{
	return (_brain->get_ideas());
}

void	Cat::setBrain(std::string *idea)
{
	_brain->set_ideas(idea);
}