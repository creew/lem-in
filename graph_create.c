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

static t_result		add_neigbor_room(t_roomdata *rdata, t_roomdata *neigbor)
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

static t_roomdata	*find_min_weight(t_roomarr *arr)
{
	t_roomdata	*rdata;
	t_roomdata	*cur;
	size_t		size;

	rdata = NULL;
	size = arr->num_elems;
	while (size--)
	{
		if (ft_array_get(arr, size, (void **)&cur) == 0)
		{
			if (cur->visited == 0 && cur->weigth != FT_INTMAX)
			{
				if (rdata == NULL || cur->weigth < rdata->weigth)
					rdata = cur;
			}
		}
	}
	return (rdata);
}

static t_result		dijkstra_algo(t_lemin *lem)
{
	t_roomdata		*rdata;
	t_neigborlst	*neigborlst;
	t_neigbor		*neigbor;

	rdata = find_room_by_cmd(&lem->rooms, LEM_CMD_END);
	rdata->weigth = 0;
	while ((rdata = find_min_weight(&lem->rooms)))
	{
		neigborlst = rdata->neigborlst;
		while (neigborlst)
		{
			neigbor = (t_neigbor *)neigborlst->content;
			if (rdata->weigth + neigbor->weight < neigbor->room->weigth)
			{
				neigbor->room->weigth = rdata->weigth + neigbor->weight;
				neigbor->room->prev = rdata;
			}
			neigborlst = neigborlst->next;
		}
		rdata->visited = 1;
	}
	return (RET_OK);
}

t_result			graph_create(t_lemin *lem)
{
	t_roomdata	*rdata;
	char		*oppname;
	int			count;
	t_roomdata	*rdata2;
	size_t		size;

	size = ft_array_size(&lem->rooms);
	while (size--)
	{
		count = 0;
		if (ft_array_get(&lem->rooms, size, (void **)&rdata) == 0)
		{
			while ((oppname =
				getlink_by_name(&lem->links, rdata->name, count++)) != NULL)
			{
				rdata2 = find_room_by_name(&lem->rooms, oppname);
				if (rdata2 == NULL)
					return (ERR_WRONG_LINK_ROOM);
				if (add_neigbor_room(rdata, rdata2) != RET_OK)
					return (ERR_ENOMEM);
			}
		}
	}
	dijkstra_algo(lem);
	return (RET_OK);
}
