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

t_result	add_lem_list(t_roomlst **root, const char *name,
						const int *xy, int cmd)
{
	t_roomdata	*ldata;
	t_roomlst	*lst;
	size_t		len;

	len = ft_strlen(name);
	lst = ft_lstaddblank(root, sizeof(t_roomdata) + len * sizeof(char));
	if (!lst)
		return (ERR_ENOMEM);
	ldata = (t_roomdata *)lst->content;
	ldata->x = xy[0];
	ldata->y = xy[1];
	ldata->cmd = cmd;
	ft_strlcpy(ldata->name, name, len + 1);
	return (RET_OK);
}

static void	del_list_elem(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

void		free_lem_list(t_roomlst **root)
{
	ft_lstdel(root, del_list_elem);
}
