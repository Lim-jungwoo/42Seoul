/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:28:24 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 15:28:24 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>

int	main(int argc, char **argv)
{
	std::string	name;

	if (argc != 4)
	{
		std::cout << "./replace filename string_to_change string_to_replace" << std::endl;
		return (0);
	}

	std::ifstream	input;
	input.open(argv[1]);
	if (input.fail())
	{
		std::cout << argv[1] << " open fail" << std::endl;
		input.close();
		return (0);
	}

	std::ofstream	output;
	name = argv[1];
	name.append(".replace");
	output.open(name);
	if (output.fail())
	{
		std::cout << name << " open fail" << std::endl;
		output.close();
		return (0);
	}

	std::string	content;
	do
	{
		std::getline(input, content);
		while (1)
		{
			size_t	idx = content.find(argv[2]);
			if (idx == std::string::npos)
			{
				output << content;
				break ;
			}
			output << content.substr(0, idx) << argv[3];
			content = content.substr(idx + std::strlen(argv[2]));
		}
		if (input.eof())
			break ;
		output << std::endl;
	} while (1);
	input.close();
	output.close();
	return (0);
}
