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
