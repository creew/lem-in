/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 09:40:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 09:40:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_roomdata	*find_min_weight(t_roomarr *arr)
{
	t_roomdata	*rdata;
	t_roomdata	*cur;
	size_t		size;

	rdata = NULL;
	size = arr->num_elems;
	while (size--)
	{
		if (ft_array_get(arr, size, (void **)&cur) == 0)
		{
			if (cur->visited == 0 && cur->weigth != FT_INTMAX)
			{
				if (rdata == NULL || cur->weigth < rdata->weigth)
					rdata = cur;
			}
		}
	}
	return (rdata);
}

static void			reset_one_elem(void *data)
{
	t_roomdata	*rdata;

	rdata = (t_roomdata *)data;
	rdata->visited = 0;
	rdata->meh_visit = 0;
	rdata->weigth = FT_INTMAX;
}

t_result			dijkstra_algo(const char *matrix, t_roomarr *rooms)
{
	t_roomdata		*rdata;
	size_t			rooms_count;
	size_t			count;
	t_roomdata		*neig;

	rooms_count = ft_array_size(rooms);
	count = 0;
	ft_array_foreach(rooms, reset_one_elem);
	rdata = find_room_by_cmd(rooms, LEM_CMD_END);
	rdata->weigth = 0;
	while ((rdata = find_min_weight(rooms)))
	{
		while (count < rooms_count)
		{
			if (matrix[rdata->index * rooms_count + count])
			{
				if (ft_array_get(rooms, count, (void **)&neig) == 0)
				{
					if (rdata->weigth + 1 < neig->weigth)
					{
						neig->weigth = rdata->weigth + 1;
						neig->prev = rdata;
					}
				}
			}
			count++;
		}
		rdata->visited = 1;
	}
	return (RET_OK);
}