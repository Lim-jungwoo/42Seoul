/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:04:57 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:04:57 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>
# include <sstream>

class	Zombie {
	private:
		std::string	_name;
	public:
		void	announce(void);
		Zombie(std::string name);
		Zombie(void);
		~Zombie(void);
		void	set_name(std::string name);
};

Zombie	*zombieHorde( int N, std::string name );
int	is_number(std::string str);

#endif
