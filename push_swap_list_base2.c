/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_list_base2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:48:27 by yugao             #+#    #+#             */
/*   Updated: 2024/02/13 08:43:16 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	l_print(t_list *l)
{
	if (!l)
		return (FALSE);
	ft_puts ("----------\n");
	while (l)
	{
		ft_puts ("INDEX:");
		ft_putnbr (l->index);
		ft_puts ("  ");
		ft_puts ("VAL:");
		ft_putnbr (l->num);
		ft_puts ("  \n");
		l = l->last;
	}
	ft_puts ("^^^^^^^^^^\n\n");
	return (TRUE);
}

t_list	*l_grep_index(t_list *l, int index)
{
	if (!l)
		return (NULL);
	if (index >= l_len (l) || index < 0)
		return (NULL);
	while (l)
	{
		if (l->index == index)
			return (l);
		l = l->last;
	}
	return (NULL);
}

t_bool	l_swap(t_list **l, int index1, int index2)
{
	int	tem;

	if (!l)
		return (FALSE);
	if (!(*l) || l_len (*l) < 2)
		return (FALSE);
	if (index1 < 0 || index1 > l_len (*l) - 1
		|| index2 < 0 || index2 > l_len (*l) - 1)
		return (FALSE);
	tem = l_grep_index (*l, index2)->num;
	l_grep_index (*l, index2)->num = l_grep_index (*l, index1)->num;
	l_grep_index (*l, index1)->num = tem;
	return (TRUE);
}

t_bool	l_destory(t_list **l)
{
	t_list	*tem;

	if (!l || !(*l) || !l_len (*l))
		return (FALSE);
	while ((*l)->last)
	{
		tem = *l;
		*l = (*l)->last;
		free (tem);
		tem = NULL;
	}
	free (*l);
	*l = NULL;
	return (TRUE);
}

t_bool	l_isorden(t_list *l)
{
	int	tem;

	if (!l)
		return (FALSE);
	tem = l->num;
	l = l->last;
	while (l)
	{
		if (l->num < tem)
			break ;
		else
			tem = l->num;
		l = l->last;
	}
	if (!l)
		return (TRUE);
	return (FALSE);
}
