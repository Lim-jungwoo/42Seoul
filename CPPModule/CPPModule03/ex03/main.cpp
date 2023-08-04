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
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int	main(void)
{
	{
		std::cout << RED;
		std::cout << "===================default constructor===================" << std::endl;
		DiamondTrap	d1;
		std::cout << std::endl;
		ClapTrap	c1;
		std::cout << std::endl;
		ScavTrap	s1;
		std::cout << std::endl;
		FragTrap	f1;
		std::cout << std::endl;

		std::cout << RED;
		std::cout << "===================default attack===================" << std::endl;
		d1.attack("lim");
		d1.ClapTrap::attack("lim");
		c1.attack("lim");
		s1.attack("lim");
		s1.ClapTrap::attack("lim");
		f1.attack("lim");
		std::cout << std::endl;
	}
	{
		std::cout << RED;
		std::cout << "===================name constructor===================" << std::endl;
		DiamondTrap	d2("diamond");
		std::cout << std::endl;
		ClapTrap	c2("clap");
		std::cout << std::endl;
		ScavTrap	s2("scav");
		std::cout << std::endl;
		FragTrap	f2("frag");
		std::cout << std::endl;

		std::cout << RED;
		std::cout << "===================name attack===================" << std::endl;
		d2.attack("lim");
		d2.ClapTrap::attack("lim");
		c2.attack("lim");
		s2.attack("lim");
		s2.ClapTrap::attack("lim");
		f2.attack("lim");
		std::cout << std::endl;
	}
	{
		std::cout << RED;
		std::cout << "===================upcasting constructor===================" << std::endl;
		ClapTrap	*c3 = new DiamondTrap("d_clap");
		std::cout << std::endl;
		ScavTrap	*s3 = new DiamondTrap("d_scav");
		std::cout << std::endl;
		FragTrap	*f3 = new DiamondTrap("d_frag");
		std::cout << std::endl;

		std::cout << RED;
		std::cout << "===================upcasting attack===================" << std::endl;
		c3->attack("lim");
		c3->ClapTrap::attack("lim");
		s3->attack("lim");
		s3->ClapTrap::attack("lim");
		f3->attack("lim");
		std::cout << std::endl;

		std::cout << RED;
		std::cout << "===================upcasting delete===================" << std::endl;
		delete c3;
		delete s3;
		delete f3;
	}
}
