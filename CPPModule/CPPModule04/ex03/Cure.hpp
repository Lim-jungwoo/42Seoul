/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:23:59 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 13:24:00 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class Cure : public AMateria
{

public:
	Cure();
	virtual ~Cure();
	Cure(std::string const &type);
	Cure(Cure const &cure);

	Cure	&operator=(Cure const &cure);

	AMateria* clone() const;
	void	use(ICharacter &target);
};

#endif