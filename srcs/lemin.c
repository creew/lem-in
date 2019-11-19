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

void		print_all(t_lemin *lem)
{
	print_rooms(&lem->rooms);
	print_links(&lem->links);
	print_neighbors(&lem->matrix, &lem->rooms);
	print_paths(&lem->paths);
}

void		init_lem(t_lemin *lem)
{
	ft_bzero(lem, sizeof(*lem));
	ft_array_init(&lem->rooms, 128);
	ft_array_init(&lem->links, 128);
	ft_array_init(&lem->paths, 128);
}

void		print_error(t_lemin *lem, t_result err)
{
	if (!lem->is_debug)
		ft_putendl_fd("Error\n", 2);
	else
	{
		ft_putstr_fd("Error ", 2);
		ft_putnbr_fd(err, 2);
		ft_putendl_fd("", 2);
	}
}

int			main(int ac, char *av[])
{
	t_lemin		lem;
	t_result	ret;

	init_lem(&lem);
	if (ac != 2 || (lem.fd = open(av[1], O_RDONLY)) == -1)
		lem.fd = 0;
	ret = read_input(lem.fd, &lem);
	if (ret == RET_OK)
		ret = check_all(&lem);
	if (ret == RET_OK)
		ret = find_all_paths(&lem);
	if (ret == RET_OK)
		print_given_data(&lem);
	else
		print_error(&lem, ret);
	if (lem.is_debug)
		print_all(&lem);
	delete_all(&lem);
	return (0);
}
