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

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	a;
	ClapTrap	b("jung");
	ClapTrap	c(a);
	ClapTrap	d;
	std::cout << std::endl;

	d = b;
	c = d;
	std::cout << std::endl;

	a.attack("jung");
	b.attack("jung");
	std::cout << std::endl;

	d.takeDamage(5);
	c.takeDamage(5);
	c.takeDamage(5);
	std::cout << std::endl;

	c.beRepaired(10);
	d.beRepaired(20);
	std::cout << std::endl;

	return (0);
}
