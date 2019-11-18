#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 12:15:31 by eklompus          #+#    #+#              #
#    Updated: 2019/11/17 15:55:14 by eleonard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ALL_C =	lemin.c \
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
        		destroy.c \
        		ants_walk.c \
        		print_given_data.c

SRCDIR = ./srcs
OBJDIR = ./objs

ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = lem-in

INCLUDES = ./includes/lemin.h \
			./includes/ants_walk.h

COMP_LIB = make -C libft
COMP_PRINTF = make -C ft_printf

FLAGS = -Wall -Wextra -Werror

all: lib ft_printf $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $^ -L./libft -lft -L./ft_printf -lftprintf -o $@

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) ./libft/libft.a ./ft_printf/libftprintf.a | $(OBJDIR)
	gcc $(FLAGS) -I./includes -I./libft/includes -I./ft_printf/includes -c $< -o $@

lib:
	$(COMP_LIB)

ft_printf:
	$(COMP_PRINTF)

clean:
	/bin/rm -rf $(OBJDIR)
	$(COMP_LIB) clean
	$(COMP_PRINTF) clean

fclean: clean
	/bin/rm -rf $(NAME)
	$(COMP_LIB) fclean
	$(COMP_PRINTF) fclean

re: fclean all

.PHONY: lib ft_printf clean fclean all re
