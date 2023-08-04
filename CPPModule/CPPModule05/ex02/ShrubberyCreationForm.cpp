/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:53:39 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 17:53:39 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form()
{
	std::cout << GREEN;
	std::cout << "[ Shrubbery default constructor ]" << std::endl;
	std::cout << RESET;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << RED;
	std::cout << "[ Shrubbery destructor ]" << std::endl;
	std::cout << RESET;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form(target, S_grade_sign, S_grade_exec, S_type)
{
	std::cout << WHITE;
	std::cout << "[ Shrubbery target constructor ]" << std::endl;
	std::cout << RESET;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &s) : Form(s)
{
	std::cout << YELLOW;
	std::cout << "[ Shrubbery copy constructor ]" << std::endl;
	std::cout << RESET;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(ShrubberyCreationForm const &s)
{
	if (this == &s)
		return (*this);
	Form::operator=(s);
	std::cout << PINK;
	std::cout << "[ Shrubbery assignment operator ]" << std::endl;
	std::cout << RESET;	
	return (*this);
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	executable(executor);
	std::cout << GREEN;
	std::string shrubbery = "               ,@@@@@@@,\n"
                          "       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
                          "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
                          "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
                          "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
                          "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
                          "   `&%\\ ` /%&'    |.|        \\ '|8'\n"
                          "       |o|        | |         | |\n"
                          "       |.|        | |         | |\n"
                          "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_";
	std::cout << shrubbery << std::endl;
	std::cout << RESET;
}