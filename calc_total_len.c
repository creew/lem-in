/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_total_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:43:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/15 09:43:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			mark_elem_unvisited(void *data)
{
	t_pathdata	*pdata;

	pdata = (t_pathdata *)data;
	pdata->visited = 0;
}

static void			mark_all_unvisited(t_patharr *paths)
{
	ft_array_foreach(paths, mark_elem_unvisited);
}

static t_pathdata	*get_min_path(t_patharr *paths)
{
	t_pathdata	*pd;
	t_pathdata	*pmin;
	size_t		size;

	pmin = NULL;
	size = ft_array_size(paths);
	while (size--)
	{
		if (ft_array_get(paths, size, (void **)&pd))
		{
			if (pd->visited == 0)
			{
				if (pmin == NULL || pd->size < pmin->size)
					pmin = pd;
			}
		}
	}
	return (pmin);
}

int					calc_total_len(t_patharr *paths, int count)
{
	int			sum_size;
	t_pathdata	*pdata;
	int			threads;
	int			total_len;

	sum_size = 0;
	threads = 0;
	total_len = FT_INTMAX;
	mark_all_unvisited(paths);
	while ((pdata = get_min_path(paths)) != NULL)
	{
		pdata->visited = 1;
		sum_size += pdata->size;
		if (((count + sum_size + threads) / (threads + 1) - 1) >= total_len)
			break ;
		total_len = (count + sum_size + threads) / (threads + 1) - 1;
		threads++;
	}
	if (threads == 0)
		return (-1);
	return (total_len);
}
