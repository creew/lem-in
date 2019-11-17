/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:35:35 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/04 16:35:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result	add_roomdata(t_roomarr *arr, const char *name,
						const int *xy, int cmd)
{
	t_roomdata	*rdata;
	size_t		len;

	len = ft_strlen(name);
	rdata = ft_memalloc(sizeof(t_roomdata) + len * sizeof(char));
	if (rdata == NULL)
		return (ERR_ENOMEM);
	if (ft_array_add(arr, rdata) != 0)
	{
		ft_memdel((void **)&rdata);
		return (ERR_ENOMEM);
	}
	rdata->index = ft_array_size(arr) - 1;
	rdata->x = xy[0];
	rdata->y = xy[1];
	rdata->cmd = cmd;
	rdata->weigth = FT_INTMAX;
	rdata->visited = 0;
	ft_strlcpy(rdata->name, name, len + 1);
	return (RET_OK);
}
