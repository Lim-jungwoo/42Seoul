/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 13:47:42 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 13:47:43 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class	Zombie {
	private:
		std::string	_name;
	public:
		void	announce(void);
		Zombie(std::string name);
		Zombie(void);
		~Zombie(void);
};

Zombie	*newZombie( std::string name );
void	randomChump( std::string name );

#endif
