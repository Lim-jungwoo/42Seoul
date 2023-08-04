/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 08:41:54 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 08:41:55 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

int	main(void)
{
	Data		d1;
	uintptr_t	u1;
	Data*		d1_s;

	u1 = serialize(&d1);
	d1_s = deserialize(u1);
	std::cout << d1;
	std::cout << *d1_s;
	std::cout << &d1 << std::endl;
	std::cout << d1_s << std::endl;

	return (0);
}
