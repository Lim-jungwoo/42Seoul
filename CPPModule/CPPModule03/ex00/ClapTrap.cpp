/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:05 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 16:43:06 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name(d_name), _hitpoints(c_h), _energy_points(c_e), _attack_damage(c_d)
{
	std::cout << GREEN;
	std::cout << "[ ClapTrap default constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ClapTrap::~ClapTrap()
{
	std::cout << RED;
	std::cout << "ClapTrap " << _name << " destructor" << std::endl;
	std::cout << RESET;
}

ClapTrap::ClapTrap(ClapTrap const &clap) : _name(clap._name), _hitpoints(clap._hitpoints), _energy_points(clap._energy_points), _attack_damage(clap._attack_damage)
{
	std::cout << GREEN;
	std::cout << "[ ClapTrap copy constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ClapTrap::ClapTrap(std::string _name) : _name(_name), _hitpoints(c_h), _energy_points(c_e), _attack_damage(c_d)
{
	std::cout << GREEN;
	std::cout << "[ ClapTrap string constructor ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
}

ClapTrap	&ClapTrap::operator=(ClapTrap const &clap)
{
	if (this == &clap)
		return (*this);
	_name = clap._name;
	_hitpoints = clap._hitpoints;
	_energy_points = clap._energy_points;
	_attack_damage = clap._attack_damage;
	std::cout << YELLOW;
	std::cout << "[ ClapTrap assignment operator ]" << std::endl;
	std::cout << "Name : " << _name;
	std::cout << ", Hitpoints : " << _hitpoints; 
	std::cout << ", Energy points : " << _energy_points;
	std::cout << ", Attack damage : " << _attack_damage << std::endl;
	std::cout << RESET;
	return (*this);
}

void	ClapTrap::attack(std::string const &target)
{
	std::cout << BLUE;
	std::cout << "ClapTrap " << _name << " attack " << target << ",";
	std::cout << " causing " << _attack_damage << " points of damage!" << std::endl;
	std::cout << RESET;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	_hitpoints -= amount;
	std::cout << PINK;
	std::cout << "ClapTrap " << _name << " take " << amount << " points of damage!" << std::endl;
	if (_hitpoints > 0)
		std::cout << "ClapTrap " << _name << " has " << _hitpoints << " Hitpoints!" << std::endl;
	else
	{
		_hitpoints = 0;
		std::cout << "ClapTrap " << _name << " die!" << std::endl;
	}
	std::cout << RESET;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << CYAN;
	if (_hitpoints == 0)
		std::cout << "ClapTrap " << _name << " revive!" << std::endl;
	_hitpoints += amount;
	std::cout << "ClapTrap " << _name << " is repaired " << amount << " points!" << std::endl;
	std::cout << "ClapTrap " << _name << " has " << _hitpoints << " Hitpoints!" << std::endl;
	std::cout << RESET;
}