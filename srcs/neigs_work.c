/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neigs_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:25:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/23 21:25:18 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

t_result		add_neig_to_adjlist(t_adjdata *adata, t_adjdata *neig, int weight)
{
	t_neiglist	*lst;
	t_neigdata	*ndata;

	lst = ft_lstaddblank(&adata->neigs, sizeof(t_neigdata));
	if (!lst)
		return (ERR_ENOMEM);
	ndata = (t_neigdata *)lst->content;
	ndata->weight = weight;
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