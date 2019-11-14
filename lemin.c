/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:23:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/04 12:23:02 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <fcntl.h>
#include <stdlib.h>

void	print_all(t_lemin *lem)
{
	print_rooms(&lem->rooms);
	print_links(&lem->links);
	print_neighbors(&lem->rooms);
}

void	init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
}

static void	delneighlst(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

static void delroomlinkarr(void *data)
{
	ft_memdel(&data);
}

static void	dellsts(void *data)
{
	t_roomdata	*rdata;

	rdata = (t_roomdata *)data;
	ft_lstdel(&rdata->neigborlst, delneighlst);
}

void	delete_all(t_lemin *lem)
{
	ft_array_foreach(&lem->rooms, dellsts);
	ft_array_remove_all(&lem->rooms, delroomlinkarr);
	ft_array_remove_all(&lem->links, delroomlinkarr);
}

int		main(int ac, char *av[])
{
	t_lemin		lem;
	t_result	ret;
	int			fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		fd = 0;
	init_lem(&lem);
	ret = read_input(fd, &lem);
	if (ret == RET_OK)
		ret = check_all(&lem);
	if (ret != RET_OK)
	{
		ft_putstr("Error ");
		ft_putnbr(ret);
		ft_putendl("");
	}
	print_all(&lem);
	delete_all(&lem);
	return (EXIT_SUCCESS);
}
