/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:54:38 by jlim              #+#    #+#             */
/*   Updated: 2022/02/27 17:54:39 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>
# include <string>
# include <cstdint>

# define d_s1 "abcd1234"
# define d_s2 "1234abcd"
# define d_n 1234

class	Data {
	private:
		std::string	_s1;
		int			_n;
		std::string	_s2;
	
	public:
		Data();
		~Data();
		Data(Data const &data);
		Data(std::string s1, int n, std::string s2);

		Data	&operator=(Data const &data);

		std::string	getS1() const;
		int			getInt() const;
		std::string	getS2() const;
};

std::ostream	&operator<<(std::ostream &out, Data const &data);

uintptr_t	serialize(Data *ptr);
Data		*deserialize(uintptr_t raw);

#endif
