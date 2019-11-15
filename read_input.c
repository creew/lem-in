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

#include "lemin.h"

static t_result	get_lem_cmd(char *str)
{
	if (*str == '#' && *(str + 1) == '#')
	{
		ft_trim_spaces(str + 2);
		if (ft_strequ(str + 2, "start"))
			return (LEM_CMD_START);
		if (ft_strequ(str + 2, "end"))
			return (LEM_CMD_END);
	}
	return (LEM_CMD_NONE);
}

static t_result	parse_not_comment_str(t_lemin *lem, char *s,
				int *is_rooms, int cmd)
{
	if (*is_rooms && count_numbers(s) == 3)
		return (add_lem_room(lem, s, cmd));
	*is_rooms = 0;
	return (add_lem_link(lem, s));
}

/*
** FIXME: Error reading comments after "##start" or "##end" (flag is missing)
** -----
*/

static t_result	read_rooms_and_links(int fd, t_lemin *lem)
{
	int			is_rooms;
	char		*s;
	t_result	res;
	int			cmd;

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

/*
** FIXME: Error reading comments before ants number
** -----
*/

t_result		read_input(int fd, t_lemin *lem)
{
	char	*s;

	if (get_next_line(fd, &s) < 0)
		return (ERR_READ_ANTS_NUMBER);
	if (ft_safe_atoi(s, &lem->num_ants) != FT_ATOI_OK || lem->num_ants < 1)
		return (ERR_WRONG_ANTS_NUMBER);
	ft_strdel(&s);
	return (read_rooms_and_links(fd, lem));
}
