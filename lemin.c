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

int		main(int ac, char *av[])
{
	t_lemin		lem;
	t_result	ret;

	(void)ac;
	(void)av;
	ft_bzero(&lem, sizeof(lem));
	ret = read_input(0, &lem);
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
