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

Form::Form() : _name(d_name), _is_signed(d_is_sign), _grade_sign(d_grade_sign), _grade_exec(d_grade_exec), _type(d_type)
{
	std::cout << GREEN;
	std::cout << "[ Form default constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
	std::cout << RESET;
}

Form::~Form()
{
	std::cout << RED;
	std::cout << "[ Form destructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
	std::cout << RESET;
}

Form::Form(Form const &form) : _name(form._name), _is_signed(form._is_signed), _grade_sign(form._grade_sign), _grade_exec(form._grade_exec), _type(form._type)
{
	std::cout << YELLOW;
	std::cout << "[ Form copy constructor ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
	std::cout << RESET;
}

Form::Form(std::string name, int grade_sign, int grade_exec) : _name(name), _is_signed(d_is_sign), _grade_sign(grade_sign), _grade_exec(grade_exec), _type(d_type)
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
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
	std::cout << RESET;
}

Form::Form(std::string name, int grade_sign, int grade_exec, std::string type) : _name(name), _is_signed(d_is_sign), _grade_sign(grade_sign), _grade_exec(grade_exec), _type(type)
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
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
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
	_type = form._type;
	std::cout << PINK;
	std::cout << "[ Form assignment operator ] ";
	std::cout << "name : " << _name;
	std::cout << " is_signed : " << _is_signed;
	std::cout << " grade_sign : " << _grade_sign;
	std::cout << " grade_exec : " << _grade_exec;
	std::cout << " type : " << _type << std::endl;
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

const char *Form::NotSignedException::what() const throw()
{
	return ("Form is not signed");
}

const char *Form::NoExcuteException::what() const throw()
{
	return ("Form has no execute grade");
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

std::string	Form::getType() const
{
	return (_type);
}

void	Form::beSigned(Bureaucrat const &bure) const
{
	if (bure.getGrade() <= _grade_sign)
	{
		const_cast<bool&>(_is_signed) = 1;
		return ;
	}
	throw (Form::GradeTooLowException());
}

std::ostream	&operator<<(std::ostream &out, const Form &form)
{
	out << "form name : " << form.getName() << " is_signed : " << form.getSigned();
	out << " grade_sign : " << form.getGradeSign() << " grade_exec : " << form.getGradeExec();
	out << " type : " << form.getType() << std::endl;
	return (out);
}

void	Form::executable(Bureaucrat const &bure) const
{
	bure.signForm(this);
	if (getSigned() == 0)
		throw (Form::NotSignedException());
	if (bure.getGrade() > getGradeExec())
		throw (Form::NoExcuteException());
}