/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:02:39 by jlim              #+#    #+#             */
/*   Updated: 2022/02/17 15:02:40 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int					_value;
	const static int	_bits;
public:
	Fixed();
	~Fixed();
	Fixed(const Fixed &f);

	Fixed	&operator=(Fixed const &f);

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
};

#endif