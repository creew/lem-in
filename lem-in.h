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

#include "libft.h"

typedef struct	s_rooms
{
	struct s_rooms	*children;
	struct s_rooms	*next;
	int				x;
	int				y;
}				t_rooms;

typedef struct	s_lemin
{
	int		number_ants;
}				t_lemin;

#endif
