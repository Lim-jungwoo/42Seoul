/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:18:31 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:18:32 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

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

class ICharacter;

class AMateria
{
protected:
	std::string	_type;

public:

	AMateria(std::string const & type);

	std::string const & getType() const;

	virtual AMateria* clone() const = 0;
	virtual void	use(ICharacter& target);

	AMateria();
	virtual ~AMateria();
	AMateria(AMateria const &am);

	AMateria	&operator=(AMateria const &am);
};

#endif