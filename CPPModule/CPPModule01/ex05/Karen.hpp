/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:36:25 by jlim              #+#    #+#             */
/*   Updated: 2022/02/13 15:36:26 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KAREN_HPP
# define KAREN_HPP

# include <iostream>
# include <string>

class Karen
{
private:
	void	debug( void );
	void	info( void );
	void	warning( void );
	void	error( void );
public:
	void	complain( std::string level );
	Karen(void);
	~Karen(void);
};

#endif