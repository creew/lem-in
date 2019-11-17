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

#include "lemin.h"

t_roomdata		*get_opposite_roomlink_by_name(
	t_linkarr *larr, const char *name, int n)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if (ft_strequ(name, ldata->rdata1->name))
			{
				if (!n--)
					return (ldata->rdata2);
			}
			if (ft_strequ(name, ldata->rdata2->name))
			{
				if (!n--)
					return (ldata->rdata1);
			}
		}
	}
	return (NULL);
}

static int		is_link_exist(t_linkarr *larr, t_roomdata *l1, t_roomdata *l2)
{
	t_linkdata	*ldata;
	size_t		size;

	size = ft_array_size(larr);
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if ((l1 == ldata->rdata1 && l2 == ldata->rdata2) ||
				(l1 == ldata->rdata2 && l2 == ldata->rdata1))
				return (1);
		}
	}
	return (0);
}

static t_result	add_lemlink_list(t_linkarr *larr,
					t_roomdata *l1, t_roomdata *l2)
{
	t_linkdata	*ldata;

	if (!is_link_exist(larr, l1, l2))
	{
		ldata = ft_memalloc(sizeof(*ldata));
		if (!ldata)
			return (ERR_ENOMEM);
		if (ft_array_add(larr, ldata) != 0)
		{
			ft_memdel((void **)&ldata);
			return (ERR_ENOMEM);
		}
		ldata->rdata1 = l1;
		ldata->rdata2 = l2;
	}
	return (RET_OK);
}

/*
** FIXME: Wrong parsing links like "abc - def" and "a-b-c-def"
** -----
*/

t_result		add_lem_link(t_lemin *lem, char *str)
{
	char		*r1;
	char		*r2;
	t_roomdata	*room1;
	t_roomdata	*room2;

	r1 = str;
	r2 = ft_strchr(str, '-');
	if (!r2)
		return (ERR_WRONG_LINK);
	*r2++ = '\0';
	if (!(room1 = find_room_by_name(&lem->rooms, ft_trim_spaces(r1))) ||
		!(room2 = find_room_by_name(&lem->rooms, ft_trim_spaces(r2))))
		return (ERR_WRONG_LINK_ROOM);
	if (ft_strequ(r1, r2))
		return (ERR_WRONG_LINK_TO_LINK);
	return (add_lemlink_list(&lem->links, room1, room2));
}
