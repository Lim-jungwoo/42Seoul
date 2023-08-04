/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:22:16 by jlim              #+#    #+#             */
/*   Updated: 2022/02/26 16:22:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

int main(int argc, char **argv)
{
	
	if (argc != 2)
		std::cout << "./convert convert_to_input" << std::endl;

	else
		std::cout << Convert(argv[1]);
	/*
	char	*tmp = NULL;
	double	value1;
	float	value2;
	std::string	input = argv[1];

	value1 = std::strtod(input.c_str(), &tmp);
	std::cout << "origin double value : " << std::setprecision(std::numeric_limits<float>::digits10) << value1 << std::endl;
	std::cout << "after cast value : " << static_cast<float>(value1)  << std::endl;
	value2 = std::strtof(input.c_str(), &tmp);
	std::cout << "origin float value : " << value2 << std::endl;
	std::cout << "float limit : " << std::numeric_limits<float>::digits10 << std::endl;
	std::cout << "double limit : " << std::numeric_limits<double>::digits10 << std::endl;
	*/
	return (0);
}
