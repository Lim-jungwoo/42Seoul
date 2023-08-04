/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:15:44 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 13:15:45 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

# define d_name "Default"
# define d_grade 150

class Form;

class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;
public:
	Bureaucrat();
	~Bureaucrat();
	Bureaucrat(Bureaucrat const &bure);
	Bureaucrat(std::string name, int grade);

	Bureaucrat	&operator=(Bureaucrat const &bure);

	class GradeTooHighException : public std::exception {
		const char *what() const throw();
	};
	class GradeTooLowException : public std::exception {
		const char *what() const throw();
	};
	
	std::string	getName() const;
	int			getGrade() const;
	void		increment_grade();
	void		decrement_grade();

	void	signForm(Form *form);
};

std::ostream	&operator<<(std::ostream &out, const Bureaucrat &bure);

#endif