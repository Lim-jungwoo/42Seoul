/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:36:11 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 21:36:12 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void	PhoneBook::reset_index(void)
{
	this->_index = 0;
}

void	PhoneBook::add_contact(int index)
{
	std::string	first_name;
	std::string	last_name;
	std::string	nick_name;
	std::string	phone_number;
	std::string	darkest_secret;

	this->_index = index;
	this->_contact[index].set_index(index);
	std::cout << "first name : ";
	std::getline(std::cin, first_name);
	this->_contact[index].set_first_name(first_name);
	std::cout << "last name : ";
	std::getline(std::cin, last_name);
	this->_contact[index].set_last_name(last_name);
	std::cout << "nick name : ";
	std::getline(std::cin, nick_name);
	this->_contact[index].set_nick_name(nick_name);
	std::cout << "phone number : ";
	std::getline(std::cin, phone_number);
	this->_contact[index].set_phone_number(phone_number);
	std::cout << "darkest secret : ";
	std::getline(std::cin, darkest_secret);
	this->_contact[index].set_darkest_secret(darkest_secret);
}

void	PhoneBook::search_screen(void)
{
	std::string	first_name;
	std::string	last_name;
	std::string	nick_name;
	if (this->flag == 0)
	{
		for (int i = 0; i <= this->_index; i++)
		{
			first_name = this->_contact[i].get_first_name();
			last_name = this->_contact[i].get_last_name();
			nick_name = this->_contact[i].get_nick_name();
			std::cout << std::setw(10) << "index" << "|";
			std::cout << std::setw(10) << "first name" << "|";
			std::cout << std::setw(10) << "last name" << "|";
			std::cout << std::setw(10) << "nick name" << std::endl;
			std::cout << std::setw(10) << this->_contact[i].get_index() << "|";
			std::cout << std::setw(10) << ft_truncate(first_name) << "|";
			std::cout << std::setw(10) << ft_truncate(last_name) << "|";
			std::cout << std::setw(10) << ft_truncate(nick_name) << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			first_name = this->_contact[i].get_first_name();
			last_name = this->_contact[i].get_last_name();
			nick_name = this->_contact[i].get_nick_name();
			std::cout << std::setw(10) << "index" << "|";
			std::cout << std::setw(10) << "first name" << "|";
			std::cout << std::setw(10) << "last name" << "|";
			std::cout << std::setw(10) << "nick name" << std::endl;
			std::cout << std::setw(10) << this->_contact[i].get_index() << "|";
			std::cout << std::setw(10) << ft_truncate(first_name) << "|";
			std::cout << std::setw(10) << ft_truncate(last_name) << "|";
			std::cout << std::setw(10) << ft_truncate(nick_name) << std::endl;
		}
	}
}

void	PhoneBook::show_contact(int index)
{
	std::cout << "first name : " << this->_contact[index].get_first_name() << std::endl;
	std::cout << "last name : " << this->_contact[index].get_last_name() << std::endl;
	std::cout << "nick name : " << this->_contact[index].get_nick_name() << std::endl;
	std::cout << "phone number : " << this->_contact[index].get_phone_number() << std::endl;
	std::cout << "darkest secret : " << this->_contact[index].get_darkest_secret() << std::endl;
}

std::string	ft_truncate(std::string str)
{
	if (str.length() > 10)
	{
		str.resize(9);
		str.append(".");
	}
	return (str);
}
