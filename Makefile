# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/06 13:06:47 by rvaz-da-          #+#    #+#              #
#    Updated: 2026/05/16 17:17:46 by rvaz-da-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

CC = cc

FLAGS = -Wall -Werror -Wextra -pthread -g

SRC = src/codexion.c src/init/parsing.c src/utils/utils.c src/sim/coder_actions.c \
	src/sim/routines.c src/utils/memory_utils.c src/init/inits.c  src/sim/simulation.c \
	src/sim/dongles.c src/heap/heap.c src/heap/heap_utils.c src/utils/dongle_utils.c
	
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
