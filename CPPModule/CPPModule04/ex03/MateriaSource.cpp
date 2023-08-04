/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:39:03 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:39:04 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		_am[i] = NULL;
	std::cout << WHITE;
	std::cout << "[ MateriaSource default constructor ]" << std::endl;
	std::cout << RESET;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		if (_am[i])
		{
			delete _am[i];
			_am[i] = NULL;
		}
	}
	std::cout << RED;
	std::cout << "[ MateriaSource destructor ]" << std::endl;
	std::cout << RESET;
}

MateriaSource::MateriaSource(MateriaSource const &ms)
{
	AMateria const	*temp;

	for (int i = 0; i < 4; i++)
	{
		temp = ms.getAMateria(i);
		if (temp)
			_am[i] = temp->clone();
	}
	std::cout << WHITE;
	std::cout << "[ MateriaSource copy constructor ]" << std::endl;
	std::cout << RESET;
}

MateriaSource	&MateriaSource::operator=(MateriaSource const &ms)
{
	if (this == &ms)
		return (*this);
	AMateria const	*temp;
	for (int i = 0; i < 4; i++)
	{
		if (_am[i])
		{
			delete _am[i];
			_am[i] = NULL;
		}
		temp = ms.getAMateria(i);
		if (temp)
			_am[i] = temp->clone();
	}
	std::cout << WHITE;
	std::cout << "[ MateriaSource assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

void	MateriaSource::learnMateria(AMateria *am)
{
	if (!am)
		return ;
	for (int i = 0; i < 4; i++)
	{
		if (!_am[i])
		{
			_am[i] = am->clone();
			std::cout << WHITE;
			std::cout << "[ learnMateria ] " << am->getType() << std::endl;
			std::cout << RESET;
			delete am;
			return ;
		}
	}
	std::cout << WHITE;
	std::cout << "[ learnMateria fail ] " << am->getType() << std::endl;
	std::cout << RESET;
}

AMateria	*MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (_am[i] && _am[i]->getType() == type)
		{
			std::cout << WHITE;
			std::cout << "[ createMateria ] " << type << std::endl;
			std::cout << RESET;
			return (_am[i]->clone());
		}
	}
	std::cout << WHITE;
	std::cout << "[ createMateria fail ] " << type << std::endl;
	std::cout << RESET;
	return (NULL);
}

AMateria const	*MateriaSource::getAMateria(int idx) const
{
	return (_am[idx]);
}
