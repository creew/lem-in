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

static t_result	get_opposite_roomlink(
	t_linkarr *larr, t_roomdata *room, int n, t_linkdata *link)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if (room == ldata->left ||
				room == ldata->right)
			{
				if (!n--)
				{
					link->right = room == ldata->left ?
						ldata->right : ldata->left;
					return (RET_OK);
				}
			}
		}
	}
	return (ERR_WRONG_LINK);
}

t_adjlist		*add_adjdata(t_adjlist **adjlist, t_roomdata *room)
{
	t_adjlist	*lst;
	t_adjdata	*data;

	lst = ft_lstaddblank(adjlist, sizeof(t_adjdata));
	if (lst)
	{
		data = (t_adjdata *)lst->content;
		data->room = room;
	}
	return (lst);
}

t_result		add_neig_to_adjlist(t_adjdata *adata, t_adjdata *neig)
{
	t_neiglist	*lst;
	t_neigdata	*ndata;

	lst = ft_lstaddblank(&adata->neigs, sizeof(t_neigdata));
	if (!lst)
		return (ERR_ENOMEM);
	ndata = (t_neigdata *)lst->content;
	ndata->weight = 1;
	ndata->node	  = neig;
	return (RET_OK);
}

t_adjdata		*find_adjdata_by_room(t_adjlist *adjlist, t_roomdata *room)
{
	t_adjdata	*adata;

	adata = NULL;
	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		if (adata->room == room)
			return (adata);
		adjlist = adjlist->next;
	}
	return (adata);
}
t_result		graph_create(t_lemin *lem)
{
	size_t		size;
	t_linkdata	link;
	t_adjdata	*adata;
	t_adjdata	*neig;
	t_adjlist	*adjlist;

	size = ft_array_size(&lem->rooms);
	while (size--)
		if (ft_array_get(&lem->rooms, size, (void **)&link.left) == 0)
			add_adjdata(&lem->adjm, link.left);
	adjlist = lem->adjm;
	while (adjlist)
	{
		adata = (t_adjdata *)adjlist->content;
		size = 0;
		link.left = adata->room;
		while ((get_opposite_roomlink(
			&lem->links, adata->room, size++, &link)) == RET_OK)
		{
			neig = find_adjdata_by_room(lem->adjm, link.right);
			if (neig)
				add_neig_to_adjlist(adata, neig);
		}
		adjlist = adjlist->next;
	}
	dijkstra_algo(lem->adjm);
	return (RET_OK);
}
