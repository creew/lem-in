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
typedef t_ftarray	t_patharr;
typedef t_list		t_path;

# define RET_OK						(0)
# define ERR_READ_ANTS_NUMBER		(-1)
# define ERR_WRONG_ANTS_NUMBER		(-2)
# define ERR_GNL_ERROR				(-3)
# define ERR_ENOMEM					(-4)
# define ERR_WRONG_ROOM_NAME		(-5)
# define ERR_WRONG_ROOM_ARG			(-6)
# define ERR_WRONG_LINK				(-7)
# define ERR_WRONG_LINK_ROOM		(-8)
# define ERR_ROOM_NAME_DUPL 		(-9)
# define ERR_EMPTY_ROOM_NAME		(-10)
# define ERR_WRONG_LINK_TO_LINK		(-11)
# define ERR_NO_START_OR_END 		(-12)
# define ERR_LINK_DUPL 				(-13)
# define ERR_ROOM_XY_DUPL			(-14)
# define ERR_NO_LINKS				(-15)
# define ERR_NO_PATH				(-16)
# define ERR_INCORRECT_PATH_REMOVE	(-17)
# define ERR_CMD_NOT_FOUNDED		(-18)

# define LEM_CMD_NONE			(0)
# define LEM_CMD_START			(1)
# define LEM_CMD_END			(2)

typedef struct	s_roomdata
{
	size_t		index;
	int			x;
	int			y;
	int 		weigth;
	char		cmd;
	char 		visited;
	char 		meh_visit;
	int			ant_index;
	char		name[1];
}				t_roomdata;

typedef struct	s_linkdata
{
	size_t		left;
	size_t		right;
}				t_linkdata;

typedef struct	s_lemin
{
	int			num_ants;
	t_roomarr	rooms;
	t_linkarr	links;
	t_patharr	paths;
	char 		*matrix;
}				t_lemin;

typedef struct	s_pathdata
{
	int			visited;
	size_t		size;
	t_path		*path;
}				t_pathdata;

t_result		add_roomdata(t_roomarr *arr, const char *name,
					const int *xy, int cmd);

t_result		read_input(int fd, t_lemin *lem);

t_result		add_lem_room(t_lemin *lem, char *str, int cmd);
t_roomdata		*find_room_by_name(t_roomarr *rooms, const char *name);
int				check_room_valid(const char *name);

t_result		get_opposite_roomlink(
					t_linkarr *larr, size_t	room_index, int n, size_t *index);
t_result		add_lem_link(t_lemin *lem, char *str);

int				count_numbers(char *str);
char			*get_next_word(char *str, int *last);

void			print_rooms(t_roomarr *rooms);
void			print_links(t_roomarr *arr, t_linkarr *links);
void			print_neighbors(const char *matrix, t_roomarr *rooms);
void			print_paths(t_patharr *parr);

t_result		check_all(t_lemin *lem);
t_roomdata		*find_room_by_cmd(t_roomarr *rooms, int cmd);

t_result		graph_create(t_lemin *lem);

void 			remove_all_paths(t_patharr *parr);
t_result		add_path_to_arr(t_patharr *parr, t_path *path);

t_result		mehmet_algo(char *matrix, t_roomarr *rooms, t_patharr *paths);
t_result		add_room_to_path(t_path **path, t_roomdata *room);
t_result		find_all_paths(t_lemin *lem);

int				calc_total_len(t_patharr *paths, int count);
t_result		dijkstra_algo(const char *matrix, t_roomarr *rooms);

void			delete_all(t_lemin *lem);

void			add_neigbor_room(t_lemin *lem, t_linkdata *link);
void			rem_neigbor_room(t_lemin *lem, t_linkdata *link);
#endif
