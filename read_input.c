/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:42:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 11:42:20 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		add_lem_link(t_lemin *lem, char *str)
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
	return (RET_OK);
}

int		get_lem_cmd(char *str)
{
	if (*str == '#' && *(str + 1) == '#')
	{
		ft_trim_spaces(str + 2);
		if (strcmp(str + 2, "start") == 0)
			return (LEM_CMD_START);
		if (strcmp(str + 2, "end") == 0)
			return (LEM_CMD_END);
	}
	return (LEM_CMD_NONE);
}

int		parse_not_comment_str(t_lemin *lem, char *s, int *is_rooms, int cmd)
{
	if (*is_rooms && count_numbers(s) == 3)
		return (add_lem_room(lem, s, cmd));
	*is_rooms = 0;
	return (add_lem_link(lem, s));
}

int		read_rooms_and_links(int fd, t_lemin *lem)
{
	int		is_rooms;
	char	*s;
	int		res;
	int		cmd;

	cmd = LEM_CMD_NONE;
	is_rooms = 1;
	while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_GNL_ERROR);
		if (*s != '#')
		{
			if ((res = parse_not_comment_str(lem, s, &is_rooms, cmd)) != RET_OK)
			{
				ft_strdel(&s);
				return (res);
			}
			cmd = LEM_CMD_NONE;
		}
		else
			cmd = get_lem_cmd(s);
		ft_strdel(&s);
	}
	return (RET_OK);
}

int		read_input(int fd, t_lemin *lem)
{
	char	*s;

	if (get_next_line(fd, &s) < 0)
		return (ERR_READ_ANTS_NUMBER);
	if (ft_safe_atoi(s, &lem->num_ants) != FT_ATOI_OK || lem->num_ants < 1)
		return (ERR_WRONG_ANTS_NUMBER);
	ft_strdel(&s);
	return (read_rooms_and_links(fd, lem));
}
