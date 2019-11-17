#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 12:15:31 by eklompus          #+#    #+#              #
#    Updated: 2019/11/17 13:47:33 by eleonard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ALL_C =	lemin.c \
		lem_list.c \
		read_input.c \
		rooms_parse.c \
		line_parse.c \
		links_parse.c \
		print.c \
		check_all.c \
		graph_create.c

SRCDIR = srcs/
OBJDIR = objs/

ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR), $(ALL_OBJ))

NAME = lem-in

INCLUDES = ./includes/lemin.h ./libft/includes/libft.h ./libft/includes/get_next_line.h

COMP_LIB = make -C libft/

FLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $^ -L ./libft -lft -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCLUDES)
	@/bin/mkdir -p $(OBJDIR)
	gcc $(FLAGS) -I./includes -I./libft/includes -c $< -o $@

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(COMP_LIB) fclean

re: fclean all

.PHONY: lib clean fclean all re

