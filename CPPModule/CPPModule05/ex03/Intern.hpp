/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:50:14 by jlim              #+#    #+#             */
/*   Updated: 2022/02/25 17:50:14 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"


class	Intern
{
	public:
		Intern();
		~Intern();
		Intern(Intern const &intern);

		Intern	&operator=(Intern const &intern);

		Form	*makeForm(std::string name, std::string target);

		class NoTypeException : public std::exception {
			const char *what() const throw();
		};
};

#endif