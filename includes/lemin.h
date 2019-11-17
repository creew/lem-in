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

#ifndef _LEMIN_H
# define _LEMIN_H

# include "libft.h"

typedef	int			t_result;
typedef t_ftarray	t_roomarr;
typedef t_ftarray	t_linkarr;
typedef t_list		t_neigborlst;

# define RET_OK					(0)
# define ERR_READ_ANTS_NUMBER	(-1)
# define ERR_WRONG_ANTS_NUMBER	(-2)
# define ERR_GNL_ERROR			(-3)
# define ERR_ENOMEM				(-4)
# define ERR_WRONG_ROOM_NAME	(-5)
# define ERR_WRONG_ROOM_ARG		(-6)
# define ERR_WRONG_LINK			(-7)
# define ERR_WRONG_LINK_ROOM	(-8)
# define ERR_ROOM_NAME_DUPL 	(-9)
# define ERR_EMPTY_ROOM_NAME	(-10)
# define ERR_WRONG_LINK_TO_LINK	(-11)
# define ERR_NO_START_OR_END 	(-12)
# define ERR_LINK_DUPL 			(-13)
# define ERR_ROOM_XY_DUPL		(-14)
# define ERR_NO_LINKS			(-15)
# define ERR_NO_PATH			(-16)

# define LEM_CMD_NONE			(0)
# define LEM_CMD_START			(1)
# define LEM_CMD_END			(2)

typedef struct	s_roomdata
{
	int					x;
	int					y;
	int					cmd;
	int 				weigth;
	struct s_roomdata	*prev;
	int 				visited;
	t_neigborlst		*neigborlst;
	char				name[1];
}				t_roomdata;

typedef struct	s_linkdata
{
	char		*l1;
	char		*l2;
	char		ldata[2];
}				t_linkdata;

typedef struct	s_neigbor
{
	t_roomdata	*room;
	int 		weight;
}				t_neigbor;

typedef struct	s_lemin
{
	int			num_ants;
	t_roomarr	rooms;
	t_linkarr	links;
}				t_lemin;

t_result		add_lem_list(t_roomarr *arr, const char *name,
						 const int *xy, int cmd);

t_result		read_input(int fd, t_lemin *lem);

t_result		add_lem_room(t_lemin *lem, char *str, int cmd);
t_roomdata		*find_room_by_name(t_roomarr *rooms, const char *name);
int				check_room_valid(const char *name);

char			*getlink_by_name(t_linkarr *lst, const char *name, int n);
t_result		add_lem_link(t_lemin *lem, char *str);

int				count_numbers(char *str);
char			*get_next_word(char *str, int *last);

void			print_rooms(t_roomarr *rooms);
void			print_links(t_linkarr *links);
void			print_neighbors(t_roomarr *rooms);

t_result		check_all(t_lemin *lem);
t_roomdata		*find_room_by_cmd(t_roomarr *rooms, int cmd);

t_result		graph_create(t_lemin *lem);
#endif
