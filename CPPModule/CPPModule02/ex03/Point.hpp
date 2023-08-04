/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:33 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:34 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include "Fixed.hpp"

class Point
{
private:
	Fixed const	_x;
	Fixed const	_y;

public:
	Point();
	~Point();
	Point(Point const &p);
	Point(Fixed const x, Fixed const y);

	Point	&operator=(Point const &p);

	Fixed	get_x(void) const;
	Fixed	get_y(void) const;
};

#endif