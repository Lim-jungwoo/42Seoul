/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:35:50 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 10:35:51 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(){}

Base	*generate(void)
{
	Base	*abc = NULL;
	time_t	current_time;
	int		random;

	current_time = time(NULL);
	random = ((int)current_time % 3);
	switch (random){
		case 0:
			abc = new A();
			std::cout << "A class instanciate" << std::endl;
			return (abc);
		case 1:
			abc = new B();
			std::cout << "B class instanciate" << std::endl;
			return (abc);
		case 2:
			abc = new C();
			std::cout << "C class instanciate" << std::endl;
			return (abc);
	}
	return (abc);
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "real point type is A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "real point type is B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "real point type is C" << std::endl;
}

void	is_A(Base& p)
{
	(void)dynamic_cast<A&>(p);
	std::cout << "real reference type is A" << std::endl;
}

void	is_B(Base& p)
{
	(void)dynamic_cast<B&>(p);
	std::cout << "real reference type is B" << std::endl;
}

void	is_C(Base& p)
{
	(void)dynamic_cast<C&>(p);
	std::cout << "real reference type is C" << std::endl;
}

bool	is_ABC(Base& p, std::string abc)
{
	try
	{
		if (abc == "A")
			is_A(p);
		else if (abc == "B")
			is_B(p);
		else if (abc == "C")
			is_C(p);
	}
	catch(const std::exception& e)
	{
		return (false);
	}
	return (true);
}

void	identify(Base& p)
{
	if (is_ABC(p, "A") || is_ABC(p, "B") || is_ABC(p, "C"))
	{}
}
