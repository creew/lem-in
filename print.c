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

void	print_rooms(t_roomlst *rooms)
{
	t_roomlst	*cur;
	t_roomdata	*data;
	size_t		size;

	size = ft_lstsize(rooms);
	while (size--)
	{
		cur = ft_lstget(rooms, size);
		if (cur)
		{
			data = (t_roomdata *)cur->content;
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

void	print_links(t_linklst *links)
{
	t_linkdata	*linkdata;
	size_t		size;
	t_linklst	*cur;

	size = ft_lstsize(links);
	while (size--)
	{
		cur = ft_lstget(links, size);
		if (cur)
		{
			linkdata = (t_linkdata *)cur->content;
			ft_putstr("link 1: \"");
			ft_putstr(linkdata->l1);
			ft_putstr("\", link 2: \"");
			ft_putstr(linkdata->l2);
			ft_putendl("\"");
		}
	}
}

void	print_neighbors(t_roomlst *rooms)
{
	t_roomlst	*cur;
	t_roomdata	*data;
	size_t		size;
	size_t 		neighbors_size;
	t_neigborlst *nlst;
	t_neigbor		*neigbor;

	size = ft_lstsize(rooms);
	while (size--)
	{
		cur = ft_lstget(rooms, size);
		if (cur)
		{
			data = (t_roomdata *)cur->content;
			ft_putstr("name: \"");
			ft_putstr(data->name);
			ft_putstr("\", neighbors: ");
			neighbors_size = ft_lstsize(data->lst);
			while (neighbors_size--)
			{
				nlst = ft_lstget(data->lst, neighbors_size);
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
	}
}
