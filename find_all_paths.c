/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 07:08:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 07:08:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int 	rem_from_neighbor(void *data1, void *data2)
{
	t_neigbor	*neighbor;
	t_roomdata	*rdata;

	neighbor = (t_neigbor *)data1;
	rdata = (t_roomdata *)data2;
	return (neighbor->room == rdata ? 0 : 1);
}

t_result	remove_path(t_path **path, size_t sindex, size_t eindex)
{
	size_t		size;
	t_roomdata	*sroom;
	t_roomdata	*eroom;
	t_path		*slst;
	t_path		*elst;

	size = ft_lstsize(*path);
	if (sindex >= eindex || eindex >= size)
		return (ERR_INCORRECT_PATH_REMOVE);
	if ((slst = ft_lstget(*path, sindex)) == NULL ||
		(elst = ft_lstget(*path, eindex)) == NULL)
		return (ERR_INCORRECT_PATH_REMOVE);
	sroom = (t_roomdata *)slst->content;
	eroom = (t_roomdata *)elst->content;
	ft_lstremove_if(&sroom->neigborlst, rem_from_neighbor, sroom);
	ft_lstremove_if(&sroom->neigborlst, rem_from_neighbor, eroom);
	return (RET_OK);
}

t_result	find_all_paths(t_lemin *lem)
{
	mehmet_algo(lem);

	return (RET_OK);
}