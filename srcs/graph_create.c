/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:40:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/06 09:40:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result		create_matrix(t_matrix *matrix, size_t size)
{
	matrix->m = ft_calloc(size * size, sizeof(char));
	if (!matrix->m)
		return (ERR_ENOMEM);
	matrix->weights = ft_calloc(size, sizeof(int));
	if (!matrix->weights)
		return (ERR_ENOMEM);
	matrix->size = size;
	return (RET_OK);
}

static t_result	get_opposite_roomlink(
	t_linkarr *larr, size_t room_index, int n, t_linkdata *link)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if (room_index == ldata->left->index ||
				room_index == ldata->right->index)
			{
				if (!n--)
				{
					link->right = room_index == ldata->left->index ?
						ldata->right : ldata->left;
					return (RET_OK);
				}
			}
		}
	}
	return (ERR_WRONG_LINK);
}

t_result		graph_create(t_lemin *lem)
{
	int			count;
	size_t		rooms_count;
	size_t		index;
	t_linkdata	link;
	t_result	res;

	index = -1;
	rooms_count = ft_array_size(&lem->rooms);
	if ((res = create_matrix(&lem->matrix, rooms_count) != RET_OK))
		return (res);
	while (++index < rooms_count)
	{
		if (ft_array_get(&lem->rooms, index, (void **)&link.left) == 0)
		{
			count = 0;
			while ((get_opposite_roomlink(
				&lem->links, index, count++, &link)) == RET_OK)
			{
				matrix_add_neighbor(&lem->matrix, &link);
			}
		}
	}
	dijkstra_algo(&lem->matrix, &lem->rooms, &lem->se);
	return (RET_OK);
}
