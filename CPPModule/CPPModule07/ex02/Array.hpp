/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:49:08 by jlim              #+#    #+#             */
/*   Updated: 2022/02/28 13:49:09 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <exception>

template <typename T>
class Array
{
private:
	unsigned int	_size;
	T*			_data;

public:
	Array() : _size(0), _data(NULL) {}
	~Array()
	{
		if (_size)
		{
			delete[] _data;
			_data = NULL;
		}
	}
	Array(unsigned int n) : _size(n), _data(NULL)
	{
		if (_size)
			_data = new T[_size];
	}
	Array(Array const &array) : _size(array.size()), _data(NULL)
	{
		if (_size)
			_data = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			_data[i] = array[i];
	}

	Array&	operator=(Array const &array)
	{
		if (this == &array)
			return (*this);
		if (_size)
		{
			delete[] _data;
			_data = NULL;
		}
		_size = array.size();
		if (_size)
			_data = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			_data[i] = array[i];
		return (*this);
	}

	T& operator[](long long i) const
	{
		if (i >= _size || i < 0)
		{
			std::cout << "i : " << i << std::endl;
			throw OutoflimitException();
		}
		return (_data[i]);
	}

	unsigned int	size() const
	{
		return (_size);
	}

	class OutoflimitException : public std::exception {
		const char* what() const throw()
		{
			return ("element is out of the limits");
		}
	};
};

#endif