/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:38:19 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 15:38:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	type = C_T;
	std::cout << PINK;
	std::cout << "[ WrongCat default constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongCat::~WrongCat()
{
	std::cout << PINK;
	std::cout << "[ WrongCat destructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongCat::WrongCat(WrongCat const &Wrongcat)
{
	type = Wrongcat.type;
	std::cout << PINK;
	std::cout << "[ WrongCat copy constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongCat::WrongCat(std::string name)
{
	type = name;
	std::cout << PINK;
	std::cout << "[ WrongCat string constructor ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
}

WrongCat	&WrongCat::operator=(WrongCat const &Wrongcat)
{
	if (this == &Wrongcat)
		return (*this);
	WrongAnimal::operator=(Wrongcat);
	type = Wrongcat.type;
	std::cout << PINK;
	std::cout << "[ WrongCat assignment operator ]" << std::endl;
	std::cout << "type : " << type << std::endl;
	std::cout << RESET;
	return (*this);
}

void	WrongCat::makeSound() const
{
	std::cout << PINK;
	std::cout << type << " : meow!!!!!" << std::endl;
	std::cout << RESET;
}

