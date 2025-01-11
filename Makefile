# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leothoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 14:10:04 by leothoma          #+#    #+#              #
#    Updated: 2025/01/11 14:10:05 by leothoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = server
NAME2 = client

COMP = cc

FLAGS = -Wall -Wextra -Werror -g3 -I ./

SRC =	server.c \
	client.c \

all:
	${COMP} ${FLAGS} ${SRC}

clean:
	rm -f ${OBJS} 

fclean: clean;
	rm -f server client

re: fclean all
		
.PHONY: all, clean, fclean, re, bonus

