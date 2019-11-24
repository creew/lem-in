/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:38:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/24 10:38:45 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	update_bf()
{


}

void		bellman_ford(t_adjlist *adjlist)
{
	size_t		size;
	t_adjlist	*adj;
	t_adjdata	*adjdata;
	t_neiglist	*neiglist;
	t_neigdata	*ndata;
	int			visited;

	reset_adjlist_values(adjlist);
	adjdata = find_node_by_cmd(adjlist, LEM_CMD_START);
	adjdata->weight = 0;
	visited = 1;
	size = ft_lstsize(adjlist);
	while (size > 1 && visited)
	{
		visited = 0;
		adj = adjlist;
		while (adj)
		{
			adjdata = (t_adjdata *)adj->content;
			neiglist = adjdata->neigs;
			while (neiglist)
			{
				ndata = (t_neigdata *)neiglist->content;
				if (adjdata->weight != WEIGHT_MAX && adjdata->weight + ndata->weight < ndata->node->weight)
				{
					ndata->node->weight = adjdata->weight + ndata->weight;
					ndata->node->prev = adjdata;
					visited = 1;
				}
				neiglist = neiglist->next;
			}
			adj = adj->next;
		}
		size--;
	}
}
