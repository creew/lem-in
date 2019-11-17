/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:40:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/06 09:40:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result		add_neigbor_room(t_roomdata *rdata, t_roomdata *neigbor)
{
	t_neigborlst	*neigh;
	t_neigbor		*ndata;

	neigh = ft_lstaddblank(&rdata->neigborlst, sizeof(t_neigbor));
	if (neigh == NULL)
		return (ERR_ENOMEM);
	ndata = (t_neigbor *)neigh->content;
	ndata->room = neigbor;
	ndata->weight = 1;
	return (RET_OK);
}

t_result		graph_create(t_lemin *lem)
{
	t_roomdata	*rdata;
	int			count;
	t_roomdata	*rdata2;
	size_t		size;

	size = ft_array_size(&lem->rooms);
	while (size--)
	{
		count = 0;
		if (ft_array_get(&lem->rooms, size, (void **)&rdata) == 0)
		{
			while ((rdata2 = get_opposite_roomlink_by_name(
				&lem->links, rdata->name, count++)) != NULL)
			{
				if (add_neigbor_room(rdata, rdata2) != RET_OK)
					return (ERR_ENOMEM);
			}
		}
	}
	dijkstra_algo(&lem->rooms);
	return (RET_OK);
}
