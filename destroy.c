/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:02:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 10:02:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	delneighlst(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

static void	delroomlinkarr(void *data)
{
	ft_memdel(&data);
}

static void	dellsts(void *data)
{
	t_roomdata	*rdata;

	rdata = (t_roomdata *)data;
	ft_lstdel(&rdata->neigborlst, delneighlst);
}

void		delete_all(t_lemin *lem)
{
	ft_array_foreach(&lem->rooms, dellsts);
	ft_array_remove_all(&lem->rooms, delroomlinkarr);
	ft_array_remove_all(&lem->links, delroomlinkarr);
	remove_all_paths(&lem->paths);
}
