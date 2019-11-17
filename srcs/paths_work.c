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
	pdata->size = ft_lstsize(path);
	if (ft_array_add(parr, pdata) != 0)
	{
		ft_memdel((void **)&pdata);
		return (ERR_ENOMEM);
	}
	return (RET_OK);
}

t_result	add_room_to_path(t_path **path, t_roomdata *room)
{
	t_path	*pathelem;

	pathelem = ft_lstnewblank(0);
	if (!pathelem)
		return (ERR_ENOMEM);
	pathelem->content = room;
	ft_lstadd_back(path, pathelem);
	return (RET_OK);
}
