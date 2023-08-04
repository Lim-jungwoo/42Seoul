/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:15:54 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 13:15:55 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	std::cout << "================create bureaucrat==============" << std::endl;
	Bureaucrat				b("lim", 140);
	Bureaucrat				b1("jung", 60);
	Bureaucrat				b2("peter", 45);
	Bureaucrat				b3("woo", 20);
	Bureaucrat				b4("john", 5);
	std::cout << std::endl;
	std::cout << "================check Shrubbery==============" << std::endl;
	ShrubberyCreationForm	a("my home");
	std::cout << std::endl;
	Form	*a1 = new ShrubberyCreationForm("school");
	std::cout << std::endl;
	b.executeForm(a);
	b.executeForm(*a1);
	b1.executeForm(a);
	b1.executeForm(*a1);
	b2.executeForm(a);
	b2.executeForm(*a1);
	b3.executeForm(a);
	b3.executeForm(*a1);
	b4.executeForm(a);
	b4.executeForm(*a1);
	std::cout << std::endl;
	delete a1;
	std::cout << std::endl;

	std::cout << "================check Robotomy==============" << std::endl;
	RobotomyRequestForm	r1("professor");
	std::cout << std::endl;
	Form	*r = new RobotomyRequestForm("scientist");
	b.executeForm(*r);
	b.executeForm(r1);
	b1.executeForm(*r);
	b1.executeForm(r1);
	b2.executeForm(*r);
	b2.executeForm(r1);
	b3.executeForm(*r);
	b3.executeForm(r1);
	b4.executeForm(*r);
	b4.executeForm(r1);
	std::cout << std::endl;
	delete r;
	std::cout << std::endl;

	std::cout << "================check President==============" << std::endl;
	PresidentialPardonForm	p1("president");
	std::cout << std::endl;
	Form	*p = new PresidentialPardonForm("lim jung woo");
	b.executeForm(*p);
	b.executeForm(p1);
	b1.executeForm(*p);
	b1.executeForm(p1);
	b2.executeForm(*p);
	b2.executeForm(p1);
	b3.executeForm(*p);
	b3.executeForm(p1);
	b4.executeForm(*p);
	b4.executeForm(p1);
	std::cout << std::endl;
	delete p;
	std::cout << std::endl;
}