/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:22:21 by jlim              #+#    #+#             */
/*   Updated: 2022/02/26 16:22:22 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert() : _error(false), _input(""), _value(0.0)
{}

Convert::~Convert()
{}

Convert::Convert(Convert const &c) : _error(false), _input(c.getInput()), _value(c.getValue())
{}

Convert::Convert(std::string const &input) : _error(false), _input(input), _value(0.0)
{
	try
	{
		char	*tmp = NULL;
		const_cast<double&>(_value) = std::strtod(_input.c_str(), &tmp);
		if (_value == 0.0 && (_input[0] != '-' && _input[0] != '+' && !std::isdigit(_input[0])))
			throw Convert::ErrorOccuredException();
		if (*tmp && std::strcmp(tmp, "f"))
			throw Convert::ErrorOccuredException();
	}
	catch(std::exception& e)
	{
		_error = true;
	}
}

const char	*Convert::ErrorOccuredException::what() const throw()
{
	return ("Error occured");
}

Convert	&Convert::operator=(Convert const &c)
{
	if (this == &c)
		return (*this);
	_error = c.getError();
	const_cast<std::string&>(_input) = c.getInput();
	const_cast<double&>(_value) = c.getValue();
	return (*this);
}

char	Convert::toChar() const
{
	return (static_cast<char>(_value));
}

int	Convert::toInt() const
{
	return (static_cast<int>(_value));
}

float	Convert::toFloat() const
{
	return (static_cast<float>(_value));
}

double	Convert::toDouble() const
{
	return (static_cast<double>(_value));
}

bool	Convert::getError() const
{
	return (_error);
}

const double	&Convert::getValue() const
{
	return (_value);
}

const std::string	&Convert::getInput() const
{
	return (_input);
}

std::ostream	&operator<<(std::ostream &out, Convert const &c)
{
	if (c.getError())
	{
		out << "convert impossible" << std::endl;
		return (out);
	}
	print_char(out, c);
	print_int(out, c);
	print_float_double(out, c);
	return (out);
}

void	print_char(std::ostream &out, Convert const &c)
{
	out << "char: ";
	if (std::isnan(c.getValue()) || std::isinf(c.getValue()))
		out << "impossible" << std::endl;
	else if (std::isprint(c.toChar()))
		out << "'" << c.toChar() << "'" << std::endl;
	else
		out << "Non Displayable" << std::endl;
}

void	print_int(std::ostream &out, Convert const &c)
{
	out << "int: ";
	if (std::isnan(c.getValue()) || std::isinf(c.getValue()))
		out << "impossible" << std::endl;
	else
		out << c.toInt() << std::endl;
}

void	print_float_double(std::ostream &out, Convert const &c)
{
	if (std::isnan(c.getValue()) || std::isinf(c.getValue()))
	{
		out << "float: " << std::showpos << c.toFloat() << "f" << std::endl;
		out << "double: " << std::showpos << c.toDouble() << std::endl;
		return ;
	}
	if (c.toFloat() == static_cast<int64_t>(c.toFloat()))
		out << "float: " << c.toFloat() << ".0f" << std::endl;
	else
	{
		out << "float: " << std::setprecision(std::numeric_limits<float>::digits10);
		out << c.toFloat() << "f" << std::endl;
	}
	if (c.toDouble() == static_cast<int64_t>(c.toDouble()))
		out << "double: " << c.toDouble() << ".0" << std::endl;
	else
	{
		out << "double: " << std::setprecision(std::numeric_limits<double>::digits10);
		out << c.toDouble() << std::endl;
	}

}