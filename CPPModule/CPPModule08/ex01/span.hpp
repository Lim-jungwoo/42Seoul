/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 08:26:17 by jlim              #+#    #+#             */
/*   Updated: 2022/03/01 08:26:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <algorithm>
# include <exception>
# include <numeric>
# include <iostream>
# include <vector>

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define RESET "\e[0m"

class Span
{
	private:
		std::vector<int>	_data;
	
		Span();
	
	public:
		~Span();
		Span(unsigned int n);
		Span(const Span& s);
		Span&	operator=(const Span& s);

		void	addNumber(int value);

		unsigned int	shortestSpan();
		unsigned int	longestSpan();

		class Abs {
			public:
				int	operator()(const int& i) {return (std::abs(i));}
		};
		class NoStoreException : public std::exception {
			public:
				const char* what() const throw();
		};
		class NoSpanException : public std::exception {
			public:
				const char* what() const throw();
		};

		const std::vector<int>&	getData() const;

		template <typename T>
		void	addRange(T begin, T end)
		{
			if (std::distance(begin, end) > static_cast<int>(_data.capacity() - _data.size()))
				throw NoStoreException();
			while (begin != end)
				_data.push_back(*begin++);
		}
};

#endif
