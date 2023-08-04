/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:36:19 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 15:36:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int	main(void)
{
	Karen	test;

	std::cout << "[ DEBUG ]" << std::endl;
	test.complain("DEBUG");
	std::cout << "[ INFO ]" << std::endl;
	test.complain("INFO");
	std::cout << "[ WARNING ]" << std::endl;
	test.complain("WARNING");
	std::cout << "[ ERROR ]" << std::endl;
	test.complain("ERROR");
}

