/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:17:21 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:17:22 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

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

class Animal
{
public:
	Animal();
	virtual	~Animal();
	Animal(Animal const &animal);
	Animal(std::string name);

	Animal	&operator=(Animal const &animal);

	virtual void	makeSound() const = 0;
	void			setType(std::string type);
	std::string		getType() const;
protected:
	std::string	type;
};

#endif