# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/22 14:53:52 by dromansk          #+#    #+#              #
#    Updated: 2020/01/18 23:16:43 by dromansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_retro

FLAGS = -Wall -Werror -Wextra

I = -I ./inc

SRC = ./src/main.cc ./src/classes/*.cc

LIB = -lncurses

all: $(NAME)

$(NAME):
	clang++ $(FLAGS) $(I) $(SRC) $(LIB) -o $(NAME)

debug:
	clang++ -g $(FLAGS) $(I) $(SRC) $(LIB) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
