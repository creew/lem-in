/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 07:08:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 07:08:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ft_printf.h"

t_path				*get_shortest_path(t_adjlist *alist)
{
	t_adjdata	*end;
	t_path		*path;

	path = NULL;
	end = find_node_by_cmd(alist, LEM_CMD_END);
	if (end)
	{
		if (end->prev)
		{
			path = ft_array_new(10);
			if (path)
			{
				while (end)
				{
					ft_array_insert(path, end->room, 0);
					end = end->prev;
				}
			}
		}
	}
	return (path);
}

static void			add_path_to_adjlist(t_adjlist *alist, t_path *path)
{
	size_t		count;
	t_roomdata	*room;
	t_roomdata	*prev;
	t_adjdata	*acur;
	t_adjdata	*aprev;

	prev = NULL;
	count = -1;
	while (++count < ft_array_size(path))
	{
		if (ft_array_get(path, count, (void **)&room) == 0)
		{
			if (prev != NULL)
			{
				acur = find_adjdata_by_room(alist, room);
				aprev = find_adjdata_by_room(alist, prev);
				if (acur && aprev)
				{
					if (remove_link(acur, aprev, NULL) != RET_OK)
						add_neig_to_adjlist(aprev, acur, 1);
				}
			}
			prev = room;
		}
	}
}

t_result	*get_all_paths(t_patharr *parr, t_adjlist *alist)
{
	t_adjdata	*start;
	t_list		*neighs;
	t_path		*path;
	t_neiglist	*nlist;
	t_neigdata	*nndata;

	start = find_node_by_cmd(alist, LEM_CMD_START);
	if (!start)
		return (NULL);
	if ((neighs = start->neigs))
	{
		while (neighs)
		{
			path = ft_array_new(10);
			add_room_to_path(path, start->room);
			nlist = neighs;
			while (nlist)
			{
				nndata = (t_neigdata *)nlist->content;
				add_room_to_path(path, nndata->node->room);
				nlist = nndata->node->neigs;
			}
			add_path_to_arr(parr, path);
			neighs = neighs->next;
		}
	}
	return (RET_OK);
}

t_patharr	*recalc_values(t_lemin *lem, t_patharr *paths, t_path *path)
{
	t_adjlist	*adjlist;
	t_pathdata	*pdata;
	size_t 		size;
	t_patharr	*sol;

	size = ft_array_size(paths);
	adjlist = NULL;
	create_adjlist(&adjlist, &lem->rooms);
	while (size--)
	{
		if (ft_array_get(paths, size, (void **)&pdata) == 0)
			add_path_to_adjlist(adjlist, pdata->path);
	}
	add_path_to_adjlist(adjlist, path);
	sol = ft_array_new(10);
	get_all_paths(sol, adjlist);
	delete_adjlist(&adjlist);
	return (sol);
}


t_result			find_all_paths(t_lemin *lem)
{
	t_patharr	*sol;
	t_path		*path;
	t_path		*newp;
	int 		prev_len;
	int			len;
	t_patharr	*newsol;
	t_patharr   *onesol;
	int 		count;
	int 		bf_updated;

	bf_updated = 1;
	sol = ft_array_new(10);
	path = get_shortest_path(lem->adjm);
	add_path_to_arr(sol, path);
	prev_len = calc_total_len(sol, lem->num_ants);
    onesol = sol;
    count = 0;
	ft_printf("start\n");
	print_paths(sol);
	while (bf_updated)
	{
		suurballe_algo(&lem->adjm);
		//print_neighbors(lem->adjm, "after suurballe");
		bf_updated = bellman_ford(lem->adjm);

		newp = get_shortest_path(lem->adjm);
		ft_printf("New short: %d\n", count++);
		print_path(newp);
		newsol = recalc_values(lem, sol, newp);
		ft_printf("Stage: %d\n", count++);
		print_paths(newsol);
		delete_path(&newp);
		len = calc_total_len(newsol, lem->num_ants);
		if (len < prev_len)
		{
		    onesol = newsol;
			prev_len = len;
		}
		else
		{
			remove_all_paths(&newsol);
			break;
		}
	}
	ft_printf("End: \n");
	print_paths(onesol);
	lem->paths = onesol;
	//print_neighbors(lem->adjm, "after bellman");
	return (RET_OK);
}
