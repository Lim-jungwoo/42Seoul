/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:44:18 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 16:44:19 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name(d_name), _is_signed(d_is_sign), _grade_sign(d_grade_sign), _grade_exec(d_grade_exec)
{
	std::cout << GREEN;
	std::cout << "[ Form default constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec << std::endl;
	std::cout << RESET;
}

Form::~Form()
{
	std::cout << RED;
	std::cout << "[ Form destructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec << std::endl;
	std::cout << RESET;
}

Form::Form(Form const &form) : _name(form._name), _is_signed(form._is_signed), _grade_sign(form._grade_sign), _grade_exec(form._grade_exec)
{
	std::cout << YELLOW;
	std::cout << "[ Form copy constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec << std::endl;
	std::cout << RESET;
}

Form::Form(std::string name, int grade_sign, int grade_exec) : _name(name), _is_signed(d_is_sign), _grade_sign(grade_sign), _grade_exec(grade_exec)
{
	if (grade_sign < 1 || grade_exec < 1)
		throw (Form::GradeTooHighException());
	if (grade_sign > 150 || grade_sign > 150)
		throw (Form::GradeTooLowException());
	std::cout << BLUE;
	std::cout << "[ Form parameter constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec << std::endl;
	std::cout << RESET;
}

Form	&Form::operator=(Form const &form)
{
	if (this == &form)
		return (*this);
	const_cast<std::string&>(_name) = form._name;
	_is_signed = form._is_signed;
	const_cast<int&>(_grade_sign) = form._grade_sign;
	const_cast<int&>(_grade_exec) = form._grade_exec;
	std::cout << PINK;
	std::cout << "[ Form assignment operator ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec << std::endl;
	std::cout << RESET;
	return (*this);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low");
}

std::string	Form::getName() const
{
	return (_name);
}

bool	Form::getSigned() const
{
	return (_is_signed);
}

int	Form::getGradeSign() const
{
	return (_grade_sign);
}

int	Form::getGradeExec() const
{
	return (_grade_exec);
}

void	Form::beSigned(Bureaucrat *bure)
{
	if (bure->getGrade() <= _grade_sign)
	{
		_is_signed = 1;
		return ;
	}
	throw (Form::GradeTooLowException());
}

std::ostream	&operator<<(std::ostream &out, const Form &form)
{
	out << "form name : " << form.getName() << " is_signed : " << form.getSigned();
	out << " grade_sign : " << form.getGradeSign() << " grade_exec : " << form.getGradeExec() << std::endl;
	return (out);
}