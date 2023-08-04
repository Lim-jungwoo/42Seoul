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
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	Dog	d1("show");
	Dog	d2("lim");
	Dog	d3(d1);

	d1 = d2;
	d1.makeSound();
	/*
	const Animal*	meta = new Animal();
	const Animal*	j = new Dog();
	const Animal*	i = new Cat();
	Animal*			a = new Dog();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << a->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	a->makeSound();
	meta->makeSound();
	i->Animal::makeSound();
	std::cout << std::endl;
	delete	meta;
	delete	j;
	delete	i;
	delete	a;

	std::cout << std::endl;
	std::cout << "======================" << std::endl;
	const WrongAnimal*	w_c = new WrongCat();
	const WrongAnimal*	w = new WrongAnimal();
	std::cout << w_c->getType() << " " << std::endl;
	w_c->makeSound();
	w->makeSound();
	delete	w_c;
	delete	w;
	*/
}
