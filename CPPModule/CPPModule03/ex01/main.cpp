/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:17 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 16:43:18 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main(void)
{
	
	ClapTrap	a;
	ClapTrap	*b = new ScavTrap("b");
	ScavTrap	d;
	ClapTrap	*c;
	ScavTrap	e("e");
	std::cout << std::endl;

	c = &d;
	d = e;
	std::cout << std::endl;

	a.attack("lim");
	b->attack("jung");
	c->attack("woo");
	d.attack("woo");
	std::cout << std::endl;

	d.takeDamage(5);
	c->takeDamage(5);
	c->takeDamage(5);
	std::cout << std::endl;

	c->beRepaired(10);
	d.beRepaired(20);
	std::cout << std::endl;

	d.guardGate();
	e.guardGate();
	std::cout << std::endl;

	delete b;
	return (0);
}
