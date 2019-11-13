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

static t_result	add_neigbor_room(t_roomdata *rdata, t_roomdata *neigbor)
{
	t_neigborlst	*neigh;
	t_neigbor		*ndata;

	neigh = ft_lstaddblank(&rdata->lst, sizeof(t_neigbor));
	if (neigh == NULL)
		return (ERR_ENOMEM);
	ndata = (t_neigbor *)neigh->content;
	ndata->room = neigbor;
	ndata->weight = 1;
	return (RET_OK);
}


static int 		have_not_visited(t_roomlst *lst)
{
	t_roomdata *rdata;

	while (lst)
	{
		rdata = (t_roomdata *)lst->content;
		if (!rdata->visited)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static t_roomdata *find_min_weight(t_roomlst *lst)
{
	t_roomdata *rdata;
	t_roomdata *cur;

	rdata = NULL;
	while (lst)
	{
		cur = (t_roomdata *)lst->content;
		if (cur->visited == 0 && cur->weigth != FT_INTMAX)
		{
			if (rdata == NULL || cur->weigth < rdata->weigth)
				rdata = cur;
		}
		lst = lst->next;
	}
	return (rdata);
}

static t_result	dijkstra_algo(t_lemin *lem)
{
	t_roomdata		*rdata;
	t_neigborlst	*neigborlst;
	t_neigbor		*neigbor;

	rdata = find_room_by_cmd(lem->rooms, LEM_CMD_START);
	rdata->weigth = 0;
	while ((rdata = find_min_weight(lem->rooms)))
	{
		neigborlst = rdata->lst;
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

t_result		graph_create(t_lemin *lem)
{
	t_roomlst	*rlst;
	t_roomdata	*rdata;
	char 		*oppname;
	int 		count;
	t_roomdata	*rdata2;

	rlst = lem->rooms;
	while (rlst)
	{
		count = 0;
		rdata = (t_roomdata *)rlst->content;
		while ((oppname = getlink_by_name(lem->links, rdata->name, count))
			!= NULL)
		{
			rdata2 = find_room_by_name(lem->rooms, oppname);
			if (rdata2 == NULL)
				return (ERR_WRONG_LINK_ROOM);
			if (add_neigbor_room(rdata, rdata2) != RET_OK)
				return (ERR_ENOMEM);
			count++;
		}
		rlst = rlst->next;
	}
	dijkstra_algo(lem);
	return (RET_OK);
}
