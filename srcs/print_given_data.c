/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_given_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:57:03 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/18 09:57:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_room_cmd(int cmd)
{
	if (cmd == LEM_CMD_START)
		ft_putendl("##start");
	else if (cmd == LEM_CMD_END)
		ft_putendl("##end");
}

static void	print_one_room(t_roomarr *arr, size_t index)
{
	t_roomdata	*rdata;

	if (ft_array_get(arr, index, (void **)&rdata) == 0)
	{
		print_room_cmd(rdata->cmd);
		ft_putstr(rdata->name);
		ft_putchar(' ');
		ft_putnbr(rdata->x);
		ft_putchar(' ');
		ft_putnbr(rdata->y);
		ft_putchar('\n');
	}
}

static void	print_one_link(t_linkarr *larr, size_t index)
{
	t_linkdata	*ldata;

	if (ft_array_get(larr, index, (void **)&ldata) == 0)
	{
		ft_putstr(ldata->left->name);
		ft_putchar('-');
		ft_putstr(ldata->right->name);
		ft_putchar('\n');
	}
}

void		print_given_data(t_lemin *lem)
{
	size_t	index;
	size_t	size;

	ft_putnbr(lem->num_ants);
	ft_putchar('\n');
	index = -1;
	size = ft_array_size(&lem->rooms);
	while (++index < size)
		print_one_room(&lem->rooms, index);
	index = -1;
	size = ft_array_size(&lem->links);
	while (++index < size)
		print_one_link(&lem->links, index);
	ft_putchar('\n');
	print_solution(lem);
}
