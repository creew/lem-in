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

void			add_neigbor_room(t_lemin *lem, t_linkdata *link)
{
	char	*matrix;
	size_t	size;

	matrix = lem->matrix;
	size = ft_array_size(&lem->rooms);
	matrix[size * link->left + link->right] = 1;
	matrix[size * link->right + link->left] = 1;
}

void			rem_neigbor_room(t_lemin *lem, t_linkdata *link)
{
	char	*matrix;
	size_t	size;

	matrix = lem->matrix;
	size = ft_array_size(&lem->rooms);
	matrix[size * link->left + link->right] = 0;
	matrix[size * link->right + link->left] = 0;
}

t_result		graph_create(t_lemin *lem)
{
	int			count;
	size_t		rooms_count;
	size_t		index;
	size_t		index2;

	index = 0;
	index2 = 0;
	rooms_count = ft_array_size(&lem->rooms);
	lem->matrix = ft_calloc(rooms_count * rooms_count, sizeof(char));
	if (!lem->matrix)
		return (ERR_ENOMEM);
	while (index < rooms_count)
	{
		count = 0;
		while ((get_opposite_roomlink(
			&lem->links, index, count++, &index2)) == RET_OK)
		{
			lem->matrix[index * rooms_count + index2] = 1;
			lem->matrix[index2 * rooms_count + index] = 1;
		}
		index++;
	}
	dijkstra_algo(lem->matrix, &lem->rooms);
	return (RET_OK);
}
