/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:38:16 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:38:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

const std::string	&Weapon::getType(void)
{
	return (this->_type);
}

Weapon::Weapon(std::string type)
{
	this->_type = type;
}

void	Weapon::setType(std::string type)
{
	this->_type = type;
}

Weapon::Weapon(void)
{
}

Weapon::~Weapon(void)
{
}
