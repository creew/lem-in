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
	(void)content_size;
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

static void		make_duples(t_adjlist **root, t_adjdata *prev, t_adjdata *data, t_adjdata *next)
{
	t_adjdata	*out;
	t_neiglist	**nlist;
	t_neiglist	*cur;
	t_neigdata	*ndata;
	t_neiglist	*newlst;

	if (next)
	{
		newlst = ft_lstaddblank(root,sizeof(*out));
		if (newlst)
		{
			out = (t_adjdata *)newlst->content;
			out->weight = data->weight;
			out->room = data->room;
			out->dij_vis = data->dij_vis;
			nlist = &data->neigs;
			while (*nlist)
			{
				cur = *nlist;
				ndata = (t_neigdata *)cur->content;
				if (ndata->node != next)
				{
					*nlist = cur->next;
					cur->next = out->neigs;
					out->neigs = cur;
				}
				else
					nlist = &cur->next;
			}
			add_neig_to_adjlist(out, data, 0);
			remove_link(prev, data);
			add_neig_to_adjlist(prev, out, 1);
		}

	}
}

void			suurballe_algo(t_adjlist **root, t_patharr *paths)
{
	t_adjdata	*adata;
	t_adjdata	*prev;
	t_adjdata	*cur;
	t_adjdata	*next;


	prev = find_node_by_cmd(*root, LEM_CMD_END);
	if (!prev)
		return ;
	if ((cur = get_min_weight_neighbor(prev, 1)))
	{
		while (cur && cur->room->cmd != LEM_CMD_START)
		{
			next = get_min_weight_neighbor(cur, 0);
			remove_link(cur, prev);
			make_link_neg(prev, cur);
			make_duples(root, prev, cur, next);
			prev = cur;
			cur = next;
		}
	}
}
