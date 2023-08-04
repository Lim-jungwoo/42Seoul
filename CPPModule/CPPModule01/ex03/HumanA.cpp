/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:38:33 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:38:34 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon)
{
}

void	HumanA::attack(void)
{
	std::cout << this->_name << " attacks with his ";
	std::cout << this->_weapon.getType() << std::endl;
}

HumanA::~HumanA(void)
{
}

