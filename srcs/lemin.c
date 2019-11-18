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

void		print_all(t_lemin *lem)
{
	print_rooms(&lem->rooms);
	print_links(&lem->links);
	print_neighbors(lem->matrix, &lem->rooms);
	print_paths(&lem->paths);
}

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->paths, 128);
}

int			main(int ac, char *av[])
{
	t_lemin	 lem;
	t_result ret;
	int		 fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		fd = 0;
	init_lem(&lem);
	ret = read_input(fd, &lem);
	if (ret == RET_OK)
		ret = check_all(&lem);
	if (ret == RET_OK)
		ret = find_all_paths(&lem);
	if (ret == RET_OK)
		start_ants(&lem);
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
