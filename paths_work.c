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

static void remove_pathlst(void *data, size_t size)
{
	(void)data;
	(void)size;
}

static void remove_pdata(void *data)
{
	t_pathdata *pdata;

	pdata = (t_pathdata *)data;
	ft_lstdel(&pdata->path, remove_pathlst);
	ft_memdel(&data);
}

void 		remove_all_paths(t_patharr *parr)
{
	ft_array_remove_all(parr, remove_pdata);
}

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
