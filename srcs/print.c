/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:18:55 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 15:18:55 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_rooms(t_roomarr *rooms)
{
	t_roomdata	*data;
	size_t		count;

	count = -1;
	while (++count < ft_array_size(rooms))
	{
		if (ft_array_get(rooms, count, (void **)&data) == 0)
		{
			ft_putstr("name: \"");
			ft_putstr(data->name);
			ft_putstr("\", x: ");
			ft_putnbr(data->x);
			ft_putstr(", y: ");
			ft_putnbr(data->y);
			ft_putendl("");
		}
	}
}

void	print_links(t_linkarr *links)
{
	t_linkdata	*linkdata;
	size_t		count;

	count = -1;
	while (++count < ft_array_size(links))
	{
		if (ft_array_get(links, count, (void **)&linkdata) == 0)
		{
			ft_putstr("link 1: \"");
			ft_putstr(linkdata->left->name);
			ft_putstr("\", link 2: \"");
			ft_putstr(linkdata->right->name);
			ft_putendl("\"");
		}
	}
}

void	print_neighbors(const char *matrix, t_roomarr *rooms)
{
	t_roomdata		*data;
	t_roomdata		*neig;
	size_t			count;
	size_t			neighb_index;
	size_t			rooms_count;

	rooms_count = ft_array_size(rooms);
	count = -1;
	while (++count < rooms_count)
	{
		if (ft_array_get(rooms, count, (void **)&data) == 0)
		{
			neighb_index = -1;
			ft_putstr("name: \"");
			ft_putstr(data->name);
			ft_putstr("\", neighbors: ");
			while (++neighb_index < rooms_count)
			{
				if (matrix[count * rooms_count + neighb_index])
				{
					if (ft_array_get(rooms, neighb_index, (void **)&neig) == 0)
					{
						ft_putstr(neig->name);
						ft_putstr(", ");
					}
				}
			}
			ft_putstr("len: ");
			ft_putnbr(data->weigth);
			ft_putendl("");
		}
	}
}

void	print_paths(t_patharr *parr)
{
	size_t		count;
	t_pathdata	*pdata;
	t_roomdata	*room;
	size_t		pcount;

	count = -1;
	while (++count < ft_array_size(parr))
	{
		if (ft_array_get(parr, count, (void **)&pdata) == 0)
		{
			pcount = -1;
			while (++pcount < ft_array_size(pdata->path))
			{
				if (ft_array_get(pdata->path, pcount, (void **)&room) == 0)
				{
					if (pcount != 0)
						ft_putstr(", ");
					ft_putstr("\"");
					ft_putstr(room->name);
					ft_putstr("\"");
				}
			}
			ft_putendl("");
		}
	}
}
