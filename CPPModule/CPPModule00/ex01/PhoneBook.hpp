/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:36:17 by jlim              #+#    #+#             */
/*   Updated: 2022/01/23 21:36:18 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iomanip>

std::string	ft_truncate(std::string str);

class PhoneBook
{
private:
	int	_index;
	Contact	_contact[8];

public:
	int		flag;
	void	search_screen(void);
	void	add_contact(int index);
	void	reset_index(void);
	void	show_contact(int index);
};

#endif
