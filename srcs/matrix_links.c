/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 09:04:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/19 09:04:39 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_uchar		matrix_get_link(t_matrix *matrix, size_t room1, size_t room2)
{
	size_t	size;

	size = matrix->size;
	if (room1 < size && room2 < size)
	{
		if (matrix->m[size *room1 + room2].ex == 1)
			return (1);
	}
	return (0);
}

void		matrix_add_neighbor(t_matrix *matrix, t_linkdata *link)
{
	size_t	lindex;
	size_t	rindex;
	size_t 	size;

	size = matrix->size;
	lindex = link->left->index;
	rindex = link->right->index;
	if (lindex < matrix->size && rindex < matrix->size)
	{
		matrix->m[size * lindex + rindex].ex = 1;
		matrix->m[size * rindex + lindex].ex = 1;
	}
}

void		matrix_rem_neighbor(t_matrix *matrix, t_linkdata *link)
{
	size_t	lindex;
	size_t	rindex;
	size_t 	size;

	size = matrix->size;
	lindex = link->left->index;
	rindex = link->right->index;
	if (lindex < matrix->size && rindex < matrix->size)
	{
		matrix->m[size * lindex + rindex].ex = 0;
		matrix->m[size * rindex + lindex].ex = 0;
	}
}
