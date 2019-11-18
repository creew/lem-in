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

static t_roomdata	*get_min_weight_neighbor(const char *matrix,
	t_roomarr *rooms, size_t index, int excl_one_len)
{
	t_roomdata	*data;
	t_roomdata	*min;
	size_t		rooms_count;
	size_t		count;

	min = NULL;
	count = -1;
	rooms_count = ft_array_size(rooms);
	matrix += rooms_count * index;
	while (++count < rooms_count)
	{
		if (matrix[count])
		{
			if (ft_array_get(rooms, count, (void **)&data) == 0)
			{
				if (!data->meh_visit && data->weigth != FT_INTMAX)
				{
					if (!excl_one_len || data->weigth > 1)
						if (min == NULL || data->weigth < min->weigth)
							min = data;
				}
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
	const char *matrix, t_roomarr *rooms, t_patharr *paths, t_roomdata	*start)
{
	size_t		count;
	size_t		count_rooms;
	t_roomdata	*room;
	t_path		*path;

	count_rooms = ft_array_size(rooms);
	count = -1;
	while (++count < count_rooms)
	{
		if (matrix[start->index * count_rooms + count] == 1)
		{
			if (ft_array_get(rooms, count, (void **)&room) == 0)
			{
				if (room->cmd == LEM_CMD_END)
				{
					if ((path = ft_array_new(2)) == NULL)
						return (ERR_ENOMEM);
					add_room_to_path(path, start);
					add_room_to_path(path, room);
					add_path_to_arr(paths, path);
					break ;
				}
			}
		}
	}
	return (RET_OK);
}

t_result			mehmet_algo(
	char *matrix, t_roomarr *rooms, t_patharr *paths)
{
	t_roomdata	*start;
	t_roomdata	*preroot;
	t_path		*path;

	remove_all_paths(paths);
	start = find_room_by_cmd(rooms, LEM_CMD_START);
	if (!start)
		return (ERR_NO_START_OR_END);
	start->meh_visit = 1;
	add_zero_len_path(matrix, rooms, paths, start);
	while ((preroot = get_min_weight_neighbor(matrix, rooms, start->index, 1)))
	{
		path = ft_array_new(0);
		if (!path)
			return (ERR_ENOMEM);
		add_room_to_path(path, start);
		while (preroot)
		{
			add_room_to_path(path, preroot);
			if (preroot->cmd == LEM_CMD_END)
				break;
			preroot->meh_visit = 1;
			preroot = get_min_weight_neighbor(matrix, rooms, preroot->index, 0);
		}
		if (preroot != NULL && preroot->cmd == LEM_CMD_END)
			add_path_to_arr(paths, path);
		else
			ft_array_delete_all(&path, remove_pathlst_callback);
	}
	return (RET_OK);
}