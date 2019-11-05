/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:59:43 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 14:59:43 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static t_result	add_lemlink_list(t_list **root, const char *l1, const char *l2)
{
	t_linkdata	*linkdata;
	t_list		*lst;
	size_t		l1_len;
	size_t		l2_len;

	l1_len = ft_strlen(l1);
	l2_len = ft_strlen(l2);
	lst = ft_lstaddblank(root, sizeof(t_linkdata) +
					(l1_len + l2_len) * sizeof(char));
	if (!lst)
		return (ERR_ENOMEM);
	linkdata = (t_linkdata *)lst->content;
	linkdata->l1 = linkdata->ldata;
	ft_strlcpy(linkdata->l1, l1, l1_len + 1);
	linkdata->l2 = linkdata->ldata + l1_len + 1;
	ft_strlcpy(linkdata->l2, l2, l2_len + 1);
	return (RET_OK);
}

t_result		add_lem_link(t_lemin *lem, char *str)
{
	char	*r1;
	char	*r2;

	r1 = str;
	r2 = ft_strchr(str, '-');
	if (!r2)
		return (ERR_WRONG_LINK);
	*r2++ = '\0';
	if (!check_room_exist(lem->rooms, ft_trim_spaces(r1)) ||
		!check_room_exist(lem->rooms, ft_trim_spaces(r2)))
		return (ERR_WRONG_LINK_ROOM);
	if (ft_strcmp(r1, r2) == 0)
		return (ERR_WRONG_LINK_TO_LINK);
	return (add_lemlink_list(&lem->links, r1, r2));
}
