/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:40:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/06 09:40:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result	find_childrens(t_roomlst *rlst, t_linklst *llst, char *name)
{
	int			count;
	char		*oppname;
	t_roomdata	*rdata;

	count = 0;
	while ((oppname = getlink_by_name(llst, name, count)) != NULL)
	{
		rdata = find_room_by_name(rlst, oppname);
		if (!rdata)
			return (ERR_WRONG_LINK_ROOM);
		count++;
	}
	if (!count)
		return (ERR_WRONG_ROOM_NAME);
	return (RET_OK);
}

t_result	graph_create(t_lemin *lem)
{
	t_roomdata	*start;

	start = find_room_by_cmd(lem->rooms, LEM_CMD_START);
	if (!start)
		return (ERR_NO_START_OR_END);


	return (RET_OK);
}
