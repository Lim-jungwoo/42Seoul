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
	Bureaucrat *lim = make_test("lim", 25);
	Bureaucrat *jung = make_test("jung", 0);
	Bureaucrat *woo = make_test("woo", 151);
	Bureaucrat *a = make_test("a", 1);
	Bureaucrat *b = make_test("b", 150);

	incre_test(a);
	decre_test(b);
	incre_test(lim);
	std::cout << *lim;
	std::cout << *a;
	std::cout << *b;
	delete lim;
	delete jung;
	delete woo;
	delete a;
	delete b;
}