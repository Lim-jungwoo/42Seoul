/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:38:25 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 14:38:26 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <iostream>
# include <string>

class Weapon
{
private:
	std::string	_type;
public:
	const std::string	&getType(void);
	void				setType(std::string type);
	Weapon(std::string type);
	Weapon(void);
	~Weapon(void);
};

#endif