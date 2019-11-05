/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:23:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/04 12:23:02 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		free_return(void *data, int ret)
{
	ft_memdel(&data);
	return (ret);
}

int		count_numbers(char *str)
{
	char	*s;
	int		count;

	count = 0;
	while ((s = ft_strchr(str, ' ')))
	{
		s++;
		if (s != (str + 1))
			count++;
		str = s;
	}
	if (*str != '\0')
		count++;
	return (count);
}

char	*get_next_word(char *str, int *last)
{
	char	*end;

	*last = 0;
	while ((end = ft_strchr(str, ' ')))
	{
		if (end != str)
			break;
		str = end + 1;
	}
	if (*str != '\0')
	{
		if (end == NULL)
			*last = 1;
		else
			*end = '\0';
		return (str);
	}
	return (NULL);
}

int		add_lem_room(t_lemin *lem, char *str)
{
	int		last;
	int 	arg2;
	char	*name;
	char	*s1;
	char	*s2;

	name = get_next_word(str, &last);
	if (!name || last)
		return (ERR_WRONG_ROOM_NAME);
	s1 = get_next_word(name + ft_strlen(name) + 1, &last);
	if (!s1 || last)
		return (ERR_WRONG_ROOM_ARG);
	s2 = get_next_word(s1 + ft_strlen(s1) + 1, &last);
	if (!s2)
		return (ERR_WRONG_ROOM_ARG);
	if (ft_safe_atoi(ft_trim_spaces(s1), &last) != FT_ATOI_OK ||
		ft_safe_atoi(ft_trim_spaces(s2), &arg2) != FT_ATOI_OK)
		return (ERR_WRONG_ROOM_ARG);
	return (add_lem_list(&lem->lem_list, name, last, arg2));
}

int		add_lem_link(t_lemin *lem, char *str)
{
	char	*r1;
	char	*r2;
	int		last;

	r1 = str;
	r2 = ft_strchr(str, '-');
	if (!str)
		return (ERR_WRONG_LINK);
	*r2++ = '\0';
}

int		read_rooms(int fd, t_lemin *lem)
{
    int		is_rooms;
    char	*s;
    int		res;

    is_rooms = 1;
    while ((res = get_next_line(fd, &s)))
	{
		if (res < 0)
			return (ERR_GNL_ERROR);
		if (*s != '#')
		{
			if (is_rooms && count_numbers(s) == 3)
			{
				if ((res = add_lem_room(lem, s)) != RET_OK)
					return (free_return(s, res));
			}
			else
			{
				is_rooms = 0;
				if ((res = add_lem_link(lem, s)) != RET_OK)
					return (free_return(s, res));
			}
		}
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
	return (read_rooms(fd, lem));
}

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_lemin lem;
	int 	ret;

	ft_bzero(&lem, sizeof(lem));
	if ((ret = read_input(0, &lem)) != RET_OK)
	{
		ft_putstr("Error ");
		ft_putnbr(ret);
		ft_putendl("");
	}
	return (0);
}
