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
#include "Intern.hpp"

int main(void)
{
	std::cout << "================create bureaucrat==============" << std::endl;
	Bureaucrat				b("lim", 140);
	Bureaucrat				b1("jung", 60);
	Bureaucrat				b2("peter", 45);
	Bureaucrat				b3("woo", 20);
	Bureaucrat				b4("john", 5);
	std::cout << std::endl;

	Intern	a1;
	Form	*f_s;
	Form	*f_r;
	Form	*f_p;
	Form	*f_n;

	std::cout << "================make form==============" << std::endl;
	f_s = a1.makeForm("plant shrubbery", "home");
	f_r = a1.makeForm("robotomy request", "Bender");
	f_p = a1.makeForm("presidentialpardon", "president");
	f_n = a1.makeForm("show me the money", "jung");
	std::cout << std::endl;

	std::cout << "================check Shrubbery==============" << std::endl;
	b.executeForm(*f_s);
	b1.executeForm(*f_s);
	b2.executeForm(*f_s);
	b3.executeForm(*f_s);
	b4.executeForm(*f_s);
	std::cout << std::endl;

	std::cout << "================check Robotomy==============" << std::endl;
	b.executeForm(*f_r);
	b1.executeForm(*f_r);
	b2.executeForm(*f_r);
	b3.executeForm(*f_r);
	b4.executeForm(*f_r);
	std::cout << std::endl;

	std::cout << "================check President==============" << std::endl;
	b.executeForm(*f_p);
	b1.executeForm(*f_p);
	b2.executeForm(*f_p);
	b3.executeForm(*f_p);
	b4.executeForm(*f_p);
	std::cout << std::endl;

	if (f_s)
		delete f_s;
	if (f_r)
		delete f_r;
	if (f_p)
		delete f_p;
	if (f_n)
		delete f_n;
}