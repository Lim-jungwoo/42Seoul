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

Form	*make_form(std::string name, int grade_sign, int grade_exec)
{
	try
	{
		Form	*form = new Form(name, grade_sign, grade_exec);
		std::cout << "there is no exception" << std::endl;
		return (form);
	}
	catch(std::exception& e)
	{
		std::cout << "form name : " << name;
		std::cout << " grade_sign or grade_exec is ";
		std::cerr << e.what() << std::endl;
	}
	return (NULL);
}

void	is_signed_test(Bureaucrat *bure, Form *form)
{
	bure->signForm(form);
}

Bureaucrat	*make_test(std::string name, int grade)
{
	try
	{
		Bureaucrat	*h = new Bureaucrat(name, grade);
		std::cout << h->getName() << " " << h->getGrade() << " ";
		std::cout << "there is no exception" << std::endl;
		return (h);
	}
	catch(std::exception& e)
	{
		std::cout << RED;
		std::cout << "name : " << name;
		std::cout << " grade : " << grade << " " << name << "'s ";
		std::cerr << e.what() << std::endl;
		std::cout << RESET;
	}
	return (NULL);
}

void	incre_test(Bureaucrat *incre)
{
	try
	{
		std::cout << "name : " << incre->getName();
		std::cout << " grade : " << incre->getGrade() << std::endl;
		incre->increment_grade();
		std::cout << "increment grade result -> name : " << incre->getName();
		std::cout << " increase grade : " << incre->getGrade() << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << RED;
		std::cout << "name : " << incre->getName();
		std::cout << " grade : " << incre->getGrade() << " increase fail because ";
		std::cerr << e.what() << '\n';
		std::cout << RESET;
	}
}

void	decre_test(Bureaucrat *decre)
{
	try
	{
		std::cout << "name : " << decre->getName();
		std::cout << " grade : " << decre->getGrade() << std::endl;
		decre->decrement_grade();
		std::cout << "decrement garde result -> name : " << decre->getName();
		std::cout << " decrease grade : " << decre->getGrade() << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << RED;
		std::cout << "name : " << decre->getName();
		std::cout << " grade : " << decre->getGrade() << " decrease fail because ";
		std::cerr << e.what() << '\n';
		std::cout << RESET;
	}
}

int	main(void)
{
	Form	*lim = make_form("lim", 49, 80);
	Form	jung(*lim);
	Form	*woo = make_form("woo", 150, 0);
	Form	jung2;
	Bureaucrat	*a = make_test("bure", 50);

	std::cout << jung;
	jung2 = jung;
	is_signed_test(a, lim);
	incre_test(a);
	is_signed_test(a, lim);
	decre_test(a);
	is_signed_test(a, lim);
	is_signed_test(a, &jung);
	delete lim;
	delete woo;
	return (0);
}