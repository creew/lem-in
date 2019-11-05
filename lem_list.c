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

#include "lem-in.h"

int		add_lem_list(t_list **root, const char *name, const int *xy, int cmd)
{
	 t_ldata	*ldata;
	 t_list		*lst;
	 size_t 	len;

	 len = ft_strlen(name);
	 lst = ft_lstaddblank(root, sizeof(t_ldata) + len * sizeof(char));
	 if (!lst)
	 	return (ERR_ENOMEM);
	 ldata = (t_ldata *)lst->content;
	 ldata->x = xy[0];
	 ldata->y = xy[1];
	 ldata->cmd = cmd;
	 ft_strlcpy(ldata->name, name, len + 1);
	 return (RET_OK);
}
