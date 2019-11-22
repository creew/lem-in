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

typedef	int				t_result;
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef t_ftarray		t_roomarr;
typedef t_ftarray		t_linkarr;
typedef t_ftarray		t_patharr;
typedef t_ftarray		t_path;

# define RET_RECALC					(1)
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
# define LEM_CMD_UNKNOWN		(3)

# define M_LINK					(1u << 0u)
# define DIJKSTRA_VIS			(1u << 1u)
# define MEHMET_VIS				(1u << 2u)

typedef struct	s_md
{
	t_uchar		dij_vis:1;
	t_uchar		path_vis:1;
	t_uchar		splitted:1;
	char 		in:2;
	char		ex:2;
}				t_md;

typedef struct	s_wd
{
	int			win:16;
	int 		wout:16;
}				t_wd;

typedef struct	s_matrix
{
	t_md		*m;
	t_wd		*weights;
	size_t		size;
}				t_matrix;

typedef struct	s_roomdata
{
	size_t		index;
	int			x;
	int			y;
	int			ant_index;
	int			ant_count;
	char		cmd;
	char		name[1];
}				t_roomdata;

typedef struct	s_linkdata
{
	t_roomdata	*left;
	t_roomdata	*right;
}				t_linkdata;

typedef	struct	s_borders
{
	t_roomdata	*start;
	t_roomdata	*end;
}				t_borders;

typedef struct	s_lemin
{
	int			num_ants;
	t_roomarr	rooms;
	t_linkarr	links;
	t_patharr	paths;
	t_borders	se;
	int			is_debug;
	int 		is_colorized;
	int			fd;
	t_matrix	matrix;
}				t_lemin;

typedef struct	s_pathdata
{
	int			visited;
	size_t		size;
	t_path		*path;
}				t_pathdata;

t_result		read_input(int fd, t_lemin *lem);

t_result		add_lem_room(t_lemin *lem, char *str, char cmd);
t_roomdata		*find_room_by_name(t_roomarr *rooms, const char *name);

t_result		add_lem_link(t_lemin *lem, char *str);

int				count_numbers(char *str);
char			*get_next_word(char *str, int *last);

void			print_rooms(t_roomarr *rooms);
void			print_links(t_linkarr *links);
void			print_neighbors(t_matrix *matrix, t_roomarr *rooms);
void			print_paths(t_patharr *parr);

t_result		check_all(t_lemin *lem);

t_result		graph_create(t_lemin *lem);

void			remove_all_paths(t_patharr *parr);
t_result		add_path_to_arr(t_patharr *parr, t_path *path);

t_result		mehmet_algo(t_matrix *matrix, t_roomarr *rooms,
					t_patharr *paths, t_borders *se);
t_result		add_room_to_path(t_path *path, t_roomdata *room);
t_result		find_all_paths(t_lemin *lem);

int				calc_total_len(t_patharr *paths, int count);
t_result		dijkstra_algo(t_matrix *matrix, t_roomarr *rooms,
					t_borders *se);

void			delete_all(t_lemin *lem);

void			print_given_data(t_lemin *lem);
void			print_solution(t_lemin *lem);

t_result		matrix_create(t_matrix *matrix, size_t size);

void			matrix_set_flag(t_matrix *matrix, size_t room, size_t flag);
t_uchar			matrix_get_flag(t_matrix *matrix, size_t room);
t_uchar			matrix_get_link(t_matrix *matrix, size_t room1, size_t room2);
void			matrix_add_neighbor(t_matrix *matrix, t_linkdata *link);
void			matrix_rem_neighbor(t_matrix *matrix, t_linkdata *link);

void			matrix_cpy(t_matrix *dst, const t_matrix *src);
t_result		matrix_dup(t_matrix *dst, const t_matrix *src);

void			suurballe_algo(
	t_matrix *matrix, t_roomarr *rooms, t_patharr *paths, t_borders *se);
#endif
