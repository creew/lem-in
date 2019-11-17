/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:28:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 16:28:05 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			push_ants(t_patharr *arr)
{
	size_t	path_count;


	path_count = ft_array_size(arr);
	while (path_count--)
	{




	}
	return (0);
}

void	start_ants(t_lemin *lem)
{
	size_t		path_count;
	t_roomdata	*rdata;

	rdata = find_room_by_cmd(&lem->rooms, LEM_CMD_START);
	if (rdata)
	{
		rdata->ant_count = lem->num_ants;
		if ((path_count = ft_array_size(&lem->paths)))
		{


		}
	}
}