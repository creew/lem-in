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

	count = 0;
	while (count < ft_array_size(rooms))
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
		count++;
	}
}

void	print_links(t_linkarr *links)
{
	t_linkdata	*linkdata;
	size_t		count;

	count = 0;
	while (count < ft_array_size(links))
	{
		if (ft_array_get(links, count, (void **)&linkdata) == 0)
		{
			ft_putstr("link 1: \"");
			ft_putstr(linkdata->l1);
			ft_putstr("\", link 2: \"");
			ft_putstr(linkdata->l2);
			ft_putendl("\"");
		}
		count++;
	}
}

void	print_neighbors(t_roomarr *rooms)
{
	t_roomdata		*data;
	size_t			count;
	size_t			neighbors_size;
	t_neigborlst	*nlst;
	t_neigbor		*neigbor;

	count = 0;
	while (count < ft_array_size(rooms))
	{
		if (ft_array_get(rooms, count, (void **)&data) == 0)
		{
			ft_putstr("name: \"");
			ft_putstr(data->name);
			ft_putstr("\", neighbors: ");
			neighbors_size = ft_lstsize(data->neigborlst);
			while (neighbors_size--)
			{
				nlst = ft_lstget(data->neigborlst, neighbors_size);
				if (nlst)
				{
					neigbor = (t_neigbor *)nlst->content;
					ft_putstr(neigbor->room->name);
					ft_putstr(", ");
				}
			}
			ft_putstr("len: ");
			ft_putnbr(data->weigth);
			ft_putendl("");
		}
		count++;
	}
}

void	print_paths(t_patharr *parr)
{
	size_t		count;
	t_pathdata	*pdata;
	t_path		*path;
	t_roomdata	*room;

	count = 0;
	while (count < ft_array_size(parr))
	{
		if (ft_array_get(parr, count, (void **)&pdata) == 0)
		{
			path = pdata->path;
			while (path)
			{
				room = (t_roomdata *)path->content;
				ft_putstr("\"");
				ft_putstr(room->name);
				ft_putstr("\", ");
				path = path->next;
			}
			ft_putendl("");
		}
		count++;
	}




}
