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

int		main(int ac, char *av[])
{
	t_lemin		lem;
	t_result	ret;
	int 		fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		fd = 0;
	ft_bzero(&lem, sizeof(lem));
	ret = read_input(fd, &lem);
	if (ret == RET_OK)
		ret = check_all(&lem);
	if (ret != RET_OK)
	{
		ft_putstr("Error ");
		ft_putnbr(ret);
		ft_putendl("");
	}
	print_rooms(lem.rooms);
	print_links(lem.links);
	return (0);
}
