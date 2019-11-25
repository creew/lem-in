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

t_result		add_neig_to_adjlist(t_adjdata *adata, t_adjdata *neig,
	int weight)
{
	t_neiglist	*lst;
	t_neigdata	*ndata;

	lst = ft_lstaddblank(&adata->neigs, sizeof(t_neigdata));
	if (!lst)
		return (ERR_ENOMEM);
	ndata = (t_neigdata *)lst->content;
	ndata->weight = weight;
	ndata->node = neig;
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

static void		del_one_elem(void *content, size_t content_size)
{
	(void)content_size;
	ft_memdel(&content);
}

t_result		remove_neig_from_adjlist(t_adjdata *from, t_adjdata *to,
	int *weigth)
{
	t_neiglist	**nlist;
	t_neiglist	*cur;
	t_neigdata	*ndata;
	int			count;

	count = 0;
	nlist = &from->neigs;
	while (*nlist)
	{
		cur = *nlist;
		ndata = (t_neigdata *)cur->content;
		if (ndata->node == to)
		{
			*nlist = cur->next;
			if (weigth)
				*weigth = ndata->weight;
			ft_lstdelone(&cur, del_one_elem);
			count++;
		}
		else
			nlist = &(cur->next);
	}
	return (count == 1 ? RET_OK : ERR_NO_LINK_TO_DEL);
}
