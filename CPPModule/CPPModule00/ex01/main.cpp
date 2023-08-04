/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:36:23 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 21:36:25 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	is_number(std::string input)
{
	for (int i = 0; input[i]; i++)
	{
		if (input[i] >= '0' && input[i] <= '9')
			continue ;
		else
			return (0);
	}
	return (1);
}

int	main(void)
{
	PhoneBook	my_phonebook;
	std::string	input;
	int			index = 0;
	int			search_index;

	my_phonebook.flag = 0;
	while (1)
	{
		std::cout << "please enter the command (ADD, SEARCH, EXIT)" << std::endl;
		std::getline(std::cin, input);
		if (index == 8)
		{
			index = 0;
			my_phonebook.reset_index();
			my_phonebook.flag = 1;
		}
		if (input == "ADD")
		{
			my_phonebook.add_contact(index);
			index++;
		}
		else if (input == "SEARCH")
		{
			if (index == 0 && my_phonebook.flag == 0)
			{
				std::cout << "there is no contact" << std::endl;
				continue ;
			}
			my_phonebook.search_screen();
			std::cout << "enter the index to find" << std::endl;
			while (1)
			{
				std::getline(std::cin, input);
				if (input == "" || is_number(input) == 0)
				{
					std::cout << "please enter the number" << std::endl;
					continue ;
				}
				else
				{
					search_index = std::stoi(input);
					if (search_index >= index && my_phonebook.flag == 0)
					{
						std::cout << "there is no contact" << std::endl;
						break ;
					}
					if (search_index >= 0 && search_index <= 7)
					{
						my_phonebook.show_contact(search_index);
						break ;
					}
					std::cout << "please enter the number (0~7)" << std::endl;
				}
			}
		}
		else if (input == "EXIT")
		{
			std::cout << "quit the program" << std::endl;
			return (0);
		}
		else
			std::cout << input << " is wrong command" << std::endl;
	}
	return (0);
}
