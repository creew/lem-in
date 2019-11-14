/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:46:37 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/06 15:35:47 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_stack_push(t_ftstack *stack, void *data)
{
	void	**newstack;
	void	**old;

	if (stack->pos >= stack->size)
	{
		newstack = ft_calloc(stack->size + stack->init_val, sizeof(void *));
		if (!newstack)
			return (1);
		if (stack->data)
			ft_voidcpy(newstack, stack->data, stack->size);
		old = stack->data;
		stack->data = newstack;
		stack->size += stack->init_val;
		ft_memdel((void **)&old);
	}
	stack->data[stack->pos++] = data;
	return (0);
}
