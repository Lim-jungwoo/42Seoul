# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 12:18:18 by jlim              #+#    #+#              #
#    Updated: 2022/02/23 12:18:19 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = recap

SRCS = ./main.cpp ./AMateria.cpp ./Cure.cpp ./Ice.cpp\
		./Character.cpp ./MateriaSource.cpp
OBJS = $(SRCS:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
