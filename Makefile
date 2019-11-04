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

CC_FLAGS = -Wall -Wextra

SRCS = lem-in.c

OBJS = $(SRCS:.c=.o)

INC_DIR = ./libft

INC_FLAG = $(addprefix -I,$(INC_DIR))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CC_FLAGS) $^ -L./libft -lft -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(NAME)

re: fclean all
