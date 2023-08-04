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
	//const Animal*	ani1 = new Animal();
	const Animal*	dog1 = new Dog();
	const Animal*	cat1 = new Cat();
	//Animal	ani2;
	Dog	dog2;
	Cat	cat2;

	dog1->makeSound();
	cat1->makeSound();
	dog2.makeSound();
	cat2.makeSound();
	delete dog1;
	delete cat1;
}