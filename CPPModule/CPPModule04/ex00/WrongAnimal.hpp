/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:38:29 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 15:38:29 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

# define A_T "Animal"
# define D_T "Dog"
# define C_T "Cat"

class WrongAnimal
{
public:
	WrongAnimal();
	virtual	~WrongAnimal();
	WrongAnimal(WrongAnimal const &w_a);
	WrongAnimal(std::string name);

	WrongAnimal	&operator=(WrongAnimal const &w_a);

	void			makeSound() const;
	void			setType(std::string type);
	std::string		getType() const;

protected:
	std::string	type;
};

#endif