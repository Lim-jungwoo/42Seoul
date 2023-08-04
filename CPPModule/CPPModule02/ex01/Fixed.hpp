/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:22:38 by jlim              #+#    #+#             */
/*   Updated: 2022/02/17 15:22:39 by jlim             ###   ########.fr       */
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

	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	int		toInt(void) const;
	float	toFloat(void) const;
};

std::ostream	&operator<<(std::ostream &s, const Fixed &f);

#endif