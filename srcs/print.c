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
#include "ft_printf.h"

void	print_rooms(t_roomarr *rooms)
{
	t_roomdata	*data;
	size_t		count;

	count = -1;
	while (++count < ft_array_size(rooms))
	{
		if (ft_array_get(rooms, count, (void **)&data) == 0)
			ft_printf("name: \"%s\", x: %d, y: %d\n",
				data->name, data->x, data->y);
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
			ft_printf("link 1: \"%s\", link2: \"%s\"\n", linkdata->left->name,
				linkdata->right->name);
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
			ft_printf("name: \"%s\", neighbors: ", data->name);
			while (++neighb_index < rooms_count)
			{
				if (matrix[count * rooms_count + neighb_index])
				{
					if (ft_array_get(rooms, neighb_index, (void **)&neig) == 0)
						ft_printf("%s, ", neig->name);
				}
			}
			ft_printf("len: %d\n", data->weigth);
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
					ft_printf("\"%s\"", room->name);
				}
			}
			ft_putendl("");
		}
	}
}
