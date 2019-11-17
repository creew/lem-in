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

t_result	remove_path(t_path **path, size_t sindex, size_t eindex, t_linkdata *link)
{
	size_t		size;
	t_path		*slst;
	t_path		*elst;

	size = ft_lstsize(*path);
	if (sindex >= eindex || eindex >= size)
		return (ERR_INCORRECT_PATH_REMOVE);
	if ((slst = ft_lstget(*path, sindex)) == NULL ||
		(elst = ft_lstget(*path, eindex)) == NULL)
		return (ERR_INCORRECT_PATH_REMOVE);
	link->left = ((t_roomdata *)slst->content)->index;
	link->right = ((t_roomdata *)elst->content)->index;
	return (RET_OK);
}

static int 	path_arr_cmp(const void *a, const void *b)
{
	t_pathdata	*pdata1;
	t_pathdata	*pdata2;

	pdata1 = *(t_pathdata **)a;
	pdata2 = *(t_pathdata **)b;
	return ((int)pdata1->size - (int)pdata2->size);
}

void		sort_path_arr(t_patharr *parr)
{
	ft_bubble_sort(parr->data, parr->num_elems,
		sizeof(*parr->data), path_arr_cmp);
}

t_pathdata	*find_pathdata_by_room(t_patharr *parr, t_roomdata *room)
{
	t_path		*path;
	t_pathdata	*pdata;
	size_t		count;
	t_roomdata	*data;

	count = 0;
	while (count < parr->num_elems)
	{
		if (ft_array_get(parr, count, (void **)&pdata) == 0)
		{
			if (ft_lstsize(pdata->path) > 1)
			{
				path = ft_lstget(pdata->path, 1);
				data = (t_roomdata *)path->content;
				if (data == room)
					return (pdata);
			}
		}
		count++;
	}
	return (NULL);
}

t_result		add_neigbor_room(t_lemin *lem, t_linkdata *link)
{
	char	*matrix;
	size_t	size;

	matrix = lem->matrix;
	size = ft_array_size(&lem->rooms);
	matrix[size * link->left + link->right] = 1;
	matrix[size * link->right + link->left] = 1;
}

t_result		rem_neigbor_room(t_lemin *lem, t_linkdata *link)
{
	char	*matrix;
	size_t	size;

	matrix = lem->matrix;
	size = ft_array_size(&lem->rooms);
	matrix[size * link->left + link->right] = 0;
	matrix[size * link->right + link->left] = 0;
}

t_result	find_all_paths(t_lemin *lem)
{
	int			len;
	int 		next_len;
	size_t		index;
	t_linkdata	link;
	t_pathdata	*pdata;
	size_t		pindex;
	size_t 		psize;
	t_roomdata	*afterstart;

	mehmet_algo(lem->matrix, &lem->rooms, &lem->paths);
	len = calc_total_len(&lem->paths, lem->num_ants);
	ft_putstr("Total len before:");
	ft_putnbr(len);
	ft_putendl("");
	index = 0;

	while (index < ft_array_size(&lem->paths))
	{
		sort_path_arr(&lem->paths);
		if (ft_array_get(&lem->paths, index, (void **)&pdata) == 0)
		{
			pindex = 0;
			psize = pdata->size - 1;
			while (pindex < psize)
			{
				afterstart = (t_roomdata *)ft_lstget(pdata->path, 1)->content;
				remove_path(&pdata->path, pindex, pindex + 1, &link);
				rem_neigbor_room(lem, &link);
				dijkstra_algo(lem->matrix, &lem->rooms);
				mehmet_algo(lem->matrix, &lem->rooms, &lem->paths);
				next_len = calc_total_len(&lem->paths, lem->num_ants);
				if (next_len >= len)
				{
					add_neigbor_room(lem, &link);
					dijkstra_algo(lem->matrix, &lem->rooms);
					mehmet_algo(lem->matrix, &lem->rooms, &lem->paths);
					sort_path_arr(&lem->paths);
					pdata = find_pathdata_by_room(&lem->paths, afterstart);
				}
				else
				{
					len = next_len;
					index = -1;
					break;
				}
				pindex++;
			}
		}
		index++;
	}
	ft_putstr("Total len after:");
	ft_putnbr(len);
	ft_putendl("");
	return (RET_OK);
}