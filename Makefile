# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/04 13:56:11 by rvaz-da-          #+#    #+#              #
#    Updated: 2026/06/08 16:03:25 by rvaz-da-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

CC = cc

FLAGS = -Wall -Werror -Wextra -pthread -g

SRC = src/codexion.c src/init/parsing.c src/init/inits.c \
	src/utils/memory_utils.c src/utils/utils.c \
	src/simulation/simulation.c src/simulation/thread_routines/monitoring.c \
	src/simulation/thread_routines/routine.c src/simulation/dongles/dongles.c \
	src/simulation/dongles/dongles_utils.c src/simulation/heap/heap.c \
	src/simulation/heap/heap_utils.c \
	
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

