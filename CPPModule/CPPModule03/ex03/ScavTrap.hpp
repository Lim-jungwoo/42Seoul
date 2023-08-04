/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:32:27 by jlim              #+#    #+#             */
/*   Updated: 2022/02/18 19:32:29 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

# define S_HP 100
# define S_EP 50
# define S_AD 20

class ScavTrap : virtual public ClapTrap
{
public:
	ScavTrap();
	virtual ~ScavTrap();
	ScavTrap(ScavTrap const &scav);
	ScavTrap(std::string name);

	ScavTrap	&operator=(ScavTrap const &scav);

	void	attack(std::string const &target);
	void	guardGate(void);
};

#endif