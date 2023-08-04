/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:17 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:18 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

int	main(void)
{
	Point	a(0,0);
	Point	b(6,0);
	Point	c(6,6);
	Point	check(1,0);

	std::cout << "a(" << a.get_x() << "," << a.get_y() << ") ";
	std::cout << "b(" << b.get_x() << "," << b.get_y() << ") ";
	std::cout << "c(" << c.get_x() << "," << c.get_y() << ") ";
	std::cout << "check(" << check.get_x() << "," << check.get_y() << ")" << std::endl;
	if (bsp(a, b, c, check))
	{
		std::cout << "check(" << check.get_x() << "," << check.get_y() << ") ";
		std::cout << "is in the triangle" << std::endl;
	}
	else
	{
		std::cout << "check(" << check.get_x() << "," << check.get_y() << ") ";
		std::cout << "is out of the triangle" << std::endl;
	}
	return (0);
}

