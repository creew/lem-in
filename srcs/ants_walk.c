/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:28:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 16:28:05 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_move(t_roomdata *cur, int *is_not_first)
{
	if (*is_not_first)
		ft_putstr(" ");
	*is_not_first = 1;
	ft_putstr("L");
	ft_putnbr(cur->ant_index);
	ft_putstr("-");
	ft_putstr(cur->name);
}

int			push_one_path(t_path *path, t_lemin *lem, int *is_not_first)
{
	size_t		size;
	t_roomdata	*cur;
	t_roomdata	*prev;

	size = ft_array_size(path);
	while (size--)
	{
		if (ft_array_get(path, size, (void **)&cur) == 0 &&
			ft_array_get(path, size - 1, (void **)&prev) == 0)
		{
			if (prev->ant_count)
			{
				cur->ant_index = prev->ant_index;
				cur->ant_count++;
				prev->ant_count--;
				if (size == 1)
					cur->ant_index = lem->num_ants - prev->ant_count;
				print_move(cur, is_not_first);
			}
		}
	}
	return (0);
}

int			push_ants(t_patharr *arr, t_lemin *lem, int *is_not_first)
{
	size_t		path_count;
	size_t		count;
	t_pathdata	*pathdata;

	count = 0;
	path_count = ft_array_size(arr);
	while (count < path_count)
	{
		if (ft_array_get(arr, count, (void **)&pathdata) == 0)
		{
			push_one_path(pathdata->path, lem, is_not_first);
		}
		count++;
	}
	return (0);
}

void	start_ants(t_lemin *lem)
{
	t_roomdata	*rdata;
	t_roomdata	*edata;
	int 		is_not_first;

	rdata = find_room_by_cmd(&lem->rooms, LEM_CMD_START);
	edata = find_room_by_cmd(&lem->rooms, LEM_CMD_END);
	if (rdata && edata)
	{
		rdata->ant_count = lem->num_ants;
		while (edata->ant_count != lem->num_ants)
		{
			is_not_first = 0;
			push_ants(&lem->paths, lem, &is_not_first);
			ft_putendl("");
		}
	}
}