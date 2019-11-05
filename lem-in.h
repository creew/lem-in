/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:03:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/04 14:03:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

# include "libft.h"

# define RET_OK					(0)
# define ERR_READ_ANTS_NUMBER	(-1)
# define ERR_WRONG_ANTS_NUMBER	(-2)
# define ERR_GNL_ERROR			(-3)
# define ERR_ENOMEM				(-4)
# define ERR_WRONG_ROOM_NAME	(-5)
# define ERR_WRONG_ROOM_ARG		(-6)
# define ERR_WRONG_LINK			(-7)
# define ERR_WRONG_LINK_ROOM	(-8)
# define ERR_WRONG_ROOM_DUPL	(-9)
# define ERR_EMPTY_ROOM_NAME	(-10)
# define ERR_WRONG_LINK_TO_LINK	(-11)

# define LEM_CMD_NONE			(0)
# define LEM_CMD_START			(1)
# define LEM_CMD_END			(2)

typedef struct	s_ldata
{
	int		x;
	int		y;
	int		cmd;
	char	name[1];
}				t_ldata;

typedef struct	s_rooms
{
	struct s_rooms	*children;
	struct s_rooms	*next;
	t_ldata			*room;
}				t_rooms;

typedef struct	s_lemin
{
	int		num_ants;
	t_list	*rooms;
}				t_lemin;

int			add_lem_list(t_list **root, const char *name,
							const int *xy, int cmd);

int			read_input(int fd, t_lemin *lem);

int			add_lem_room(t_lemin *lem, char *str, int cmd);
int			check_room_exist(t_list *rooms, const char *name);
int			check_room_valid(const char *name);

int			count_numbers(char *str);
char		*get_next_word(char *str, int *last);
#endif
