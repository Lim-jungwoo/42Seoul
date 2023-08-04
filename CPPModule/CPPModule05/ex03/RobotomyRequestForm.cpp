/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:53:53 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 17:53:53 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm() : Form()
{
	std::cout << GREEN;
	std::cout << "[ Robotomy default constructor ]" << std::endl;
	std::cout << RESET;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << RED;
	std::cout << "[ Robotomy destructor ]" << std::endl;
	std::cout << RESET;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form(target, R_grade_sign, R_grade_exec, R_type)
{
	std::cout << WHITE;
	std::cout << "[ Robotomy target constructor ]" << std::endl;
	std::cout << RESET;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &r) : Form(r)
{
	std::cout << YELLOW;
	std::cout << "[ Robotomy copy constructor ]" << std::endl;
	std::cout << RESET;
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(RobotomyRequestForm const &r)
{
	if (this == &r)
		return (*this);
	Form::operator=(r);
	std::cout << PINK;
	std::cout << "[ Robotomy assignment operator ]" << std::endl;
	std::cout << RESET;	
	return (*this);
}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	time_t	current_time;
	std::string	success = " has been robotomized successfully 50% of the time";
	std::string	failure = " is failed to have been robotomized";

	executable(executor);
	current_time = time(NULL);
	std::cout << RED;
	std::cout << "drilllllllllllllllllllll!!!!!!!!" << std::endl;
	std::cout << executor.getName();
	if ((int)current_time % 2 == 1)
		std::cout << success << std::endl;
	else
		std::cout << failure << std::endl;
	std::cout << RESET;
}