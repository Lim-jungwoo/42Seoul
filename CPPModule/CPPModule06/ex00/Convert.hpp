/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:22:26 by jlim              #+#    #+#             */
/*   Updated: 2022/02/26 16:22:26 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <string>
# include <cmath>
# include <iomanip>
# include <limits>
# include <cctype>
# include <cstdlib>
# include <cstdint>

class	Convert
{
	private:
		bool	_error;
		const std::string	_input;
		const double	_value;

	public:
		Convert();
		~Convert();
		Convert(Convert const &c);
		Convert(std::string const &input);

		Convert	&operator=(Convert const &c);

		class ErrorOccuredException : public std::exception {
			const char *what() const throw();
		};

		char	toChar() const;
		int		toInt() const;
		float	toFloat() const;
		double	toDouble() const;

		bool	getError() const;
		const double	&getValue() const;
		const std::string	&getInput() const;
};

std::ostream	&operator<<(std::ostream &out, Convert const &c);

void	print_char(std::ostream &out, Convert const &c);
void	print_int(std::ostream &out, Convert const &c);
void	print_float_double(std::ostream &out, Convert const &c);

#endif
