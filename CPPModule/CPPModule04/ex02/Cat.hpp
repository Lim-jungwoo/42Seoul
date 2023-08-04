/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:19:20 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 14:19:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
private:
	Brain	*_brain;

public:
	Cat();
	~Cat();
	Cat(Cat const &cat);
	Cat(std::string name);

	Cat	&operator=(Cat const &cat);

	void	makeSound() const;
	std::string	*getBrain() const;
	void	setBrain(std::string *idea);
};

#endif