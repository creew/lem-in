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

static t_path	*get_last_shortest_path(t_adjlist *alist)
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

static int		path_cmp(const void *d1, const void *d2)
{
	t_path	*p1;
	t_path	*p2;

	p1 = *(t_path **)d1;
	p2 = *(t_path **)d2;
	return ((int)ft_array_size(p1) - (int)ft_array_size(p2));
}

t_result		find_all_paths(t_lemin *lem)
{
	t_patharr	*sol;
	t_path		*path;
	t_path		*newp;
	int			prev_len;
	int			len;
	t_patharr	*newsol;
	t_patharr	*onesol;
	int			bf_updated;

	bf_updated = 1;
	sol = ft_array_new(10);
	path = get_last_shortest_path(lem->adjm);
	add_path_to_arr(sol, path);
	prev_len = calc_total_len(sol, lem->num_ants);
	onesol = sol;
	while (bf_updated)
	{
		suurballe_algo(&lem->adjm);
		bf_updated = bellman_ford(lem->adjm);
		if (bf_updated)
		{
			newp = get_last_shortest_path(lem->adjm);
			newsol = recalc_values(&lem->rooms, sol, newp);
			delete_path(&newp);
			ft_bubble_sort(newsol->data, newsol->num_elems,
				sizeof(*newsol->data), path_cmp);
			len = calc_total_len(newsol, lem->num_ants);
			if (len < prev_len)
			{
				remove_all_paths(&sol);
				onesol = newsol;
				prev_len = len;
			}
			else
				break ;
			sol = newsol;
		}
	}
	lem->paths = onesol;
	return (RET_OK);
}
