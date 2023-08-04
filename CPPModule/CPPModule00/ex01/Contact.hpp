/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:36:01 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 21:36:02 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class Contact
{
private:
	int	_index;
	std::string	_first_name;
	std::string	_last_name;
	std::string	_nick_name;
	std::string	_phone_number;
	std::string	_darkest_secret;

public:
	void	set_index(int _index);
	void	set_first_name(std::string _first_name);
	void	set_last_name(std::string _last_name);
	void	set_nick_name(std::string _nick_name);
	void	set_phone_number(std::string _phone_number);
	void	set_darkest_secret(std::string _darkest_secret);
	int		get_index(void);
	std::string	get_first_name(void);
	std::string	get_last_name(void);
	std::string get_nick_name(void);
	std::string	get_phone_number(void);
	std::string	get_darkest_secret(void);
};

#endif
