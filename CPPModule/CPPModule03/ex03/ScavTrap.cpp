/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:32:22 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 19:32:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	_hitpoints = S_HP;
	_energy_points = S_EP;
	_attack_damage = S_AD;
	std::cout << YELLOW;
	std::cout << "[ ScavTrap default constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ScavTrap::~ScavTrap()
{
	std::cout << YELLOW;
	std::cout << "ScavTrap " << _name << " destructor" << std::endl;
	std::cout << RESET;
}

ScavTrap::ScavTrap(ScavTrap const &scav) : ClapTrap(scav)
{
	std::cout << YELLOW;
	std::cout << "[ ScavTrap copy constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	_hitpoints = S_HP;
	_energy_points = S_EP;
	_attack_damage = S_AD;
	std::cout << YELLOW;
	std::cout << "[ ScavTrap string constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ScavTrap	&ScavTrap::operator=(ScavTrap const &scav)
{
	if (this == &scav)
		return (*this);
	ClapTrap::operator=(scav);
	std::cout << YELLOW;
	std::cout << "[ ScavTrap assignment operator ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
	return (*this);
}

void	ScavTrap::attack(std::string const &target)
{
	std::cout << YELLOW;
	std::cout << "ScavTrap " << _name << " attack " << target << ",";
	std::cout << " causing " << _attack_damage << " points of damage!" << std::endl;
	std::cout << RESET;
}

void	ScavTrap::guardGate(void)
{
	std::cout << YELLOW;
	std::cout << "ScavTrap have enterred in Gate keeper mode" << std::endl;
	std::cout << RESET;
}