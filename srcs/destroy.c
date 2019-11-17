/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:02:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 10:02:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	remove_pathlst_callback(void *data, size_t size)
{
	(void)data;
	(void)size;
}

static void	remove_pdata(void *data)
{
	t_pathdata *pdata;

	pdata = (t_pathdata *)data;
	ft_lstdel(&pdata->path, remove_pathlst_callback);
	ft_memdel(&data);
}

void		remove_all_paths(t_patharr *parr)
{
	ft_array_remove_all(parr, remove_pdata);
}

static void	delroomlinkarr(void *data)
{
	ft_memdel(&data);
}

void		delete_all(t_lemin *lem)
{
	ft_array_remove_all(&lem->rooms, delroomlinkarr);
	ft_array_remove_all(&lem->links, delroomlinkarr);
	remove_all_paths(&lem->paths);
	ft_memdel((void **)&lem->matrix);
}
