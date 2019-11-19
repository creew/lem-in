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
	if ((res = create_matrix(dst, size)) != RET_OK)
		return (res);
	matrix_cpy(dst, src);
	return (RET_OK);
}
