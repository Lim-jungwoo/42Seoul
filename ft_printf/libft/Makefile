# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 12:03:31 by jlim              #+#    #+#              #
#    Updated: 2020/12/24 10:14:44 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

TARGET = libft.a
SOURCES = *.c
OBJECTS = *.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	ar -r $(TARGET) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

clean :
	rm -f $(OBJECTS)
fclean : clean
	rm -f $(TARGET)
compile :
	$(CC) -Wall -Wextra -Werror $(SOURCES)
re : fclean all
