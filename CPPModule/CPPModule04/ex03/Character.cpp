/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:38:54 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:38:55 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	_name = "";
	for (int i = 0; i < 4; i++)
		_am[i] = NULL;
	std::cout << CYAN;
	std::cout << "[ Character default constrcutor ]" << std::endl;
	std::cout << RESET;
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		if (_am[i])
			delete _am[i];
	}
	std::cout << WHITE;
	std::cout << "[ Character destructor ] " << _name << std::endl;
	std::cout << RESET;
}

Character::Character(Character const &c)
{
	const AMateria	*temp;

	_name = c.getName();
	for (int i = 0; i < 4; i++)
	{
		temp = c.getAMateria(i);
		if (temp)
			_am[i] = temp->clone();
	}
	std::cout << CYAN;
	std::cout << "[ Character copy constructor ]" << std::endl;
	std::cout << RESET;
}

Character::Character(std::string const &name)
{
	_name = name;
	for (int i = 0; i < 4; i++)
		_am[i] = NULL;
	std::cout << CYAN;
	std::cout << "[ Character string constructor ]" << std::endl;
	std::cout << RESET;
}

Character	&Character::operator=(Character const &c)
{
	if (this == &c)
		return (*this);
	const AMateria	*temp;

	_name = c.getName();
	for (int i = 0; i < 4; i++)
	{
		if (_am[i])
		{
			delete	_am[i];
			_am[i] = NULL;
		}
		temp = c.getAMateria(i);
		if (temp)
			_am[i] = temp->clone();
	}
	std::cout << CYAN;
	std::cout << "[ Character assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

const AMateria	*Character::getAMateria(int idx) const
{
	return (_am[idx]);
}

const std::string	&Character::getName() const
{
	return (_name);
}

void	Character::equip(AMateria *am)
{
	if (!am)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!_am[i])
		{
			_am[i] = am;
			std::cout << CYAN;
			std::cout << "[ equip ] " << _name << "'s " << i;
			std::cout << "th Materia " << am->getType() << std::endl;
			std::cout << RESET;
			return ;
		}
	}
	std::cout << CYAN;
	std::cout << "[ equip fail ] " << _name << std::endl;
	std::cout << RESET;
}

void	Character::unequip(int idx)
{
	if (idx >= 0 && idx < 4 && _am[idx])
	{
		std::cout << CYAN;
		std::cout << "[ unequip ] " << _name  << "'s " << idx;
		std::cout << "th Materia " << _am[idx]->getType() << std::endl;
		std::cout << RESET;
		_am[idx] = NULL;
		return ;
	}
	std::cout << CYAN;
	std::cout << "[ unequip fail ] " << _name << std::endl;
	std::cout << RESET;
}

void	Character::use(int idx, ICharacter &ic)
{
	if (idx >= 0 && idx < 4 && _am[idx])
		_am[idx]->use(ic);
	else
	{
		std::cout << YELLOW;
		std::cout << "[ use fail ] " << _name  << "'s " << idx;
		std::cout << "th Materia" << std::endl;
		std::cout << RESET;
	}
}