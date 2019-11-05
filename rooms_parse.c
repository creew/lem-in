/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:50:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 11:50:18 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	check_room_xy_exist(t_list *rooms, int x, int y)
{
	t_roomdata *rdata;

	while (rooms)
	{
		rdata = (t_roomdata *)rooms->content;
		if (rdata->x == x && rdata->y == y)
			return (1);
		rooms = rooms->next;
	}
	return (0);
}

t_result	add_lem_room(t_lemin *lem, char *str, int cmd)
{
	int		last;
	int		xy[2];
	char	*name;
	char	*s1;
	char	*s2;

	name = get_next_word(str, &last);
	if (!name || last)
		return (ERR_EMPTY_ROOM_NAME);
	if (!check_room_valid(ft_trim_spaces(name)))
		return (ERR_WRONG_ROOM_NAME);
	if (check_room_exist(lem->rooms, name))
		return (ERR_WRONG_ROOM_DUPL);
	s1 = get_next_word(name + ft_strlen(name) + 1, &last);
	if (!s1 || last)
		return (ERR_WRONG_ROOM_ARG);
	s2 = get_next_word(s1 + ft_strlen(s1) + 1, &last);
	if (!s2)
		return (ERR_WRONG_ROOM_ARG);
	if (ft_safe_atoi(ft_trim_spaces(s1), &xy[0]) != FT_ATOI_OK ||
		ft_safe_atoi(ft_trim_spaces(s2), &xy[1]) != FT_ATOI_OK)
		return (ERR_WRONG_ROOM_ARG);
	if (check_room_xy_exist(lem->rooms, xy[0], xy[1]))
		return (ERR_WRONG_ROOM_XY_DUPL);
	return (add_lem_list(&lem->rooms, name, xy, cmd));
}

int			check_room_valid(const char *name)
{
	if (!name || !*name || *name == 'L' || *name == '#')
		return (0);
	return (1);
}

int			check_room_exist(t_list *rooms, const char *name)
{
	t_roomdata *rdata;

	while (rooms)
	{
		rdata = (t_roomdata *)rooms->content;
		if (ft_strcmp(name, rdata->name) == 0)
			return (1);
		rooms = rooms->next;
	}
	return (0);
}
