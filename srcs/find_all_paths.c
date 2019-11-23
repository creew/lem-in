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
#include "ft_printf.h"

static t_result		remove_path(t_path *path, size_t sindex, size_t eindex,
	t_linkdata *link)
{
	t_roomdata		*slst;
	t_roomdata		*elst;

	if (ft_array_get(path, sindex, (void **)&slst) != 0 ||
		ft_array_get(path, eindex, (void **)&elst) != 0)
		return (ERR_INCORRECT_PATH_REMOVE);
	link->left = slst;
	link->right = elst;
	return (RET_OK);
}


t_result			find_all_paths(t_lemin *lem)
{



	//suurballe_algo(&lem->adjm, &lem->paths);
	return (RET_OK);
}
