/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 08:26:12 by jlim              #+#    #+#             */
/*   Updated: 2022/03/01 08:26:12 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::~Span(void) {}

Span::Span(void) : _data(0, 0)
{
	_data.reserve(0);
}

Span::Span(unsigned int n) : _data(0, 0)
{
	_data.reserve(n);
}

Span::Span(const Span& s) : _data(0, 0)
{
	_data.reserve(s.getData().capacity());
	std::copy(std::begin(s.getData()), std::end(s.getData()), std::back_inserter(_data));
}

Span&	Span::operator=(const Span& s)
{
	if (this == &s || _data.capacity() != s.getData().capacity())
		return (*this);
	_data.clear();
	_data.reserve(s.getData().capacity());
	std::copy(std::begin(s.getData()), std::end(s.getData()), std::back_inserter(_data));

	return (*this);
}

void	Span::addNumber(int value)
{
	if (_data.size() == _data.capacity())
		throw NoStoreException();
	_data.push_back(value);
}

unsigned int	Span::shortestSpan(void)
{
	if (_data.size() < 2)
		throw NoSpanException();
	std::vector<int>	sort_data(_data);
	std::vector<int>	after_minus;
	std::vector<int>	abs_minus;
	unsigned int		result;
	after_minus.resize(_data.size());
	abs_minus.resize(_data.size());

	std::sort(std::begin(sort_data), std::end(sort_data));
	std::adjacent_difference(std::begin(sort_data), std::end(sort_data), std::begin(after_minus));
	std::transform(std::begin(after_minus), std::end(after_minus), std::begin(abs_minus), Abs());
	result = *std::min_element(std::begin(abs_minus) + 1, std::end(abs_minus));
	return (result);
}

unsigned int	Span::longestSpan(void)
{
	if (_data.size() < 2)
		throw NoSpanException();
	unsigned int	result;
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator>	p_iter =
		std::minmax_element(std::begin(_data), std::end(_data));
	result = *(p_iter.second) - *(p_iter.first);
	return (result);
}

const char*	Span::NoStoreException::what(void) const throw()
{
	return ("There are already N of them stored in the object");
}

const char*	Span::NoSpanException::what(void) const throw()
{
	return ("There is no span to find");
}

const std::vector<int>&	Span::getData(void) const
{
	return (_data);
}
