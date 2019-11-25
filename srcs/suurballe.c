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

static t_adjdata	*get_min_weight_neighbor(t_adjdata *adata)
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
			if (ndata->node->weight != WEIGHT_MAX)
			{
				if (min == NULL || ndata->node->weight < min->weight)
					min = ndata->node;
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

t_result		remove_link(t_adjdata *from, t_adjdata *to, int *weigth)
{
	t_neiglist	**nlist;
	t_neiglist	*cur;
	t_neigdata	*ndata;
	int         count;

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
	int 		weigth;

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
			if (remove_link(prev, data, &weigth) == RET_OK)
				add_neig_to_adjlist(prev, out, weigth);
		}
	}
}

t_path			*suurballe_algo(t_adjlist **root)
{
	t_adjdata	*prev;
	t_adjdata	*cur;
	t_adjdata	*next;

	prev = find_node_by_cmd(*root, LEM_CMD_END);
	if (!prev)
		return (NULL);
	if ((cur = prev->prev))
	{
		while (cur)
		{
			next = cur->prev;
			remove_link(cur, prev, NULL);
			make_link_neg(prev, cur);
			if (cur->room->cmd == LEM_CMD_START)
				break;
			make_duples(root, prev, cur, next);
			prev = cur;
			cur = next;
		}
	}
}
