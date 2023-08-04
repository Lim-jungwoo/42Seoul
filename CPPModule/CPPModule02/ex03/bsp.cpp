/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:44 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:45 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool	check_triangle(Point const a, Point const b, Point const c)
{
	if ((a.get_x() == b.get_x()) && (a.get_y() == b.get_y()))
		return (false);
	if ((b.get_x() == c.get_x()) && (b.get_y() == c.get_y()))
		return (false);
	if ((c.get_x() == a.get_x()) && (c.get_y() == a.get_y()))
		return (false);
	if ((a.get_x() == b.get_x()))
		if (a.get_x() == c.get_x())
			return (false);
	if ((a.get_y() == b.get_y()))
		if (a.get_y() == c.get_y())
			return (false);
	return (true);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	int		meet_count = 0;
	Fixed	meet_x;

	if (check_triangle(a, b, c) == 0)
	{
		std::cout << "abc is not triangle" << std::endl;
		return (false);
	}

	if (a.get_y() == b.get_y())
	{
		if (a.get_y() == point.get_y())
			return (false);
	}
	else if ((a.get_y() > point.get_y()) != (b.get_y() > point.get_y()))
	{
		meet_x = (b.get_x() - a.get_x()) * (point.get_y() - a.get_y()) / (b.get_y() - a.get_y()) + a.get_x();
		if (meet_x == point.get_x())
			return (false);
		if (point.get_x() < meet_x)
			meet_count++;
	}
	
	if (b.get_y() == c.get_y())
	{
		if (b.get_y() == point.get_y())
			return (false);
	}
	else if ((b.get_y() > point.get_y()) != (c.get_y() > point.get_y()))
	{
		meet_x = (c.get_x() - b.get_x()) * (point.get_y() - b.get_y()) / (c.get_y() - b.get_y()) + b.get_x();
		if (meet_x == point.get_x())
			return (false);
		if (point.get_x() < meet_x)
			meet_count++;
	}

	if (c.get_y() == a.get_y())
	{
		if (c.get_y() == point.get_y())
			return (false);
	}
	else if ((c.get_y() > point.get_y()) != (a.get_y() > point.get_y()))
	{
		meet_x = (a.get_x() - c.get_x()) * (point.get_y() - c.get_y()) / (a.get_y() - c.get_y()) + c.get_x();
		if (meet_x == point.get_x())
			return (false);
		if (point.get_x() < meet_x)
			meet_count++;
	}
	
	return (meet_count == 1);
}
