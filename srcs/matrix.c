/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:26:01 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/19 11:26:01 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result		matrix_create(t_matrix *matrix, size_t size)
{
	matrix->m = ft_calloc(size * size, sizeof(*matrix->m));
	if (!matrix->m)
		return (ERR_ENOMEM);
	matrix->weights = ft_calloc(size, sizeof(*matrix->weights));
	if (!matrix->weights)
		return (ERR_ENOMEM);
	matrix->size = size;
	return (RET_OK);
}

void			matrix_cpy(t_matrix *dst, const t_matrix *src)
{
	size_t	size;
	size_t	count;

	size = src->size;
	if (size == dst->size)
	{
		ft_memcpy(dst->m, src->m, size * size * sizeof(*src->m));
		count = -1;
		while (++count < size)
			dst->weights[count] = src->weights[count];
	}
}

t_result		matrix_dup(t_matrix *dst, const t_matrix *src)
{
	t_result	res;
	size_t		size;

	size = src->size;
	if ((res = matrix_create(dst, size)) != RET_OK)
		return (res);
	matrix_cpy(dst, src);
	return (RET_OK);
}
