/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:55:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/21 15:55:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_adjdata	*get_min_weight_neighbor(t_adjdata *adata, int excl_one_elem)
{
	t_neiglist	*nlist;
	t_adjdata	*min;
	t_neigdata	*ndata;

	min = NULL;
	if (adata)
	{
		nlist = adata->neigs;
		while (nlist)
		{
			ndata = (t_neigdata *)nlist->content;
			if (!excl_one_elem || ndata->node->weight != 1)
			{
				if (ndata->node->weight != WEIGHT_MAX)
				{
					if (min == NULL || ndata->node->weight < min->weight)
						min = ndata->node;
				}
			}

			nlist = nlist->next;
		}
	}
	return (min);
}

static void		del_one_elem(void *content, size_t content_size)
{
	ft_memdel(&content);
}

static void		remove_link(t_adjdata *from, t_adjdata *to)
{
	t_neiglist	**nlist;
	t_neiglist	*cur;
	t_neigdata	*ndata;

	nlist = &from->neigs;
	while (*nlist)
	{
		cur = *nlist;
		ndata = (t_neigdata *)cur->content;
		if (ndata->node == to)
		{
			*nlist = cur->next;
			ft_lstdelone(&cur, del_one_elem);
		}
		else
		{
			nlist = &(cur->next);
		}
	}
}

static void		make_link_neg(t_adjdata *from, t_adjdata *to)
{
	t_neiglist	*nlist;
	t_neigdata	*ndata;

	nlist = from->neigs;
	while (nlist)
	{
		ndata = (t_neigdata *)nlist->content;
		if (ndata->node == to)
			ndata->weight = -ndata->weight;
		nlist = nlist->next;
	}
}

static void		make_duples(t_adjdata *data)
{
	t_adjdata	*in;
	t_adjdata	*out;

	in = ft_memalloc(sizeof(*in));
	in->weight = data->weight;
	in->room = data->room;
	in->dij_vis = data->dij_vis;






}

void			suurballe_algo(t_adjlist *adjlist, t_patharr *paths)
{
	t_adjdata	*adata;
	t_adjdata	*prev;
	t_adjdata	*cur;

	prev = find_node_by_cmd(adjlist, LEM_CMD_END);
	if (!prev)
		return ;
	if ((cur = get_min_weight_neighbor(prev, 1)))
	{
		while (cur)
		{
			remove_link(cur, prev);
			make_link_neg(prev, cur);

			cur = get_min_weight_neighbor(prev, 0);
		}
	}
}
