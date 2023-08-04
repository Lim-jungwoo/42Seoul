/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:49:46 by jlim              #+#    #+#             */
/*   Updated: 2022/02/19 14:49:47 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : _name(ClapTrap::_name)
{
	ClapTrap::_name += "_clap_name";
	_energy_points = S_EP;
	std::cout << CYAN;
	std::cout << "[ DiamondTrap default constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << CYAN;
	std::cout << "DiamondTrap " << _name << " destructor" << std::endl;
	std::cout << RESET;
}

DiamondTrap::DiamondTrap(DiamondTrap const &dia) : ClapTrap(dia), ScavTrap(dia), FragTrap(dia), _name(dia._name)
{
	std::cout << CYAN;
	std::cout << "[ DiamondTrap copy constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	_energy_points = S_EP;
	std::cout << CYAN;
	std::cout << "[ DiamondTrap string constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

DiamondTrap	&DiamondTrap::operator=(DiamondTrap const &dia)
{
	if (this == &dia)
		return (*this);
	ScavTrap::operator=(dia);
	FragTrap::operator=(dia);
	_name = dia._name;
	_hitpoints = dia._hitpoints;
	_energy_points = dia._energy_points;
	_attack_damage = dia._attack_damage;
	std::cout << CYAN;
	std::cout << "[ DiamondTrap assignment operator ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
	return (*this);
}

void	DiamondTrap::whoAmI(void) const
{
	std::cout << CYAN;
	std::cout << "DiamondTrap name : " << _name << ", ClapTrap name : " << ClapTrap::_name << std::endl;
	std::cout << RESET;
}