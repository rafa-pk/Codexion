# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/06 13:06:47 by rvaz-da-          #+#    #+#              #
#    Updated: 2026/05/06 13:06:49 by rvaz-da-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRC = src/codexion.c src/parsing.c src/utils.c src/routine/monitor.c \
	src/routine/routine.c src/routine/routine_functions.c \
	src/simulation/init_simulation.c src/simulation/simulation.c
	
OBJ = $(SRC:.c=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re