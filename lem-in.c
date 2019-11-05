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

#include "lem-in.h"

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_lemin lem;
	int 	ret;

	ft_bzero(&lem, sizeof(lem));
	if ((ret = read_input(0, &lem)) != RET_OK)
	{
		ft_putstr("Error ");
		ft_putnbr(ret);
		ft_putendl("");
	}
	return (0);
}
