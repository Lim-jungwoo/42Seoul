/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:26:48 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 13:26:49 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>

template <typename T>
void	iter(T* arr, std::size_t len, void (*f)(T&))
{
	for (std::size_t i = 0; i < len; i++)
		f(arr[i]);
	std::cout << std::endl;
}

template <typename T>
void	print(T& t)
{
	std::cout << t << " ";
}

#endif
