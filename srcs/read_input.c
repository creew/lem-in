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

static void		get_lem_cmd(char *str, char *cmd)
{
	if (*str == '#' && *(str + 1) == '#')
	{
		ft_trim_spaces(str + 2);
		if (ft_strequ(str + 2, "start"))
			*cmd = LEM_CMD_START;
		else if (ft_strequ(str + 2, "end"))
			*cmd = LEM_CMD_END;
	}
}

static t_result	parse_not_comment_str(t_lemin *lem, char *s,
				int *is_rooms, char cmd)
{
	if (*is_rooms && count_numbers(s) == 3)
		return (add_lem_room(lem, s, cmd));
	*is_rooms = 0;
	return (add_lem_link(lem, s));
}

static t_result	read_rooms_and_links(int fd, t_lemin *lem)
{
	int			is_rooms;
	char		*s;
	t_result	res;
	char		cmd;

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
			get_lem_cmd(s, &cmd);
		ft_strdel(&s);
	}
	return (RET_OK);
}

t_result		read_input(int fd, t_lemin *lem)
{
	char	*s;
	int		res;

	while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_READ_ANTS_NUMBER);
		if (*s != '#')
			break ;
		ft_strdel(&s);
	}
	if (ft_safe_atoi(s, &lem->num_ants) != FT_ATOI_OK || lem->num_ants < 1)
		return (ERR_WRONG_ANTS_NUMBER);
	ft_strdel(&s);
	return (read_rooms_and_links(fd, lem));
}
