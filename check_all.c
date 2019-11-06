/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:49:38 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/05 15:49:38 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_result	is_start_end_exists(t_list *root)
{
	int			start_count;
	int			end_count;
	t_roomdata	*rdata;

	start_count = 0;
	end_count = 0;
	while (root)
	{
		rdata = (t_roomdata *)root->content;
		if (rdata->cmd == LEM_CMD_START)
			start_count++;
		if (rdata->cmd == LEM_CMD_END)
			end_count++;
		root = root->next;
	}
	return (start_count == 1 && end_count == 1 ? RET_OK : ERR_NO_START_OR_END);
}

t_result	check_all(t_lemin *lem)
{
	t_result	res;

	if (ft_lstsize(lem->links) == 0)
		return (ERR_NO_LINKS);
	if ((res = is_start_end_exists(lem->rooms)) != RET_OK)
		return (res);
	graph_create(lem);
	return (RET_OK);
}
