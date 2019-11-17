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

t_result		graph_create(t_lemin *lem)
{
	t_roomdata	*rdata;
	int			count;
	size_t		size;
	size_t		index;
	size_t		index2;

	index = 0;
	index2 = 0;
	size = ft_array_size(&lem->rooms);
	lem->matrix = ft_calloc(size * size, sizeof(char));
	if (!lem->matrix)
		return (ERR_ENOMEM);
	while (index < size)
	{
		count = 0;
		if (ft_array_get(&lem->rooms, size, (void **)&rdata) == 0)
		{
			while ((get_opposite_roomlink(
				&lem->links, rdata, count++, &index2)) != NULL)
			{
				lem->matrix[index * size + index2] = 1;
				lem->matrix[index2 + size * index] = 1;
			}
		}
		index++;
	}
	dijkstra_algo(lem->matrix, &lem->rooms);
	return (RET_OK);
}
