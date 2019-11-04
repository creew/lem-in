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

typedef struct	s_ldata
{
	char	*name;
	int		x;
	int		y;
}				t_ldata;

typedef struct	s_rooms
{
	struct s_rooms	*children;
	struct s_rooms	*next;
	t_ldata			*room;
}				t_rooms;

typedef struct	s_lemin
{
	int		number_ants;
}				t_lemin;

#endif
