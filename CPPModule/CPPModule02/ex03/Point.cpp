/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:38 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:39 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : _x(0), _y(0)
{
}

Point::~Point()
{
}

Point::Point(Point const &p) : _x(p._x), _y(p._y)
{
}

Point::Point(Fixed const x, Fixed const y) : _x(x), _y(y)
{
}

Point	&Point::operator=(Point const &p)
{
	if (this != &p)
	{
		const_cast<Fixed&>(_x) = p._x;
		const_cast<Fixed&>(_y) = p._y;
	}
	return (*this);
}

Fixed	Point::get_x(void) const
{
	return (_x);
}

Fixed	Point::get_y(void) const
{
	return (_y);
}
