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

void		matrix_set_flag(t_matrix *matrix, size_t room, size_t flag)
{
	if (room < matrix->size)
		matrix->m[room] |= flag;
}

t_uchar		matrix_get_flag(t_matrix *matrix, size_t room)
{
	if (room < matrix->size)
		return (matrix->m[room]);
	return (0);
}

t_uchar		matrix_get_link(t_matrix *matrix, size_t room1, size_t room2)
{
	if (room1 < matrix->size && room2 < matrix->size)
		return (matrix->m[room1 * matrix->size + room2] & M_LINK);
	return (0);
}

void		matrix_add_neighbor(t_matrix *matrix, t_linkdata *link)
{
	size_t	lindex;
	size_t	rindex;

	lindex = link->left->index;
	rindex = link->right->index;
	if (lindex < matrix->size && rindex < matrix->size)
	{
		matrix->m[matrix->size * lindex + rindex] |= M_LINK;
		matrix->m[matrix->size * rindex + lindex] |= M_LINK;
	}
}

void		matrix_rem_neighbor(t_matrix *matrix, t_linkdata *link)
{
	size_t	lindex;
	size_t	rindex;

	lindex = link->left->index;
	rindex = link->right->index;
	if (lindex < matrix->size && rindex < matrix->size)
	{
		matrix->m[matrix->size * lindex + rindex] &= ~M_LINK;
		matrix->m[matrix->size * rindex + lindex] &= ~M_LINK;
	}
}
