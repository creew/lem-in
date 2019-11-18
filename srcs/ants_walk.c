/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:28:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/17 16:28:05 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "ft_printf.h"

static void	print_move(t_roomdata *cur, int *is_not_first)
{
	if (*is_not_first)
		ft_putstr(" ");
	*is_not_first = 1;
	ft_printf("L%d-%s", cur->ant_index, cur->name);
}

static int	push_one_path(size_t index, t_lemin *lem,
	int *is_not_first, size_t *sum)
{
	size_t		size;
	t_pathdata	*pdata;
	t_roomdata	*cur;
	t_roomdata	*prev;

	if (ft_array_get(&lem->paths, index, (void **)&pdata) == 0)
	{
		size = ft_array_size(pdata->path);
		while (size > 1)
		{
			size--;
			if (ft_array_get(pdata->path, size, (void **)&cur) == 0 &&
				ft_array_get(pdata->path, size - 1, (void **)&prev) == 0)
			{
				if (prev->ant_count)
				{
					if (size == 1)
					{
						if (index != 0 && prev->ant_count <=
						(int)((ft_array_size(pdata->path) - 1) * index) - (int)*sum)
							break ;
						cur->ant_index = lem->num_ants - prev->ant_count + 1;
					}
					else
						cur->ant_index = prev->ant_index;
					cur->ant_count++;
					prev->ant_count--;
					print_move(cur, is_not_first);
				}
			}
		}
		*sum = *sum + (ft_array_size(pdata->path) - 1);
	}
	return (0);
}

void		print_solution(t_lemin *lem)
{
	size_t		path_count;
	size_t		count;
	size_t		total_size;
	int			is_not_first;

	lem->se.start->ant_count = lem->num_ants;
	while (lem->se.end->ant_count != lem->num_ants)
	{
		count = 0;
		total_size = 0;
		is_not_first = 0;
		path_count = ft_array_size(&lem->paths);
		while (count < path_count)
		{
			push_one_path(count, lem, &is_not_first, &total_size);
			count++;
		}
		ft_putendl("");
	}
}
