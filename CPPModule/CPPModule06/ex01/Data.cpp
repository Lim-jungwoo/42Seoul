/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 08:42:02 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 08:42:03 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() : _s1(d_s1), _n(d_n), _s2(d_s2)
{}

Data::~Data()
{}

Data::Data(Data const &data) : _s1(data.getS1()), _n(data.getInt()), _s2(data.getS2())
{}

Data::Data(std::string s1, int n, std::string s2) : _s1(s1), _n(n), _s2(s2)
{}

Data	&Data::operator=(Data const &data)
{
	if (this == &data)
		return (*this);
	_s1 = data.getS1();
	_n = data.getInt();
	_s2 = data.getS2();
	return (*this);
}
std::string	Data::getS1() const
{
	return (_s1);
}

int	Data::getInt() const
{
	return (_n);
}

std::string	Data::getS2() const
{
	return (_s2);
}

std::ostream	&operator<<(std::ostream &out, Data const &data)
{
	out << "s1 : " << data.getS1() << ", n : " << data.getInt();
	out << ", s2 : " << data.getS2() << std::endl;
	return (out);
}

uintptr_t	serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data	*deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}
