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

int		read_input(int fd, t_lemin *lem)
{
	char	*s;
	int		res;

	if (get_next_line(fd, &s) < 0)
		return (ERR_READ_ANTS_NUMBER);
	if (ft_safe_atoi(s, &lem->number_ants) != FT_ATOI_OK)
		return (ERR_WRONG_ANTS_NUMBER);
	while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_GNL_ERROR);
	}
	return (RET_OK);
}

int		main(int ac, char *av[])
{
	t_lemin lem;
	if (read_input(0, &lem) != RET_OK)
		ft_putendl("Error");
	return (0);
}
