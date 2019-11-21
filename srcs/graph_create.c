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

static t_result	add_all_rooms_links(t_matrix *matrix)
{
	size_t		size;
	size_t 		line;

	size = matrix->size;
	while (size--)
	{
		line = matrix->size;
		while (line--)
			matrix->m[matrix->size * size + line].in = 1;
	}
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
	if ((res = matrix_create(&lem->matrix, rooms_count) != RET_OK))
		return (res);
	add_all_rooms_links(&lem->matrix);
	while (++index < rooms_count)
	{
		if (ft_array_get(&lem->rooms, index, (void **)&link.left) == 0)
		{
			count = 0;
			while ((get_opposite_roomlink(
				&lem->links, index, count++, &link)) == RET_OK)
				matrix_add_neighbor(&lem->matrix, &link);
		}
	}
	dijkstra_algo(&lem->matrix, &lem->rooms, &lem->se);
	return (RET_OK);
}
