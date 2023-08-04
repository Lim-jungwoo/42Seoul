/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:29:52 by jlim              #+#    #+#             */
/*   Updated: 2022/02/19 14:29:53 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

# define F_HP 100
# define F_EP 100
# define F_AD 30

class	FragTrap : public ClapTrap
{
	public:
		FragTrap();
		~FragTrap();
		FragTrap(FragTrap const &frag);
		FragTrap(std::string name);

		FragTrap	&operator=(FragTrap const &frag);

		void	highFivesGuys(void);
};

#endif