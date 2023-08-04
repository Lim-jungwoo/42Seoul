/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:56:56 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 18:56:57 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include <string>

int	main(int argc, char **argv)
{
	std::string	str;
	std::string	ret;
	int			i;
	int			j;

	if (argc <= 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (i = 1; i < argc; i++)
		{
			str = argv[i];
			for (j = 0; str[j]; j++)
			{
				ret = static_cast<char>(std::toupper(str[j]));
				std::cout << ret;
			}
		}
		std::cout << std::endl;
	}
	return (0);
}
