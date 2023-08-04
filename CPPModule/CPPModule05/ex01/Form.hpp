/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:44:23 by jlim              #+#    #+#             */
/*   Updated: 2022/02/24 16:44:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include "Bureaucrat.hpp"

# define d_is_sign 0
# define d_grade_sign 50
# define d_grade_exec 70

class Form
{
private:
	const std::string	_name;
	bool				_is_signed;
	const int			_grade_sign;
	const int			_grade_exec;

public:
	Form();
	~Form();
	Form(Form const &form);
	Form(std::string name, int grade_sign, int grade_exec);

	Form	&operator=(Form const &form);

	class GradeTooHighException : public std::exception {
		const char *what() const throw();
	};
	class GradeTooLowException : public std::exception {
		const char *what() const throw();
	};

	std::string	getName() const;
	bool		getSigned() const;
	int			getGradeSign() const;
	int			getGradeExec() const;
	void		beSigned(Bureaucrat *bure);
};

std::ostream	&operator<<(std::ostream &out, const Form &form);

#endif