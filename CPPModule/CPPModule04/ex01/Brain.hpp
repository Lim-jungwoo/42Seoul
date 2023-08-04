/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:35:22 by jlim              #+#    #+#             */
/*   Updated: 2022/02/22 16:35:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include "Animal.hpp"
# include <sstream>

class Brain
{
private:
	std::string	_ideas[100];
public:
	Brain();
	~Brain();
	Brain(Brain const &brain);
	
	Brain	&operator=(Brain const &brain);

	std::string	*get_ideas();
	void		set_ideas(std::string *ideas);
	void		change_ideas(std::string ideas);
};

#endif