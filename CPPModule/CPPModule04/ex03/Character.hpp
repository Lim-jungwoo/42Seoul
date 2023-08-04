/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:38:39 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:38:39 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

class Character : public ICharacter
{
private:
	AMateria*	_am[4];
	std::string	_name;

public:
	Character();
	virtual ~Character();
	Character(Character const &c);
	Character(std::string const &name);

	Character	&operator=(Character const &c);

	const AMateria	*getAMateria(int idx) const;
	std::string const & getName() const;
	void	equip(AMateria* am);
	void	unequip(int idx);
	void	use(int idx, ICharacter& target);
};

#endif