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

void	print_rooms(t_list *rooms)
{
	t_list		*cur;
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

void	print_links(t_list *links)
{
	t_linkdata	*linkdata;
	size_t		size;
	t_list		*cur;

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
