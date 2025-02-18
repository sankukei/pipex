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

all: client server

client:
	gcc -o client client.c

server:
	gcc -o server server.c

clean:
	rm -f client && rm -f server 

fclean: clean

re: fclean all
		
.PHONY: all, clean, fclean, re, bonus
