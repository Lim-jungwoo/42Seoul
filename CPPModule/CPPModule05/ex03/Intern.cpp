/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:50:20 by jlim              #+#    #+#             */
/*   Updated: 2022/02/25 17:50:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	std::cout << GREEN;
	std::cout << "[ Intern default constructor ]" << std::endl;
	std::cout << RESET;
}

Intern::~Intern()
{
	std::cout << RED;
	std::cout << "[ Intern destructor ]" << std::endl;
	std::cout << RESET;
}

Intern::Intern(Intern const &intern)
{
	(void)intern;
	std::cout << YELLOW;
	std::cout << "[ Intern copy constructor ]" << std::endl;
	std::cout << RESET;
}

Intern	&Intern::operator=(Intern const &intern)
{
	if (this == &intern)
		return (*this);
	(void)intern;
	std::cout << PINK;
	std::cout << "[ Intern assignment operator ]" << std::endl;
	std::cout << RESET;
	return (*this);
}

Form	*Intern::makeForm(std::string name, std::string target)
{
	std::string	type[3] = {S_type, R_type, P_type};

	try
	{
		for (int i = 0; i < 3; i++)
		{
			if (type[i] == name)
			{
				std::cout << YELLOW;
				std::cout << "Intern creates " << name << " target to " << target << std::endl;
				switch (i)
				{
					case 0:
						return (new ShrubberyCreationForm(target));
						break ;
					case 1:
						return (new RobotomyRequestForm(target));
						break ;
					case 2:
						return (new PresidentialPardonForm(target));
						break ;
				}
			}
		}
		throw NoTypeException();
	}
	catch(std::exception& e)
	{
		std::cout << RED;
		std::cout << "Intern cannot creates name because ";
		std::cerr << e.what() << std::endl;
		std::cout << RESET;
		return (NULL);
	}
}

const char	*Intern::NoTypeException::what() const throw()
{
	return ("there is no type");
}