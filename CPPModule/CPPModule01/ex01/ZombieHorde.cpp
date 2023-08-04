/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:05:04 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:05:04 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name)
{
	Zombie	*zom = new Zombie[N];
	std::stringstream	num;
	std::string			name_num;

	for (int i = 0; i < N; i++)
	{
		num << (i + 1);
		name_num = num.str();
		num.str("");
		zom[i].set_name(name + name_num);
	}
	return (zom);
}
