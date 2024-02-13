/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_list_base4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 03:45:06 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 22:17:32 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	l_copy(t_list *ori, t_list **new)
{
	int	i;
	int	len;

	if (!ori)
		return (FALSE);
	i = 0;
	len = l_len (ori);
	while (i < len)
	{
		l_add_tail (new, l_grep_index (ori, i)->num);
		i ++;
	}
	return (TRUE);
}

t_list	*l_grep_val(t_list *l, int val)
{
	if (!l)
		return (NULL);
	while (l)
	{
		if (l->num == val)
			return (l);
		l = l->last;
	}
	return (NULL);
}

t_bool	l_neg_to_pos(t_list *ref, t_list *ori)
{
	int	i;

	i = 0;
	if (!ref || !ori)
		return (FALSE);
	while (i < l_len (ori))
	{
		l_grep_index (ori, i)->num = l_grep_val (ref,
			l_grep_index (ori, i)->num)->index;
		i ++;
	}
	l_destory (&ref);
	return (TRUE);
}

t_bool	l_sa(t_list *ori)
{
	if (!ori)
		return (FALSE);
	l_swap (&ori, 0, 1);
	ft_puts ("sa\n");
	return (TRUE);
}
