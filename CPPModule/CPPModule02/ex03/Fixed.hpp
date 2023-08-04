/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:11:23 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 09:11:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int					_value;
	const static int	_bits;
public:
	Fixed();
	~Fixed();
	Fixed(const int Fixed);
	Fixed(const float Fixed);
	Fixed(const Fixed &f);

	Fixed	&operator=(const Fixed &f);
	bool	operator>(const Fixed &f) const;
	bool	operator<(const Fixed &f) const;
	bool	operator>=(const Fixed &f) const;
	bool	operator<=(const Fixed &f) const;
	bool	operator==(const Fixed &f) const;
	bool	operator!=(const Fixed &f) const;
	Fixed	operator+(const Fixed &f) const;
	Fixed	operator-(const Fixed &f) const;
	Fixed	operator*(const Fixed &f) const;
	Fixed	operator/(const Fixed &f) const;
	Fixed	&operator++(void);
	Fixed	operator++(int);
	Fixed	&operator--(void);
	Fixed	operator--(int);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	int		toInt(void) const;
	float	toFloat(void) const;

	static Fixed		&min(Fixed &f1, Fixed &f2);
	static Fixed const	&min(Fixed const &f1, Fixed const &f2);
	static Fixed		&max(Fixed &f1, Fixed &f2);
	static Fixed const	&max(Fixed const &f1, Fixed const &f2);
};

std::ostream	&operator<<(std::ostream &s, const Fixed &f);

#endif

