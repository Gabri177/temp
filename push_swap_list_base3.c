/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_list_base3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:10:20 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 08:38:15 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	l_rotate_nom(t_list *l, int *num_pa)
{
	int		tem;

	if (!l || l_len (l) < 2)
		return (FALSE);
	sol_pa_pb (*num_pa);
	*num_pa = 0;
	tem = l->num;
	while (l->last)
	{
		l->num = l->last->num;
		l = l->last;
	}
	l->num = tem;
	ft_puts ("ra\n");
	return (TRUE);
}

t_bool	l_rotate_rev(t_list *l, int *num_pa)
{
	int		tem;
	t_list	*pre;

	if (!l || l_len (l) < 2)
		return (FALSE);
	sol_pa_pb (*num_pa);
	*num_pa = 0;
	pre = l_grep_index (l, l_len (l) - 1);
	tem = pre->num;
	while (pre->front)
	{
		pre->num = pre->front->num;
		pre = pre->front;
	}
	l_grep_index (l, 0)->num = tem;
	ft_puts ("rra\n");
	return (TRUE);
}

t_bool	l_push(t_list **l1, t_list **l2, t_bool isa, int *ispa)
{
	t_list	*tem;

	if (!l1 || !(*l1) || !l2 || !l_len(*l1))
		return (FALSE);
	tem = *l1;
	if (tem->last)
	{
		*l1 = (*l1)->last;
		(*l1)->front = NULL;
	}
	else
		*l1 = NULL;
	l_add_front (l2, tem->num);
	free (tem);
	if (isa)
		*ispa += 1;
	else
		*ispa -= 1;
	if (*l1)
		l_fresh_index (*l1);
	return (TRUE);
}

t_bool	l_swap_index(t_list *l, int i1, int i2)
{
	int	tem;

	if (!l)
		return (FALSE);
	if (!l_grep_index (l, i2) || !l_grep_index (l, i1))
		return (FALSE);
	tem = l_grep_index (l, i2)->index;
	l_grep_index (l, i2)->index = l_grep_index (l, i1)->index;
	l_grep_index (l, i1)->index = tem;
	return (TRUE);
}

t_bool	l_sort(t_list *l)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!l)
		return (FALSE);
	len = l_len (l);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (l_grep_index (l, j)->num > l_grep_index (l, j + 1)->num)
				l_swap (&l, j, j + 1);
			j ++;
		}
		i ++;
	}
	return (TRUE);
}
