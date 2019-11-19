/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mehmet_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:31:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/16 16:31:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_roomdata	*get_min_weight_neighbor(t_matrix *matrix,
	t_roomarr *rooms, size_t index, int excl_one_len)
{
	t_roomdata	*data;
	t_roomdata	*min;
	size_t		rooms_count;
	size_t		count;

	min = NULL;
	count = -1;
	rooms_count = ft_array_size(rooms);
	while (++count < rooms_count)
	{
		if (matrix_get_link(matrix, index, count))
		{
			if (ft_array_get(rooms, count, (void **)&data) == 0)
			{
				if (!(matrix_get_flag(matrix, data->index) & MEHMET_VIS) &&
					matrix->weights[data->index] != FT_INTMAX)
					if (!excl_one_len || matrix->weights[data->index] > 0)
						if (min == NULL || matrix->weights[data->index] <
							matrix->weights[min->index])
							min = data;
			}
		}
	}
	return (min);
}

static void			remove_pathlst_callback(void *data)
{
	(void)data;
}

static t_result		add_zero_len_path(
	t_matrix *matrix, t_patharr *paths, t_borders *se)
{
	t_path		*path;

	if (matrix_get_link(matrix, se->start->index, se->end->index))
	{
		if ((path = ft_array_new(2)) == NULL)
			return (ERR_ENOMEM);
		add_room_to_path(path, se->start);
		add_room_to_path(path, se->end);
		add_path_to_arr(paths, path);
	}
	return (RET_OK);
}

t_result			mehmet_algo(
	t_matrix *matrix, t_roomarr *rooms, t_patharr *paths, t_borders *se)
{
	t_roomdata	*neig;
	t_path		*path;

	remove_all_paths(paths);
	matrix_set_flag(matrix, se->start->index, MEHMET_VIS);
	add_zero_len_path(matrix, paths, se);
	while ((neig = get_min_weight_neighbor(matrix, rooms, se->start->index, 1)))
	{
		if (!(path = ft_array_new(0)))
			return (ERR_ENOMEM);
		add_room_to_path(path, se->start);
		while (neig)
		{
			add_room_to_path(path, neig);
			if (neig->cmd == LEM_CMD_END)
				break ;
			matrix_set_flag(matrix, neig->index, MEHMET_VIS);
			neig = get_min_weight_neighbor(matrix, rooms, neig->index, 0);
		}
		if (neig != NULL && neig->cmd == LEM_CMD_END)
			add_path_to_arr(paths, path);
		else
			ft_array_delete_all(&path, remove_pathlst_callback);
	}
	return (RET_OK);
}
