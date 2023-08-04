/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:54:33 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 12:54:33 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>
#include <string>


template <typename T>
void	swap(T& a, T& b)
{
	T	temp;

	temp = a;
	a = b;
	b = temp;
}

template <typename T>
T&	min(T& a, T& b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

template <typename T>
T&	max(T& a, T& b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

#endif