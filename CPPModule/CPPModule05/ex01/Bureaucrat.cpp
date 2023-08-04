/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:15:51 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 13:15:51 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _name(d_name), _grade(d_grade)
{
	std::cout << GREEN;
	std::cout << "[ Bureaucrat default constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " grade : " << _grade << std::endl;
	std::cout << RESET;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << RED;
	std::cout << "[ Bureaucrat destructor ] ";
	std::cout << "name : " << _name;
	std::cout << " grade : " << _grade << std::endl;
	std::cout << RESET;
}

Bureaucrat::Bureaucrat(Bureaucrat const &bure) : _name(bure._name), _grade(bure._grade)
{
	std::cout << YELLOW;
	std::cout << "[ Bureaucrat copy constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " grade : " << _grade << std::endl;
	std::cout << RESET;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade)
{
	if (grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	if (grade > 150)
		throw (Bureaucrat::GradeTooLowException());
	std::cout << BLUE;
	std::cout << "[ Bureaucrat parameter constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " grade : " << _grade << std::endl;
	std::cout << RESET;	
}

Bureaucrat	&Bureaucrat::operator=(Bureaucrat const &bure)
{
	if (this == &bure)
		return (*this);
	const_cast<std::string&>(_name) = bure._name;
	_grade = bure._grade;
	std::cout << PINK;
	std::cout << "[ Bureaucrat assignment operator ] ";
	std::cout << "name : " << _name;
	std::cout << " grade : " << _grade << std::endl;
	std::cout << RESET;	
	return (*this);
}

std::string	Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade() const
{
	return (_grade);
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat grade is too high");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat grade is too low");
}

void	Bureaucrat::increment_grade()
{
	if ((_grade - 1) < 1)
		throw (Bureaucrat::GradeTooHighException());
	--_grade;
}

void	Bureaucrat::decrement_grade()
{
	if ((_grade + 1) > 150)
		throw (Bureaucrat::GradeTooLowException());
	++_grade;
}

std::ostream	&operator<<(std::ostream &out, const Bureaucrat &bure)
{
	out << bure.getName() << ", bureaucrat grade " << bure.getGrade()  << std::endl;
	return (out);
}

void	Bureaucrat::signForm(Form *form)
{
	try
	{
		form->beSigned(this);
		std::cout << CYAN;
		std::cout << _name << " signs " << form->getName() << std::endl;
		std::cout << RESET;
	}
	catch(std::exception& e)
	{
		std::cout << CYAN;
		std::cout << _name << " cannot sign " << form->getName();
		std::cout << " because ";
		std::cerr << e.what() << std::endl;
		std::cout << RESET;
	}
	
}