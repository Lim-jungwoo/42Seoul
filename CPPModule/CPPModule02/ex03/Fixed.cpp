/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:28 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:29 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_bits = 8;

Fixed::Fixed(void)
{
	_value = 0;
}

Fixed::Fixed(const int value)
{
	_value = value << _bits;
}

Fixed::Fixed(const float value)
{
	_value = roundf(value * (1 << _bits));
}

Fixed::Fixed(const Fixed &f)
{
	*this = f;
}

Fixed::~Fixed(void)
{
}

Fixed	&Fixed::operator=(const Fixed &f)
{
	if (this == &f)
		return (*this);
	_value = f._value;
	return (*this);
}

bool	Fixed::operator>(const Fixed &f) const
{
	return (_value > f._value);
}

bool	Fixed::operator<(const Fixed &f) const
{
	return (_value < f._value);
}

bool	Fixed::operator>=(const Fixed &f) const
{
	return (_value >= f._value);
}

bool	Fixed::operator<=(const Fixed &f) const
{
	return (_value <= f._value);
}

bool	Fixed::operator==(const Fixed &f) const
{
	return (_value == f._value);
}

bool	Fixed::operator!=(const Fixed &f) const
{
	return (_value != f._value);
}

Fixed	Fixed::operator+(const Fixed &f) const
{
	return (Fixed(toFloat() + f.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &f) const
{
	return (Fixed(toFloat() - f.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &f) const
{
	return (Fixed(toFloat() * f.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &f) const
{
	return (Fixed(toFloat() / f.toFloat()));
}

Fixed	&Fixed::operator++(void)
{
	_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	f(*this);

	_value++;
	return (f);
}

Fixed	&Fixed::operator--(void)
{
	_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	f(*this);

	_value--;
	return (f);
}

int	Fixed::getRawBits(void) const
{
	return (_value);
}

void	Fixed::setRawBits(int const raw)
{
	_value = raw;
}

int	Fixed::toInt(void) const
{
	return (_value >> _bits);
}

float	Fixed::toFloat(void) const
{
	return (float(_value) / (1 << _bits));
}

Fixed	&Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed const	&Fixed::min(Fixed const &f1, Fixed const &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed	&Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1 < f2)
		return (f2);
	return (f1);
}

Fixed const &Fixed::max(Fixed const &f1, Fixed const &f2)
{
	if (f1 < f2)
		return (f2);
	return (f1);
}

std::ostream	&operator<<(std::ostream &out, const Fixed &f)
{
	out << f.toFloat();
	return (out);
}
