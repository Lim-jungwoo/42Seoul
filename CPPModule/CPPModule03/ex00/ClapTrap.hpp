/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:12 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 16:43:12 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

# define d_name "default"
# define c_h	10
# define c_e	10
# define c_d	0

class ClapTrap
{
private:
	std::string		_name;
	unsigned int	_hitpoints;
	unsigned int	_energy_points;
	unsigned int	_attack_damage;
	
public:
	ClapTrap();
	~ClapTrap();
	ClapTrap(ClapTrap const &clap);
	ClapTrap(std::string _name);

	ClapTrap	&operator=(ClapTrap const &clap);

	void	attack(std::string const &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif