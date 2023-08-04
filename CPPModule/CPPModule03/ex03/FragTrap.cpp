/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:29:47 by jlim              #+#    #+#             */
/*   Updated: 2022/02/19 14:29:48 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	_hitpoints = F_HP;
	_energy_points = F_EP;
	_attack_damage = F_AD;
	std::cout << PINK;
	std::cout << "[ FragTrap default constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

FragTrap::~FragTrap()
{
	std::cout << PINK;
	std::cout << "FragTrap " << _name << " destructor" << std::endl;
	std::cout << RESET;
}

FragTrap::FragTrap(FragTrap const &frag) : ClapTrap(frag)
{
	std::cout << PINK;
	std::cout << "[ FragTrap copy constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	_hitpoints = F_HP;
	_energy_points = F_EP;
	_attack_damage = F_AD;
	std::cout << PINK;
	std::cout << "[ FragTrap string constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

FragTrap	&FragTrap::operator=(FragTrap const &frag)
{
	if (this == &frag)	
		return (*this);
	ClapTrap::operator=(frag);
	std::cout << PINK;
	std::cout << "[ FragTrap assignment operator ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
	return (*this);
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << PINK;
	std::cout << "FragTrap has a positive high fives request" << std::endl;
	std::cout << RESET;
}