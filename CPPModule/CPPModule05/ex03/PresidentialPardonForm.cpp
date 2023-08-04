/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:54:12 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 17:54:13 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form()
{
	std::cout << GREEN;
	std::cout << "[ PresidentialPardon default constructor ]" << std::endl;
	std::cout << RESET;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << RED;
	std::cout << "[ PresidentialPardon destructor ]" << std::endl;
	std::cout << RESET;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form(target, P_grade_sign, P_grade_exec, P_type)
{
	std::cout << WHITE;
	std::cout << "[ PresidentialPardon target constructor ]" << std::endl;
	std::cout << RESET;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &p) : Form(p)
{
	std::cout << YELLOW;
	std::cout << "[ PresidentialPardon copy constructor ]" << std::endl;
	std::cout << RESET;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(PresidentialPardonForm const &p)
{
	if (this == &p)
		return (*this);
	Form::operator=(p);
	std::cout << PINK;
	std::cout << "[ PresidentialPardon assignment operator ]" << std::endl;
	std::cout << RESET;	
	return (*this);
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	executable(executor);
	std::cout << RED;
	std::cout << getName() << " has been pardoned by Zafod Beeblebrox" << std::endl;
	std::cout << RESET;
}