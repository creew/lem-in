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


typedef struct	s_ldata
{
	int		x;
	int		y;
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
	t_list	*lem_list;
}				t_lemin;

int			add_lem_list(t_list **root, char *name, int x, int y);

#endif
