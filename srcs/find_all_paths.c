/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 07:08:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 07:08:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ft_printf.h"

static t_result		remove_path(t_path *path, size_t sindex, size_t eindex,
	t_linkdata *link)
{
	t_roomdata		*slst;
	t_roomdata		*elst;

	if (ft_array_get(path, sindex, (void **)&slst) != 0 ||
		ft_array_get(path, eindex, (void **)&elst) != 0)
		return (ERR_INCORRECT_PATH_REMOVE);
	link->left = slst;
	link->right = elst;
	return (RET_OK);
}

static t_result		recalc_paths(t_lemin *lem, int *prev_len,
						t_matrix *matrix, t_patharr *paths)
{
	t_result	res;
	size_t		count;
	int			next_len;

	res = RET_OK;
	dijkstra_algo(matrix, &lem->rooms, &lem->se);
	mehmet_algo(matrix, &lem->rooms, paths, &lem->se);
	next_len = calc_total_len(paths, lem->num_ants);
	if (next_len < *prev_len)
	{
		res = RET_RECALC;
		*prev_len = next_len;
		matrix_cpy(&lem->matrix, matrix);
		remove_all_paths(&lem->paths);
		count = -1;
		while (++count < paths->num_elems)
			ft_array_add(&lem->paths, paths->data[count]);
		ft_memdel((void **)&paths->data);
	}
	else
		remove_all_paths(paths);
	return (res);
}

static t_result		try_recalc(t_lemin *lem, int *prev_len,
	t_pathdata *pdata, size_t pindex)
{
	t_matrix	tmp;
	t_patharr	paths;
	t_result	res;
	t_linkdata	link;

	if ((res = remove_path(pdata->path, pindex, pindex + 1, &link) == RET_OK))
	{
		if (matrix_dup(&tmp, &lem->matrix) != RET_OK)
			return (ERR_ENOMEM);
		ft_array_init(&paths, 64);
		matrix_rem_neighbor(&tmp, &link);
		res = recalc_paths(lem, prev_len, &tmp, &paths);
		ft_memdel((void **)&tmp.m);
		ft_memdel((void **)&tmp.weights);
	}
	return (res);
}

static int			min_neig_start_end(t_matrix *matrix, t_borders *se)
{
	size_t	size;
	int		count_e;
	int		count_s;

	count_e = 0;
	count_s = 0;
	size = matrix->size;
	while (size--)
	{
		if (matrix_get_link(matrix, se->start->index, size))
			count_s++;
		if (matrix_get_link(matrix, se->end->index, size))
			count_e++;
	}
	return (ft_min(count_s, count_e));
}

t_result			find_all_paths(t_lemin *lem)
{
	int			len;
	size_t		index;
	t_pathdata	*pdata;
	size_t		pindex;


	while (42)
	{
		suurballe_algo(&lem->matrix, &lem->rooms, &lem->paths, &lem->se);




	}


	mehmet_algo(&lem->matrix, &lem->rooms, &lem->paths, &lem->se);
	len = calc_total_len(&lem->paths, lem->num_ants);
	if (min_neig_start_end(&lem->matrix, &lem->se) == 1)
		return (RET_OK);
	index = -1;
	while (++index < ft_array_size(&lem->paths))
	{
		if (ft_array_get(&lem->paths, index, (void **)&pdata) == 0)
		{
			pindex = -1;
			while (++pindex < pdata->size - 1)
				if (try_recalc(lem, &len, pdata, pindex) == RET_RECALC)
				{
					index = -1;
					break ;
				}
		}
	}
	return (RET_OK);
}
