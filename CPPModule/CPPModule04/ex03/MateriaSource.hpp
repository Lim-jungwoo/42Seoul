/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:39:17 by jlim              #+#    #+#             */
/*   Updated: 2022/02/23 12:39:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"


class MateriaSource : public IMateriaSource
{
private:
	AMateria*	_am[4];
	
public:
	MateriaSource();
	virtual	~MateriaSource();
	MateriaSource(MateriaSource const &ms);
	
	MateriaSource	&operator=(MateriaSource const &ms);

	AMateria const	*getAMateria(int idx) const;
	void			learnMateria(AMateria *am);
	AMateria		*createMateria(std::string const &type);
};

#endif