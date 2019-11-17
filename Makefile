#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 12:15:31 by eklompus          #+#    #+#              #
#    Updated: 2019/11/04 12:22:47 by eklompus         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

CC = gcc

CC_FLAGS = -Wall -Wextra -g3 -O3

SRCS =	lemin.c \
		lem_list.c \
		read_input.c \
		rooms_parse.c \
		line_parse.c \
		links_parse.c \
		print.c \
		check_all.c \
		graph_create.c \
		calc_total_len.c \
		paths_work.c \
		mehmet_algo.c \
		find_all_paths.c \
		dijkstra_algo.c \
		destroy.c

OBJS = $(SRCS:.c=.o)

INC_DIR = ./libft

INC_FLAG = $(addprefix -I,$(INC_DIR))

HEADERS = ./lemin.h

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CC_FLAGS) $^ -L./libft -lft -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all
