/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:48:32 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/15 09:48:32 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result	add_path_to_arr(t_patharr *parr, t_path *path)
{
	t_pathdata *pdata;

	pdata = (t_pathdata *)ft_memalloc(sizeof(*pdata));
	if (!pdata)
		return (ERR_ENOMEM);
	pdata->visited = 0;
	pdata->path = path;
	pdata->size = ft_array_size(path);
	if (ft_array_add(parr, pdata) != 0)
	{
		ft_memdel((void **)&pdata);
		return (ERR_ENOMEM);
	}
	return (RET_OK);
}

t_result	add_room_to_path(t_path *path, t_roomdata *room)
{
	return (ft_array_add(path, (void *)room) == 0 ? RET_OK : ERR_ENOMEM);
}
