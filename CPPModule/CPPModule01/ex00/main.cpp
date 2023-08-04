/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 13:47:48 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 13:47:49 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*zom1 = newZombie("jung");
	Zombie	*zom2 = newZombie("woo");
	zom1->announce();
	zom2->announce();
	randomChump("lim");
	delete(zom1);
	delete(zom2);
	return (0);
}
