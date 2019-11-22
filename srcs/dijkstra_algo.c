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

#define BIT_16_MAX	(32767)

static t_roomdata	*find_min_weight(t_matrix *matrix, t_roomarr *arr)
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
			if (!(matrix->m[cur->index].dij_vis) &&
				matrix->weights[cur->index].wout != BIT_16_MAX)
			{
				if (rdata == NULL ||
					matrix->weights[cur->index].wout < matrix->weights[rdata->index].wout)
					rdata = cur;
			}
		}
	}
	return (rdata);
}

static void			reset_matrix_algos(t_matrix *matrix)
{
	size_t	size;

	size = matrix->size;
	while (size--)
	{
		matrix->m[size].dij_vis = 0;
		matrix->weights[size].wout = BIT_16_MAX;
	}
}

t_result			dijkstra_algo(
	t_matrix *matrix, t_roomarr *rooms, t_borders *se)
{
	t_roomdata		*rdata;
	size_t			rooms_count;
	size_t			count;
	t_roomdata		*neig;

	rooms_count = ft_array_size(rooms);
	reset_matrix_algos(matrix);
	matrix->weights[se->end->index].wout = 0;
	while ((rdata = find_min_weight(matrix, rooms)))
	{
		count = -1;
		while (++count < rooms_count)
		{
			if (matrix_get_link(matrix, rdata->index, count))
				if (ft_array_get(rooms, count, (void **)&neig) == 0)
					if (matrix->weights[rdata->index].wout + 1 <
						matrix->weights[neig->index].wout)
						matrix->weights[neig->index].wout =
							matrix->weights[rdata->index].wout = 1;
		}
		matrix->m[rdata->index].dij_vis = 1;
	}
	return (RET_OK);
}
