/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:35:53 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 21:35:54 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void	Contact::set_index(int _index)
{
	this->_index = _index;
}

void	Contact::set_first_name(std::string _first_name)
{
	this->_first_name = _first_name;
}

void	Contact::set_last_name(std::string _last_name)
{
	this->_last_name = _last_name;
}

void	Contact::set_nick_name(std::string _nick_name)
{
	this->_nick_name = _nick_name;
}

void	Contact::set_phone_number(std::string _phone_number)
{
	this->_phone_number = _phone_number;
}

void	Contact::set_darkest_secret(std::string _darkest_secret)
{
	this->_darkest_secret = _darkest_secret;
}

int	Contact::get_index(void)
{
	return (this->_index);
}

std::string	Contact::get_first_name(void)
{
	return (this->_first_name);
}

std::string	Contact::get_last_name(void)
{
	return (this->_last_name);
}

std::string	Contact::get_nick_name(void)
{
	return (this->_nick_name);
}

std::string	Contact::get_phone_number(void)
{
	return (this->_phone_number);
}

std::string	Contact::get_darkest_secret(void)
{
	return (this->_darkest_secret);
}
