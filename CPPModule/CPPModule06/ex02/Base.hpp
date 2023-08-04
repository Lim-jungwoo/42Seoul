/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:35:45 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 10:35:46 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

#include <iostream>
#include <string>
#include <ctime>

class Base
{
public:
	virtual ~Base();
};

Base	*generate(void);
void	identify(Base* p);
void	identify(Base& p);

class A : public Base
{};

class B : public Base
{};

class C : public Base
{};

#endif