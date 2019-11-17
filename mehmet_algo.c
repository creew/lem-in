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

t_roomdata	*get_min_weight_neighbor(t_neigborlst *nlst)
{
	t_roomdata	*min;
	t_neigbor	*data;

	min = NULL;
	while (nlst)
	{
		data = (t_neigbor *)nlst->content;
		if (!data->room->meh_visit && data->room->weigth != FT_INTMAX)
		{
			if (min == NULL || data->room->weigth < min->weigth)
				min = data->room;
		}
		nlst = nlst->next;
	}
	return (min);
}

static void	remove_pathlst_callback(void *data, size_t size)
{
	(void)size;
	(void)data;
}

static void	remove_pathlst(t_path *path)
{
	ft_lstdel(&path, remove_pathlst_callback);
}

t_result	mehmet_algo(t_roomarr *rooms, t_patharr *paths)
{
	t_roomdata	*start;
	t_roomdata	*preroot;
	t_path		*path;

	remove_all_paths(paths);
	start = find_room_by_cmd(rooms, LEM_CMD_START);
	if (!start)
		return (ERR_NO_START_OR_END);
	start->meh_visit = 1;
	while ((preroot = get_min_weight_neighbor(start->neigborlst)))
	{
		path = NULL;
		add_room_to_path(&path, start);
		while (preroot)
		{
			add_room_to_path(&path, preroot);
			if (preroot->cmd == LEM_CMD_END)
				break;
			preroot->meh_visit = 1;
			preroot = get_min_weight_neighbor(preroot->neigborlst);
		}
		if (preroot != NULL && preroot->cmd == LEM_CMD_END)
			add_path_to_arr(paths, path);
		else
			remove_pathlst(path);
	}
	return (RET_OK);
}