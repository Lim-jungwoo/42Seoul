/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:17:12 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:17:13 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"


int	main(void)
{
	const Animal*	meta[10];

	std::cout << RED;
	std::cout << "<<<<<<<<<<<<<create and fill array of animal>>>>>>>>>>>>" << std::endl;
	std::cout << RESET;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "<<<<<<<<create and fill " << (i + 1) << "th animal>>>>>>>>>>" << std::endl;
		if ((i % 2) == 1)
			meta[i] = new Cat();
		else
			meta[i] = new Dog();
		std::cout << std::endl;
	}
	std::cout << RED;
	std::cout << std::endl;
	std::cout << "==========================================" << std::endl;
	std::cout << "<<<<<<<<<<<delete array of animal>>>>>>>>>>" << std::endl;
	std::cout << RESET;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "<<<<<<<<delete " << (i + 1) << "th animal>>>>>>>>>>" << std::endl;
		delete meta[i];
		std::cout << std::endl;
	}
	
	std::cout << RED;
	std::cout << "==========================================" << std::endl;
	std::cout << "<<<<<<<<<<<deep copy check>>>>>>>>>>" << std::endl;
	std::cout << RESET;

	const Dog*	dog1 = new Dog("jung");
	const Dog*	dog2 = new Dog();
	Dog	dog3("lim");
	std::string	idea = "show";

	dog2->setBrain(idea);
	std::cout << "Dog3 type : " << dog3.getType() << std::endl;
	std::cout << "Dog3 brain : " << dog3.getBrain()[0] << std::endl;
	dog3 = *dog2;
	delete dog2;
	std::cout << "Dog3 = *Dog2 result -> Dog3 type : " << dog3.getType() << std::endl;
	std::cout << "Dog3 = *Dog2 result -> Dog3 brain : " << dog3.getBrain()[0] << std::endl;
	
	std::cout << RED;
	std::cout << "==========================================" << std::endl;
	std::cout << "<<<<<<<<<<<after delete dog1>>>>>>>>>>" << std::endl;
	std::cout << RESET;
	dog1->setBrain(idea);
	Dog	dog4(*dog1);
	std::cout << "Dog1 type : " << dog1->getType() << std::endl;
	std::cout << "Dog1 brain : " << dog1->getBrain()[0] << std::endl;
	delete dog1;
	std::cout << "Dog4 type : " << dog4.getType() << std::endl;
	std::cout << "Dog4 brain : " << dog4.getBrain()[0] << std::endl;
	dog3 = dog4;
	std::cout << "Dog3 type : " << dog3.getType() << std::endl;
	std::cout << "Dog3 brain : " << dog3.getBrain()[0] << std::endl;
	
	return (0);
}