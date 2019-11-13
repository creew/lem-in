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

char		*getlink_by_name(t_linkarr *larr, const char *name, int n)
{
	t_linkdata	*ldata;
	size_t 		size;

	size = larr->num_elems;
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if (ft_strequ(name, ldata->l1))
			{
				if (!n--)
					return (ldata->l2);
			}
			if (ft_strequ(name, ldata->l2))
			{
				if (!n--)
					return (ldata->l1);
			}
		}
	}
	return (NULL);
}

static int		is_link_exist(t_linkarr *larr, const char *l1, const char *l2)
{
	t_linkdata *ldata;
	size_t 		size;

	size = larr->num_elems;
	while (size--)
	{
		if (ft_array_get(larr, size, (void **)&ldata) == 0)
		{
			if ((ft_strequ(l1, ldata->l1) && ft_strequ(l2, ldata->l2)) ||
				(ft_strequ(l1, ldata->l2) && ft_strequ(l2, ldata->l1)))
				return (1);
		}
	}
	return (0);
}

static t_result	add_lemlink_list(t_linkarr *larr,
					const char *l1, const char *l2)
{
	t_linkdata	*ldata;
	size_t		l1_len;
	size_t		l2_len;

	if (!is_link_exist(larr, l1, l2))
	{
		l1_len = ft_strlen(l1);
		l2_len = ft_strlen(l2);
		ldata = ft_memalloc(sizeof(*ldata) + (l1_len + l2_len) * sizeof(char));
		if (!ldata)
			return (ERR_ENOMEM);
		if (ft_array_add(larr, ldata) != 0)
		{
			ft_memdel((void **)&ldata);
			return (ERR_ENOMEM);
		}
		ldata->l1 = ldata->ldata;
		ft_strlcpy(ldata->l1, l1, l1_len + 1);
		ldata->l2 = ldata->ldata + l1_len + 1;
		ft_strlcpy(ldata->l2, l2, l2_len + 1);
	}
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
	if (!find_room_by_name(&lem->rooms, ft_trim_spaces(r1)) ||
		!find_room_by_name(&lem->rooms, ft_trim_spaces(r2)))
		return (ERR_WRONG_LINK_ROOM);
	if (ft_strequ(r1, r2))
		return (ERR_WRONG_LINK_TO_LINK);
	return (add_lemlink_list(&lem->links, r1, r2));
}
